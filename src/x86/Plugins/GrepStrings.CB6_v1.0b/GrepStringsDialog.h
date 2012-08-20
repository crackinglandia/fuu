/*
$Id: GrepStringsDialog.h 96 2010-09-19 19:27:20Z nahuelriva $

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

#ifndef GrepStringsDialogH
#define GrepStringsDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SDK\FUU_SDK.h"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Clipbrd.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TFormGrepStringsDialog : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog;
        TStatusBar *StatusBar;
        TTabControl *TabControl;
        TStringGrid *StringGrid;
        TEdit *EdStringSearch;
        TProgressBar *ProgressBar1;
        TCheckBox *CheckBContainString;
        TCheckBox *CheckBHexAdress;
        TLabel *LabelStringSearch;
        TPopupMenu *PopupMenu;
        TMenuItem *CopyText1;
        TMenuItem *SaveToFile1;
        TMenuItem *N1;
        TMenuItem *CopyAddress1;
        TMenuItem *CopyString1;
        TMenuItem *SaveAllToFile1;
        TSaveDialog *SaveDialog;
        TCheckListBox *CheckListBOptions;

        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall StatusBarDrawPanel(TStatusBar *StatusBar,
          TStatusPanel *Panel, const TRect &Rect);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall StringGridMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall CheckBHexAdressClick(TObject *Sender);
        void __fastcall EdStringSearchChange(TObject *Sender);
        void __fastcall CheckBContainStringClick(TObject *Sender);
        void __fastcall CopyText1Click(TObject *Sender);
        void __fastcall CopyAddress1Click(TObject *Sender);
        void __fastcall CopyString1Click(TObject *Sender);
        void __fastcall SaveToFile1Click(TObject *Sender);
        void __fastcall SaveAllToFile1Click(TObject *Sender);
        void __fastcall TabControlChange(TObject *Sender);


private:
        bool Executing;
        TStringList *ListASCII;
        TStringList *ListASCIIZ;
        TStringList *ListUNICODE;
        TStringList *ListALLSTRINGS;

        void __fastcall Add_StrsASCII(TObject * Sender, int n, int Offset, char * Str);
        void __fastcall Add_StrsASCIIZ(TObject * Sender, int n, int Offset, char * Str);
        void __fastcall Add_StrsUnicode(TObject * Sender, int n, int Offset, char * Str);
        void __fastcall SetControlOnStatusBar(TControl * Control, const TRect & Rect);
        void __fastcall SetControlOnStatusBar(TControl * Control, int nPanel, const TStatusBar * StatusB);
        void __fastcall ClearStringGrid(void);
        void __fastcall PutFileNameInCaption(AnsiString FileName);
        void __fastcall CreateStringListFormSelectRows(TStringList * List, int Alcance);

        int  __fastcall PutAllStringsInStringGrid(TStringList * ActiveList);
        int  __fastcall PutStringsInStringGrid(TStringList * ActiveList, AnsiString StrToSearch);
        void __fastcall SetActiveInStringGrid(void);

public:		// User declarations
       AnsiString InternalCaption;
       TExternalData  *DataOfFUU;
        __fastcall TFormGrepStringsDialog(TComponent* Owner);
       void __fastcall Execute(void);
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//extern PACKAGE TFormGrepStringsDialog *FormGrepStringsDialog;
//---------------------------------------------------------------------------
#endif
