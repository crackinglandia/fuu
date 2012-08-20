/*
$Id: Unit_GrepStrings.h 96 2010-09-19 19:27:20Z nahuelriva $

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

#ifndef Unit_GrepStringsH
#define Unit_GrepStringsH
//---------------------------------------------------------------------------

#include <Classes.hpp>
//---------------------------------------------------------------------------

#define defMax_Str_Suported 1023

typedef void __fastcall (__closure *TFoundGrepEvent) (TObject *Sender, int n, int Offset, char *Str);
//---------------------------------------------------------------------------


class PACKAGE TGrepStrings : public TObject
{
private:
        AnsiString      FFileName;
        char *pszBuffer;
        int iBytesRead;                
        int FMinStrLen;
        int FStringsFound;
        int FStringsZFound;
        int FStringsUnicodeFound;
        bool FIncludeSpanish;
        char FCharacters [256];

        TFoundGrepEvent FOnFoundAsciiStr;
        TFoundGrepEvent FOnFoundAsciiZStr;
        TFoundGrepEvent FOnFoundUnicodeStr;

        bool __fastcall OpenAndLoadFile   (void);
        void __fastcall SetMinStrLen      (int value);
        void __fastcall SetIncludeSpanish (bool value);
        bool __fastcall IsValidAsciiCh    (char Ch);
        int  __fastcall PescarUnicode     (int Index, char * Buffer);

protected:

public:
        __fastcall  TGrepStrings(AnsiString FileName);
        __fastcall ~TGrepStrings();
        int __fastcall GrepAsciiSrings(void);
        int __fastcall GrepAsciiZSrings(void);
        int __fastcall GrepUnicodeSrings(void);

        __property int  MinStrLen       = { read=FMinStrLen, write=SetMinStrLen };
        __property bool IncludeSpanish  = { read=FIncludeSpanish, write=SetIncludeSpanish };
        __property int  StringsFound    = { read=FStringsFound };

        __property TFoundGrepEvent OnFoundAsciiStr    = { read=FOnFoundAsciiStr,   write=FOnFoundAsciiStr };
        __property TFoundGrepEvent OnFoundAsciiZStr   = { read=FOnFoundAsciiZStr,  write=FOnFoundAsciiZStr };
        __property TFoundGrepEvent OnFoundUnicodeStr  = { read=FOnFoundUnicodeStr, write=FOnFoundUnicodeStr };


//__published:
//	__property TFoundDirEvent  OnFindDir  = {read=FOnFoundDir,  write=FOnFoundDir};

};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
 