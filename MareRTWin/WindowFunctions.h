#pragma once

#include "stdafx.h"

namespace marert
{

extern void PrintMAREProgramUsingDialog(HWND parentWindow, MARE_MODULE& mod);

//Opens the program and stores it and its data in mod.
//mod must not be nullptr.
extern int OpenMAREProgram(_IN_WSTR_Z_ const wchar_t* programPath,
									_OUT_ MARE_MODULE* const mod);

	//Unloads the MARE_MODULE.
extern void CloseMAREProgram(_IN_ MARE_MODULE& mod);

//Call this when the window recieves WM_SIZING message.
extern LRESULT OnWindowResizing(HWND parentWindow,
										  MARE_MODULE& mod,
										  WPARAM resizeMod,
										  RECT* rect_p,
										  LONG minWinWidth,
										  LONG minWinHeight);

extern void CannotOpenFileDialogBox(_IN_OPT_ HWND parentWindow = nullptr,
												_IN_OPT_ const std::wstring* message = nullptr);

}