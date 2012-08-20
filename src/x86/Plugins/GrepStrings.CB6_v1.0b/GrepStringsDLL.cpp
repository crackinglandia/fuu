/*
$Id: GrepStringsDLL.cpp 96 2010-09-19 19:27:20Z nahuelriva $

GrepString plugin for FUU v1.0

Copyright (C) 2010 +NCR/CRC! [ReVeRsEr] http://crackinglandia.blogspot.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Author: Zapper

*/

//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "GrepStringsDLL.h"
#include "GrepStringsDialog.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
/*
 *  Blank Plugin skeleton -- Version 1.0 -- By Zapper
 *  Conversion to C++ Builder By Zapper Zaku -
 *
 */
// --------------------------------------------------------------------------



// Variables Globales y Constantes
// The name that shows-up in FUU's list of plugins
char          *PluginName = "Grep Strings v1.0b [Only for FUU v1.1b]";

TExternalData  *DataOfFUU;
TFormGrepStringsDialog *Dialog;
//---------------------------------------------------------------------------
void ShowDialog(void)
{
    // Put your code here, and in Form1.create as usual
    Dialog= new TFormGrepStringsDialog(NULL);
    try{

      Dialog->DataOfFUU=DataOfFUU;
      Dialog->InternalCaption="Grep Strings v1.0b";
      //Dialog->ShowModal();
      Dialog->Execute();
    }
    __finally{
      Dialog->Free();  //<-- Probaremos con esta.
    }
};
// --------------------------------------------------------------------------
char * WINAPI GetPluginName(void)
{
  return PluginName;
};
// --------------------------------------------------------------------------
void WINAPI DoUnpack(HWND hMainDlg, char *szFname, DWORD lpOptionsArray, DWORD lpReserved, DWORD lpParam)
{
  // Guard against errors
  try{
    DataOfFUU = new TExternalData();
    DataOfFUU->hFUU=hMainDlg;
    DataOfFUU->Target_Filename=szFname;
    DataOfFUU->lpOptionsArray=lpOptionsArray;
    DataOfFUU->lpReserved=lpReserved;
    DataOfFUU->lpParam=lpParam;

    ShowDialog();
  }
  __finally // in case of error...
  {
  };
};
// --------------------------------------------------------------------------


// DLL Main
#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
        return 1;
}
//---------------------------------------------------------------------------
 