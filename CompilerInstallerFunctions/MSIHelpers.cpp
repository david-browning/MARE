#include "stdafx.h"
#include "MSIHelpers.h"

UINT msi_helpers::GetCustomActionData(MSIHANDLE msi, TCHAR** data_p, DWORD* dataSize_p)
{
	*dataSize_p = 0;
	auto ret = MsiGetProperty(msi, L"CustomActionData", const_cast<LPWSTR>(L""), dataSize_p);
	if(ret == ERROR_MORE_DATA)
	{
		(*dataSize_p)++;
		*data_p = new TCHAR[*dataSize_p];

		ret = MsiGetProperty(msi, L"CustomActionData", *data_p, dataSize_p);
		if(ret != ERROR_SUCCESS)
		{
			//Something went wrong.
			return ret;
		}

		return ret;
	}
	else
	{
		//Invalid handle or invalid parameter.
		return ret;
	}
}
