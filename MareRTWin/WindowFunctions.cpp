#include "stdafx.h"
#include "WindowFunctions.h"
#include <mare_rt.h>
#include <mare_compiler_consts.h>

void marert::PrintMAREProgramUsingDialog(HWND parentWindow, MARE_MODULE& mod)
{
	PRINTDLG pd;
	memset(&pd, 0, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner = parentWindow;
	pd.Flags = PD_ALLPAGES | PD_RETURNDC | PD_RETURNDC;

	BOOL pdRet = PrintDlg(&pd);
	if(pdRet == 0)
	{
		if(CommDlgExtendedError() != 0)
		{
			MessageBox(parentWindow, L"There was a problem printing. Try again.",
						  L"Print Error", MB_OK | MB_ICONERROR);
			return;
		}
		else
		{
			return;
		}
	}

	DOCINFO docInfo;
	memset(&docInfo, 0, sizeof(docInfo));
	docInfo.cbSize = sizeof(docInfo);
	docInfo.lpszDocName = L"MARE Program";

	StartDoc(pd.hDC, &docInfo);
	StartPage(pd.hDC);

	const auto paperW = GetDeviceCaps(pd.hDC, HORZRES);
	const auto paperH = GetDeviceCaps(pd.hDC, VERTRES);

	MareRT rt(pd.hDC,
				 paperW,
				 paperH,
				 mod.GetPageWidthProc(),
				 mod.GetPageHeightProc());
	mod.RunProgramProc(rt);

	EndPage(pd.hDC);
	EndDoc(pd.hDC);
}

int marert::OpenMAREProgram(_IN_WSTR_Z_ const wchar_t* programPath,
									  _OUT_ MARE_MODULE* const mod)
{
	//Expand the path into a full path.
	wchar_t fullPath[MAX_PATH];
	auto ret = GetFullPathName(programPath, MAX_PATH, fullPath, nullptr);
	if(ret == 0)
	{
		const auto lastError = GetLastError();
		std::wstringstream message;
		message << L"Error " << lastError << " occurred when opening the MARE program.";
		marert::CannotOpenFileDialogBox(nullptr, &message.str());
		return lastError;
	}

	//Verify the dll file exists
	WIN32_FIND_DATA findFileData;
	HANDLE findFileHandle = FindFirstFile(fullPath, &findFileData);
	if(findFileHandle == INVALID_HANDLE_VALUE)
	{
		const auto lastError = GetLastError();
		if(lastError == ERROR_FILE_NOT_FOUND)
		{
			std::wstring message = L"The MARE program was not found.";
			marert::CannotOpenFileDialogBox(nullptr, &message);
			return E_FILE_LOAD;
		}
		else
		{
			std::wstringstream message;
			message << L"An unknown error occurred when opening the MARE program. Last error was " << GetLastError() << L".";
			marert::CannotOpenFileDialogBox(nullptr, &message.str());
			return E_FILE_LOAD;
		}
	}
	else
	{
		FindClose(findFileHandle);
	}

	HMODULE dll = LoadLibrary(fullPath);
	if(dll)
	{
		auto procAddr = (MareRunProc)GetProcAddress(dll, MARE_PROGRAM_ENTRY.c_str());
		auto getWidthAddr = (MareGetPageSizeProc)GetProcAddress(dll, MARE_GET_PAGE_WIDTH_ENTRY.c_str());
		auto getHeightAddr = (MareGetPageSizeProc)GetProcAddress(dll, MARE_GET_PAGE_HEIGHT_ENTRY.c_str());
		if(!procAddr || !getWidthAddr || !getHeightAddr)
		{
			std::wstringstream message;
			message << L"Could not find the function pointer for " << programPath << L". It is skipped.\n";
			marert::CannotOpenFileDialogBox(nullptr, &message.str());
		}
		else
		{
			*mod =
			{
				dll,
				procAddr,
				getHeightAddr,
				getWidthAddr,
				true
			};
		}
	}
	else
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}

	return 0;
}

void marert::CloseMAREProgram(_IN_ MARE_MODULE& mod)
{
	if(!FreeLibrary(mod.Module))
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}
}

LRESULT marert::OnWindowResizing(HWND parentWindow, MARE_MODULE& mod,
											WPARAM resizeMod, RECT* rect_p,
											LONG minWinWidth,
											LONG minWinHeight)
{
   if (mod.GetPageHeightProc == nullptr)
   {
      return FALSE;
   }

	const float wToHRatio = mod.WToHAspectRatio();
	const auto windowHeight = rect_p->bottom - rect_p->top;
	const auto windowWidth = rect_p->right - rect_p->left;
	switch(resizeMod)
	{
		case WMSZ_BOTTOM:
		{
			//Restrict the bottom to the minimum window height.
			rect_p->bottom = rect_p->top + std::max<LONG>(minWinHeight, windowHeight);

			rect_p->right = rect_p->left + std::max<LONG>(minWinWidth, LONG(windowHeight * wToHRatio));
			break;
		}
		case WMSZ_RIGHT:
		{
			//Restrict the right to the minimum window width.
			rect_p->right = rect_p->left + std::max<LONG>(minWinWidth, windowWidth);

			rect_p->bottom = rect_p->top + std::max<LONG>(minWinHeight, LONG(windowWidth / wToHRatio));
			break;
		}
		case WMSZ_TOPRIGHT:
		{
			break;
		}
		case WMSZ_BOTTOMRIGHT:
		{
			break;
		}
		case WMSZ_BOTTOMLEFT:
		case WMSZ_TOPLEFT:
		case WMSZ_LEFT:
		case WMSZ_TOP:
		{
			break;
		}
		default:
		{
         break;
		}
	}

	return TRUE;
}

void marert::CannotOpenFileDialogBox(_IN_OPT_ HWND parentWindow,
												 _IN_OPT_ const std::wstring* message)
{
	static const std::wstring defaultErrorMessage = L"There was a problem opening the MARE program."
		L"Try recompiling your program.";
	const std::wstring* msg_p;

	if(message)
	{
		msg_p = message;
	}
	else
	{
		msg_p = &defaultErrorMessage;
	}

	MessageBox(parentWindow, msg_p->c_str(), L"Cannot open the MARE program.", MB_OK | MB_ICONERROR);
}
