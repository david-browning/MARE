#pragma once
#include "stdafx.h"

namespace reg_edit
{
	extern UINT AddMARE_DIRToEnvironmentPath();

	extern UINT RemoveMARE_DIRFromEnvironmentPath();

	extern UINT CreateMARE_DIRKey(const TCHAR* mareDir, DWORD mareDirLen);

	extern UINT RemoveMARE_DIRKey();

	extern UINT GetMAREDirValueFromReg(TCHAR** value_p,
												  DWORD* valueSizeLength_p,
												  DWORD* valueType_p);

	extern UINT GetPathValueFromReg(TCHAR** value_p,
											  DWORD* valueSizeLength_p,
											  DWORD* valueType_p);

	inline void BroadcastSettingsChangedMessage()
	{
		SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (WPARAM)L"Environment", SMTO_ABORTIFHUNG, 5000, nullptr);
	}
}