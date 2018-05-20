#pragma once
#include "stdafx.h"

namespace msi_helpers
{

extern LIB_EXPORT UINT GetCustomActionData(MSIHANDLE msi, TCHAR** data_p, DWORD* dataSize_p);

}