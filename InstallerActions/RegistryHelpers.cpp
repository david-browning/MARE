#include "stdafx.h"
#include "RegistryHelpers.h"
#include "regutil.h"

static const auto REG_MARE_DIR_SUB_KEY = L"MARE_DIR";
static const std::wstring REG_PATH_SUB_KEY = L"Path";
static const auto REG_ENVI_SUB_KEY = TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\");
static constexpr DWORD GET_REG_FLAGS = RRF_RT_REG_EXPAND_SZ | RRF_RT_REG_SZ | RRF_NOEXPAND;

UINT AddMARE_DIRToEnvironmentPath()
{
	//Get the %MARE_DIR% value from the registry.
	TCHAR* regMAREDirValueData = nullptr;
	DWORD regMAREDirValueType;
	DWORD regMAREDirValueSize = 0;
	auto regRes = GetMAREDirValueFromReg(&regMAREDirValueData, &regMAREDirValueSize, &regMAREDirValueType);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	//Get the %PATH% value from the registry.
	TCHAR* regPathValueData = nullptr;
	DWORD regPathValueType;
	DWORD regPathValueSize = 0;
	regRes = GetPathValueFromReg(&regPathValueData, &regPathValueSize, &regPathValueType);
	if(regRes != ERROR_SUCCESS)
	{
		delete[] regMAREDirValueData;
		return regRes;
	}

	//Search the %PATH% to see if it contains the MARE_DIR value.
	std::wstring pathWString(regPathValueData);
	auto regMAREDirValuePositionInPath = pathWString.find(regMAREDirValueData);
	if(regMAREDirValuePositionInPath == pathWString.npos)
	{
		//Found the %MARE_DIR% value in %PATH%
		//Check if the %PATH% value ends with a semicolon.
		if(*(pathWString.end() - 1) != TEXT(';'))
		{
			//If it does not, add one.
			pathWString.append(TEXT(";"));
		}

		//Append the %MARE_DIR% value to %PATH%
		pathWString.append(regMAREDirValueData);

		HKEY enviKey;
		auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_WRITE, &enviKey);
		if(regRes != ERROR_SUCCESS)
		{
			return regRes;
		}

		//Put the updated version of %PATH% back into the registry.
		regRes = RegSetValueEx(enviKey, REG_PATH_SUB_KEY.c_str(), 0, regPathValueType,
			(BYTE*)pathWString.c_str(), pathWString.length() * sizeof(TCHAR));

		if(regRes != ERROR_SUCCESS)
		{
			MessageBox(nullptr, L"Could not write the new %path%", L"Error", MB_OK | MB_ICONERROR);
		}

		RegCloseKey(enviKey);
	}

	delete[] regMAREDirValueData;
	delete[] regPathValueData;
	return regRes;
}

UINT RemoveMARE_DIRFromEnvironmentPath()
{
	//Get the %MARE_DIR% value from the registry.
	TCHAR* regMAREDirValueData = nullptr;
	DWORD regMAREDirValueType;
	DWORD regMAREDirValueSize = 0;
	auto regRes = GetMAREDirValueFromReg(&regMAREDirValueData, &regMAREDirValueSize, &regMAREDirValueType);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	//This excludes the NULL character.
	auto numCharsToRemoveFromPathValue = wcslen(regMAREDirValueData);

	//Get the %PATH% value from the registry.
	TCHAR* regPathValueData = nullptr;
	DWORD regPathValueType;
	DWORD regPathValueSize = 0;
	regRes = GetPathValueFromReg(&regPathValueData, &regPathValueSize, &regPathValueType);
	if(regRes != ERROR_SUCCESS)
	{
		delete[] regMAREDirValueData;
		return regRes;
	}

	//Search the %PATH% to see if it contains the MARE_DIR value.
	std::wstring pathWString(regPathValueData);
	auto regMAREDirValuePositionInPath = pathWString.find(regMAREDirValueData);
	if(regMAREDirValuePositionInPath != pathWString.npos)
	{
		//Found the %MARE_DIR% value in %PATH%
		//Check if there is a semicolon before the %MARE_DIR% value.
		if(pathWString[regMAREDirValuePositionInPath - 1] == TEXT(';'))
		{
			//If there is, it must be erased too.
			//Move the iterator back by 1 character.
			regMAREDirValuePositionInPath--;

			//Increase the number of chars to remove by one.
			numCharsToRemoveFromPathValue++;
		}

		//Erase it the %MARE_DIR% value the %PATH%
		pathWString.erase(regMAREDirValuePositionInPath, numCharsToRemoveFromPathValue);

		HKEY enviKey;
		auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_WRITE, &enviKey);
		if(regRes != ERROR_SUCCESS)
		{
			return regRes;
		}

		//Put the updated version of %PATH% back into the registry.
		regRes = RegSetValueEx(enviKey, REG_PATH_SUB_KEY.c_str(), 0, regPathValueType,
			(BYTE*)pathWString.c_str(), pathWString.length() * sizeof(TCHAR));

		if(regRes != ERROR_SUCCESS)
		{
			MessageBox(nullptr, L"Could not write the new %path%", L"Error", MB_OK | MB_ICONERROR);
		}

		RegCloseKey(enviKey);
	}

	delete[] regMAREDirValueData;
	delete[] regPathValueData;
	return regRes;
}

