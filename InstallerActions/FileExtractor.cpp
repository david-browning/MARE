#include "stdafx.h"
#include "FileExtractor.h"

bool ExtractResource(const HINSTANCE hInstance, WORD resourceID, LPCWSTR szOutputFilename)
{
	HRSRC resourceHandle = FindResourceW(hInstance, MAKEINTRESOURCE(resourceID), TEXT("VSIX"));
	HGLOBAL fileResourceHandle = LoadResource(hInstance, resourceHandle);

	LPVOID file = LockResource(fileResourceHandle);
	DWORD fileSize = SizeofResource(hInstance, resourceHandle);

	HANDLE fileHandle = CreateFile(szOutputFilename, GENERIC_READ | GENERIC_WRITE, 0, 
											 nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	HANDLE fileMap = CreateFileMapping(fileHandle, nullptr, PAGE_READWRITE, 0, fileSize, NULL);
	LPVOID baseAddress = MapViewOfFile(fileMap, FILE_MAP_WRITE, 0, 0, 0);


	// Write the fileCopyMemory(lpBaseAddress, lpFile, dwSize);

	// Unmap the file and close the handles




	UnmapViewOfFile(baseAddress);
	CloseHandle(fileMap);
	CloseHandle(fileHandle);

	return 0;
}
