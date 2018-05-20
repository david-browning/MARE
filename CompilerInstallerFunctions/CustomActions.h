#pragma once
#include "stdafx.h"

extern "C" __declspec(dllexport) UINT __stdcall AddToPATH(MSIHANDLE hInstall);

extern "C" __declspec(dllexport) UINT __stdcall NoAction(MSIHANDLE hInstall)
{
	return ERROR_SUCCESS;
}

extern "C" __declspec(dllexport) UINT __stdcall RemoveFromPATH(MSIHANDLE hInstall);