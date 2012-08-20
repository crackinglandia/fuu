/*
$Id: GrepStringsDLL.h 96 2010-09-19 19:27:20Z nahuelriva $

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

#ifndef GrepStringsDLLH
#define GrepStringsDLLH

// Declaraciones de Macros para facilitar la vida.
#ifdef _DLLMACRO
	#define DllExport extern "C" __declspec( dllexport )
#else
	#define DllExport extern "C" __declspec( dllexport )
#endif

#define _DLLEXPORT_(Type) extern "C" __declspec( dllexport ) Type WINAPI
//--------------------------------------------------------------------------



//Funciones Internas de la DLL
void ShowDialog(void);
//--------------------------------------------------------------------------

// Funciones exportadas para PlugIns de PEiD
DllExport void WINAPI DoUnpack (HWND hMainDlg, char *szFname, DWORD lpOptionsArray, DWORD lpReserved, DWORD lpParam);
DllExport LPSTR WINAPI GetPluginName ();
//--------------------------------------------------------------------------

#endif