UINT CreateMARE_DIRKey(const TCHAR* mareDir, DWORD mareDirLen)
{
	//Open the environment sub key
	HKEY enviKey;
	auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_WRITE, &enviKey);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	//Add the path to the mare compiler.
	regRes = RegSetValueEx(enviKey,
								  L"MARE_DIR",
								  0, REG_SZ, (BYTE*)mareDir, mareDirLen * sizeof(TCHAR));
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not set the value for %MARE_DIR%", L"Error", MB_OK | MB_ICONERROR);
	}

	RegCloseKey(enviKey);
	return regRes;
}

UINT RemoveMARE_DIRKey()
{
	//Open the environment sub key
	HKEY enviKey;
	auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_WRITE, &enviKey);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	regRes = RegDeleteValue(enviKey, REG_MARE_DIR_SUB_KEY);
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not remove the value for %MARE_DIR%", L"Error", MB_OK | MB_ICONERROR);
	}
	RegCloseKey(enviKey);
	return regRes;
}

UINT GetMAREDirValueFromReg(TCHAR** value_p,
									 DWORD* valueSizeLength_p,
									 DWORD* valueType_p)
{
	//Open the environment sub key
	HKEY enviKey;
	auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_QUERY_VALUE, &enviKey);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	//Get the size of the %MARE_DIR% value.
	regRes = RegGetValue(enviKey, nullptr, REG_MARE_DIR_SUB_KEY,
								GET_REG_FLAGS, valueType_p, nullptr, valueSizeLength_p);
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not get the size of the %MARE_DIR% value.", L"Error", MB_OK | MB_ICONERROR);
		RegCloseKey(enviKey);
		return regRes;
	}

	//Allocate memory for the MARE_DIR value and get it.
	*value_p = new TCHAR[*valueSizeLength_p];
	regRes = RegGetValue(enviKey, nullptr, REG_MARE_DIR_SUB_KEY,
								GET_REG_FLAGS, valueType_p, *value_p, valueSizeLength_p);
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not get %MARE_DIR% value.", L"Error", MB_OK | MB_ICONERROR);

		RegCloseKey(enviKey);
		delete[] * value_p;
		return regRes;
	}

	return regRes;
}

UINT GetPathValueFromReg(TCHAR** value_p,
								 DWORD* valueLengthBytes_p,
								 DWORD* valueType_p)
{
	//Open the environment sub key
	HKEY enviKey;
	auto regRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_ENVI_SUB_KEY, 0, KEY_QUERY_VALUE, &enviKey);
	if(regRes != ERROR_SUCCESS)
	{
		return regRes;
	}

	//Get the size of the %PATH% value.
	regRes = RegGetValue(enviKey, nullptr, REG_PATH_SUB_KEY.c_str(),
								GET_REG_FLAGS, valueType_p, nullptr, valueLengthBytes_p);
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not get the size of the %path% value.", L"Error", MB_OK | MB_ICONERROR);

		RegCloseKey(enviKey);
		return regRes;
	}

	//Allocate memory for %PATH% and get it.
	*value_p = new TCHAR[*valueLengthBytes_p];
	regRes = RegGetValue(enviKey, nullptr, REG_PATH_SUB_KEY.c_str(),
								GET_REG_FLAGS, valueType_p, *value_p, valueLengthBytes_p);
	if(regRes != ERROR_SUCCESS)
	{
		MessageBox(nullptr, L"Could not get %path% value.", L"Error", MB_OK | MB_ICONERROR);

		RegCloseKey(enviKey);
		delete[] * value_p;
		return regRes;
	}

	return regRes;
}
