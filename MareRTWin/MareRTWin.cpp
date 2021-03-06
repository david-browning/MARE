#include "stdafx.h"
#include "MareRTWin.h"
#include "WindowFunctions.h"
#include <mare_rt.h>
#include <mare_compiler_consts.h>

#define MAX_LOADSTRING 100

// Forward declarations of functions included in this code module:
extern ATOM                MyRegisterClass(HINSTANCE hInstance);
extern BOOL                InitInstance(HINSTANCE, int, int w, int h);
extern LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

MARE_MODULE __mare_module__;
static LONG __minWindowWidth__;
static LONG __minWindowHeight__;
static int __windowWidth__ = 425;
static int __windowHeight__ = 550;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
							 _In_opt_ HINSTANCE hPrevInstance,
							 _In_ LPWSTR    lpCmdLine,
							 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//Parse command line to get the module path.
	int numArgs = 0;
	auto rawcmdArgs = CommandLineToArgvW(GetCommandLine(), &numArgs);
	if(!rawcmdArgs)
	{
		std::cerr << "Could not parse the command line arguments." << std::endl;
		return E_CMD_PARSE;
	}

	//For each command line argument:
	//Skip the first one.
	for(auto i = 1; i < numArgs; i++)
	{
		//Modules will not start with a dash.
		if(rawcmdArgs[i][0] != '-')
		{
			//Load the module into the address space.
			
			//Only load the DLL if one hasn't been loaded.
			if(!__mare_module__.IsLoaded)
			{
				auto ret = marert::OpenMAREProgram(rawcmdArgs[i], &__mare_module__);
				if(ret != 0)
				{
					return ret;
				}

				__minWindowWidth__ = LONG(__windowWidth__);
				__minWindowHeight__ = LONG(__minWindowWidth__ / __mare_module__.WToHAspectRatio());
			}
		}
		else
		{
			//Evaluate the options.








		}
	}

	//Done with command line args
	LocalFree(rawcmdArgs);

	//Initialize GDI
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MARERTWIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//Perform application initialization:
	if(!InitInstance(hInstance, nCmdShow, __windowWidth__, __windowHeight__))
	{
		return E_WINDOW_INITIALIZATION;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MARERTWIN));

	//Main message loop:
	MSG msg;
	while(GetMessage(&msg, nullptr, 0, 0))
	{
		if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//Done with GDI
	GdiplusShutdown(gdiplusToken);

	//Free the module.
	if(__mare_module__.IsLoaded)
	{
		marert::CloseMAREProgram(__mare_module__);
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MARERTWIN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MARERTWIN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MARERTWIN));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, int w, int h)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
									  CW_USEDEFAULT, 0, w, h, nullptr, nullptr, hInstance, nullptr);

	if(!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch(wmId)
			{
				case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				}
				case ID_FILE_PRINT:
				{
					marert::PrintMAREProgramUsingDialog(hWnd, __mare_module__);
					break;
				}
				default:
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			
			//Run the MARE program when the window needs to be drawn.
			if(__mare_module__.IsLoaded)
			{
				MareRT rt(hdc, __windowWidth__, __windowHeight__,
							 __mare_module__.GetPageWidthProc(),
							 __mare_module__.GetPageHeightProc());
				__mare_module__.RunProgramProc(rt);
			}

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_SIZING:
		{
			//When the user tries to resize the window, enforce certain proportions.
			RECT* windowRect_p = (RECT*)lParam;
			return marert::OnWindowResizing(hWnd, __mare_module__, wParam, windowRect_p, 
													  __minWindowWidth__, __minWindowHeight__);
		}
		case WM_SIZE:
		{
			//The window has been resized. 
			//Update the window width and height so when the window is redrawn, 
			//the image is updated.
			__windowWidth__ = LOWORD(lParam);
			__windowHeight__ = HIWORD(lParam);
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
		case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
		case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
	}

	return (INT_PTR)FALSE;
}
