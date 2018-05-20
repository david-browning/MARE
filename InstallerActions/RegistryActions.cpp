#include "stdafx.h"
#include "MSIHelpers.h"
#include "RegistryHelpers.h"
#include "RegistryActions.h"

static const wchar_t* REMOVE_MESSAGE_TITLE = L"Remove Error";
static const wchar_t* INSTALL_MESSAGE_TITLE = L"Install Error";

std::wstring GetCannotGetCustomDataMessage(UINT ret)
{
	std::wstringstream m;
	m << L"Could not get the data passed to this action.\nError code is " << ret << L".";
	return std::wstring(m.str());
}

std::wstring GetCannotCreateKeyMessage(UINT ret)
{
	std::wstringstream m;
	m << L"Could not create the MARE_DIR value in the registry.\n"
		"Error code is " << ret << ".";
	return std::wstring(m.str());
}

std::wstring GetCannotRemoveKeyMessage(UINT ret)
{
	std::wstringstream m;
	m << L"Could not remove MARE from the registry."
		"There is an orphaned value now in the \"Environment\" key.\n"
		"Error code is " << ret << ".";
	return std::wstring(m.str());
}

std::wstring GetCannotUpdatePathMessage(UINT ret)
{
	std::wstringstream m;
	m << L"Cannot udpate the %path% value.\n"
		"Error code is " << ret << ".";
	return std::wstring(m.str());
}

UINT __stdcall AddToPath(MSIHANDLE hInstall)
{
	HRESULT hr = S_OK;
	UINT er = ERROR_SUCCESS;

	hr = WcaInitialize(hInstall, "AddToPath");
	ExitOnFailure(hr, "Failed to initialize");

	WcaLog(LOGMSG_STANDARD, "Initialized.");


	DWORD customActionDataSize = 0;
	TCHAR* customActionData = nullptr;

	auto ret = GetCustomActionData(hInstall, &customActionData, &customActionDataSize);
	if(ret != ERROR_SUCCESS)
	{
		MessageBox(nullptr, GetCannotGetCustomDataMessage(ret).c_str(), INSTALL_MESSAGE_TITLE,
					  MB_OK | MB_ICONERROR);
		return ret;
	}

	ret = CreateMARE_DIRKey(customActionData, customActionDataSize);
	if(ret != ERROR_SUCCESS)
	{
		MessageBox(nullptr, GetCannotCreateKeyMessage(ret).c_str(),
					  INSTALL_MESSAGE_TITLE, MB_OK | MB_ICONERROR);
		return ret;
	}

	ret = AddMARE_DIRToEnvironmentPath();
	if(ret != ERROR_SUCCESS)
	{
		MessageBox(nullptr, GetCannotUpdatePathMessage(ret).c_str(),
					  INSTALL_MESSAGE_TITLE, MB_OK | MB_ICONWARNING);
		return ret;
	}

	//Notify the system that the environment has changed.
	BroadcastSettingsChangedMessage();

	LExit:
	er = SUCCEEDED(hr) ? ERROR_SUCCESS : ERROR_INSTALL_FAILURE;
	return WcaFinalize(er);
}

UINT __stdcall RemoveFromPath(MSIHANDLE hInstall)
{
	HRESULT hr = S_OK;
	UINT er = ERROR_SUCCESS;

	hr = WcaInitialize(hInstall, "RemoveFromPath");
	ExitOnFailure(hr, "Failed to initialize");

	WcaLog(LOGMSG_STANDARD, "Initialized.");

	//Remove the %MARE_DIR% value from %PATH%.
	//This function uses the value in %MARE_DIR%.
	//This function must be called before removing %MARE_DIR%.
	auto ret = RemoveMARE_DIRFromEnvironmentPath();
	if(ret != ERROR_SUCCESS)
	{
		MessageBox(nullptr, GetCannotUpdatePathMessage(ret).c_str(),
					  REMOVE_MESSAGE_TITLE, MB_OK | MB_ICONWARNING);
		//return ret;
	}

	//Remove %MARE_DIR% from the registry.
	ret = RemoveMARE_DIRKey();
	if(ret != ERROR_SUCCESS)
	{
		MessageBox(nullptr, GetCannotRemoveKeyMessage(ret).c_str(),
					  REMOVE_MESSAGE_TITLE, MB_OK | MB_ICONWARNING);
		//return ret;
	}

	//Notify the system that the environment has changed.
	BroadcastSettingsChangedMessage();

	LExit:
	er = SUCCEEDED(hr) ? ERROR_SUCCESS : ERROR_INSTALL_FAILURE;
	return WcaFinalize(er);
}