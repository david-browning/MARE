#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <Shobjidl.h>
#include <tchar.h>

#include <annotations.h>
#include <mare_rt.h>

struct MARE_MODULE
{
	HMODULE Module = nullptr;
	MareRunProc RunProgramProc = nullptr;
	MareGetPageSizeProc GetPageHeightProc = nullptr;
	MareGetPageSizeProc GetPageWidthProc = nullptr;
	bool IsLoaded = false;
	float WToHAspectRatio()
	{
		return float(GetPageWidthProc()) / float(GetPageHeightProc());
	}
};

static constexpr int E_CMD_PARSE = 1;
static constexpr int E_FILE_LOAD = 2;
static constexpr int E_WINDOW_INITIALIZATION = 3;