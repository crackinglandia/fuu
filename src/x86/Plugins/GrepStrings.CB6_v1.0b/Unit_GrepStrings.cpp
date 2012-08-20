/*
$Id: Unit_GrepStrings.cpp 96 2010-09-19 19:27:20Z nahuelriva $

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


#pragma hdrstop

#include "Unit_GrepStrings.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TGrepStrings::TGrepStrings(AnsiString FileName)
{
        //TODO: Add your source code here
  int i;
  FFileName=FileName;
  FStringsFound=0;
  FStringsZFound=0;
  FMinStrLen=3;
  FOnFoundAsciiStr=NULL;
  FOnFoundAsciiZStr=NULL;
  FIncludeSpanish=false;
  setmem(FCharacters, 256, 0);
  for (i=32; i<127; i++)
       FCharacters[i]=1;
}
//---------------------------------------------------------------------------
__fastcall TGrepStrings::~TGrepStrings()
{
        //TODO: Add your source code here
  if (pszBuffer)
    {
      delete[] pszBuffer;
      //delete pszBuffer;
    }
}
//---------------------------------------------------------------------------
void __fastcall TGrepStrings::SetMinStrLen(int value)
{
        if(FMinStrLen != value) {
                FMinStrLen = value;
        }
}
//---------------------------------------------------------------------------
void __fastcall TGrepStrings::SetIncludeSpanish(bool value)
{
   if (FIncludeSpanish != value)
     {
       FIncludeSpanish = value;
       FCharacters['Ñ']= value;
       FCharacters['ñ']= value;
     }
}
//---------------------------------------------------------------------------
bool __fastcall TGrepStrings::IsValidAsciiCh(char Ch)
{
        //TODO: Add your source code here

  if ( (Ch>31 ) && (Ch<127) )
      return true;

  if ( (FIncludeSpanish==true) &&
       ((Ch=='ñ') || (Ch=='Ñ')) )
        return true;
//if (FCharacters[Ch]==1)
//      return true;
 return false;
}
//---------------------------------------------------------------------------
bool __fastcall TGrepStrings::OpenAndLoadFile(void)
{
        //TODO: Add your source code here
  int iFileHandle;
  int iFileLength;

    pszBuffer=NULL;
    try
    {
      iFileHandle = FileOpen(FFileName, fmOpenRead|fmShareDenyNone);
      iFileLength = FileSeek(iFileHandle,0,2);
      FileSeek(iFileHandle,0,0);
      pszBuffer = new char[iFileLength+1];
      iBytesRead = FileRead(iFileHandle, pszBuffer, iFileLength);
      FileClose(iFileHandle);
      return true;
    }
    catch(...)
    {
      MessageBox(0, "No puedo Abrir el archivo ", "Error", MB_OK);
    }
  return false;
}
//---------------------------------------------------------------------------
int __fastcall TGrepStrings::GrepAsciiSrings(void)
{
        //TODO: Add your source code here
 int i, n;
 char ch;
 char Buffer[defMax_Str_Suported+1];

 if (OpenAndLoadFile()==false) return -1;

 setmem(Buffer, defMax_Str_Suported, 0); // Limpiar el Buffer.
 for (i=0, n=0; i<iBytesRead; i++)
   {
        ch=pszBuffer[i];
        if ( IsValidAsciiCh(ch) )
          {
            Buffer[n]=ch;              // Añadirlo a la cadena.
            n++;                       // Siguiente Caracter.
          }
        else
          {
            if (n>=FMinStrLen)
              {
                // Terminar cadena, checar tamaño minitmo y guardar.
                Buffer[n]=0; // Añadir el terminador de la cadena.
                FStringsFound++;      // Encontrado
                if (FOnFoundAsciiStr) // Activar evento.
                    FOnFoundAsciiStr(this, FStringsFound, i-strlen(Buffer), Buffer);
                setmem(Buffer, defMax_Str_Suported, 0); // Reiniciar Buffer.
              }
            else
                setmem(Buffer, n, 0); // Reiniciar Buffer.
             n=0; // Reiniciar la busqueda de cadena.
          }
   }
 return FStringsFound; // Numero de cadenas encontradas.
}
//---------------------------------------------------------------------------
int __fastcall TGrepStrings::GrepAsciiZSrings(void)
{
        //TODO: Add your source code here
 int i, n;
 char ch;
 char Buffer[defMax_Str_Suported+1];

 if (OpenAndLoadFile()==false) return -1;

 setmem(Buffer, defMax_Str_Suported, 0); // Limpiar el Buffer.
 for (i=0, n=0; i<iBytesRead; i++)
   {
        ch=pszBuffer[i];
        if (IsValidAsciiCh(ch))
          {
            Buffer[n]=ch;              // Añadirlo a la cadena.
            n++;                       // Siguiente Caracter.
          }
        if (ch==0)
          {
            // Terminar cadena, checar tamaño minitmo y guardar.
            Buffer[n]=ch; // Añadir el terminador de la cadena.
            if ((int)strlen(Buffer)>=FMinStrLen)  // Si es de longitud minima, añadir
              {
                FStringsZFound++;      // Encontrado
                if (FOnFoundAsciiZStr) // Activar evento.
                    FOnFoundAsciiZStr(this, FStringsZFound, i-strlen(Buffer), Buffer);
              }
            setmem(Buffer, defMax_Str_Suported, 0); // Reiniciar Buffer.
            n=0; // Reiniciar la busqueda de cadena.
          }
   }
 return FStringsZFound; // Numero de cadenas encontradas.
}
//---------------------------------------------------------------------------
int __fastcall TGrepStrings::GrepUnicodeSrings(void)
{
        //TODO: Add your source code here
 int i, len;
 char ch;
 char Buffer[defMax_Str_Suported+1];

 if (OpenAndLoadFile()==false) return -1;

 setmem(Buffer, defMax_Str_Suported, 0); // Limpiar el Buffer.
 for (i=0; i<iBytesRead; i++)
   {
        ch=pszBuffer[i];

        if (ch==0)
          {
            if ( (IsValidAsciiCh(pszBuffer[i-1])) && (IsValidAsciiCh(pszBuffer[i+1])) )
              {
                // Pescar la cadena Unicode
                i--;
                i=PescarUnicode(i, Buffer);
                len=strlen(Buffer);
                if (len>=FMinStrLen)  // Si es de longitud minima, añadir
                  {
                    FStringsUnicodeFound++;      // Encontrado
                    if (FOnFoundUnicodeStr) // Activar evento.
                        FOnFoundUnicodeStr(this, FStringsUnicodeFound, i-(len*2), Buffer);
                 }
                setmem(Buffer, defMax_Str_Suported, 0); // Reiniciar Buffer.
              }
          }
   }
 return FStringsUnicodeFound; // Numero de cadenas encontradas.
}
//---------------------------------------------------------------------------
int __fastcall TGrepStrings::PescarUnicode(int Index, char * Buffer)
{
        //TODO: Add your source code here
 int i;
 char ch;
 for (i=0; Index<iBytesRead; Index++)
   {
     ch=pszBuffer[Index];
     if ( (IsValidAsciiCh(ch)==true) && (pszBuffer[Index+1]==0) )
        {
          Buffer[i]=ch;
          i++;
          Index++; // Saltar el 0.
        }
     else
        break;
   }
 Buffer[i]=0; // Añadimos el Terminador  
 return Index;
}
//---------------------------------------------------------------------------
