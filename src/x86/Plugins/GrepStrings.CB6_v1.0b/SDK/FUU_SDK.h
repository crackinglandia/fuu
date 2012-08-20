//---------------------------------------------------------------------------

#ifndef FUU_SDKH
#define FUU_SDKH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
typedef struct
{
  AnsiString  Target_Filename; // File
  HWND        hFUU;            // Handle de FUU
  DWORD       lpOptionsArray;
  DWORD       lpReserved;
  DWORD       lpParam;
}TExternalData, *pTExternalData;

//---------------------------------------------------------------------------
#endif
