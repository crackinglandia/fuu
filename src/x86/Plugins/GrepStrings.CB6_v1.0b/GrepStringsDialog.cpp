/*
$Id: GrepStringsDialog.cpp 96 2010-09-19 19:27:20Z nahuelriva $

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
#pragma hdrstop
#include <stdio.h>
#include "FUU_SDK.h"
#include "Unit_GrepStrings.h"
#include "GrepStringsDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TFormGrepStringsDialog *FormGrepStringsDialog;
#define defALL     0
#define defADDRESS 1
#define defSTRING  2
//---------------------------------------------------------------------------
__fastcall TFormGrepStringsDialog::TFormGrepStringsDialog(TComponent* Owner)
        : TForm(Owner)
{
  BorderStyle=bsDialog;
  Position=poDesktopCenter;
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::FormCreate(TObject *Sender)
{
 DataOfFUU=NULL;
 Executing=false;
 Caption="Standar Dialog for FUU";
 SetControlOnStatusBar(CheckBContainString, 0, StatusBar);
 SetControlOnStatusBar(CheckBHexAdress, 1, StatusBar);
// SetControlOnStatusBar(ProgressBar1, 2, StatusBar);

 StringGrid->Cells[0][0]="Num";
 StringGrid->Cells[1][0]="Offset";
 StringGrid->Cells[2][0]="String";
 StringGrid->ColWidths[2]=1800;
 StringGrid->Font->Name="Courier New";

 ListASCII      = new TStringList();
 ListASCIIZ     = new TStringList();
 ListUNICODE    = new TStringList();
 ListALLSTRINGS = new TStringList();

}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if (ListASCII)      delete ListASCII;
  if (ListASCIIZ)     delete ListASCIIZ;
  if (ListUNICODE)    delete ListUNICODE;
  if (ListALLSTRINGS) delete ListALLSTRINGS;
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::FormShow(TObject *Sender)
{
   PutFileNameInCaption(DataOfFUU->Target_Filename);
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::StatusBarDrawPanel(TStatusBar *StatusBar,
      TStatusPanel *Panel, const TRect &Rect)
{
  switch (Panel->Index)
  {
    case 0: SetControlOnStatusBar(CheckBContainString, Rect); break;
    case 1: SetControlOnStatusBar(CheckBHexAdress, Rect); break;
//    case 2: SetControlOnStatusBar(ProgressBar1, Rect); break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::SetControlOnStatusBar(TControl * Control, const TRect & Rect)
{
#define MARGEN 1
        //TODO: Add your source code here
     Control->Left=Rect.Left+MARGEN;
     Control->Top=Rect.Top+MARGEN;
     Control->Height=(Rect.Bottom-Rect.Top)-(2*MARGEN);
     Control->Width =(Rect.Right-Rect.Left)-(2*MARGEN);
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::SetControlOnStatusBar(TControl * Control, int nPanel, const TStatusBar * StatusB)
{
        //TODO: Add your source code here
 Control->Parent=StatusBar;
 StatusB->Panels->Items[nPanel]->Style=psOwnerDraw;
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::ClearStringGrid(void)
{
        //TODO: Add your source code here
 StringGrid->RowCount=2;
 for (int j=0; j<3; j++)
   StringGrid->Cells[j][1]="";
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::PutFileNameInCaption(AnsiString FileName)
{
        //TODO: Add your source code here
  if (DataOfFUU==NULL)   return;
  if (DataOfFUU->Target_Filename != "")
      Caption = InternalCaption + " - [ "+ ExtractFileName(FileName) +" ]";
}

//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::Add_StrsASCII(TObject * Sender, int n, int Offset, char * Str)
{
        //TODO: Add your source code here
 char Buffer[1023+1];
 sprintf(Buffer, "%08d:%s", Offset, Str);
 ListASCII->Add(Buffer);
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::Add_StrsASCIIZ(TObject * Sender, int n, int Offset, char * Str)
{
        //TODO: Add your source code here
 char Buffer[1023+1];
 sprintf(Buffer, "%08d:%s", Offset, Str);
 ListASCIIZ->Add(Buffer);
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::Add_StrsUnicode(TObject * Sender, int n, int Offset, char * Str)
{
        //TODO: Add your source code here
 char Buffer[1023+1];
 sprintf(Buffer, "%08d:%s", Offset, Str);
 ListUNICODE->Add(Buffer);
}
//---------------------------------------------------------------------------
int __fastcall TFormGrepStringsDialog::PutAllStringsInStringGrid(TStringList * ActiveList)
{
        //TODO: Add your source code here
 int i, Pos;
 AnsiString Full, Address, Str;
 
 if (ActiveList->Count==0) return 0;
 ClearStringGrid();
 StringGrid->RowCount=ActiveList->Count+1;
 for (i=0; i<ActiveList->Count; i++)
  {
    Full=ActiveList->Strings[i];
    Pos=Full.Pos(":");
    Address=Full.SubString(0, Pos-1).TrimRight();
    Str    =Full.SubString(Pos+1, Full.Length()-Pos).Trim();
    StringGrid->Cells[0][i+1]=i+1;
    if (CheckBHexAdress->Checked==true)
        StringGrid->Cells[1][i+1]=IntToHex(StrToInt(Address), 8);
    else
        StringGrid->Cells[1][i+1]=Address;
    StringGrid->Cells[2][i+1]=Str;
  }
 StatusBar->Panels->Items[2]->Text=" Count = "+ IntToStr(i);
 return i;
}
//---------------------------------------------------------------------------
int __fastcall TFormGrepStringsDialog::PutStringsInStringGrid(TStringList * ActiveList, AnsiString StrToSearch)
{
        //TODO: Add your source code here
 int i, j, Pos;
 AnsiString Full, Address, Str;
// StringGrid->Rows->BeginUpdate();
 ClearStringGrid();
 if (ActiveList==NULL) return 0;
 if (ActiveList->Count==0) return 0;
 for (i=0, j=1; i<ActiveList->Count; i++)
  {
    Full=ActiveList->Strings[i];
    Pos=Full.Pos(":");
    Address=Full.SubString(0, Pos-1).TrimRight();
    Str    =Full.SubString(Pos+1, Full.Length()-Pos).Trim();

//    if (StrToSearch!="")
      {
        Pos=Str.Pos(StrToSearch);
        if (CheckBContainString->Checked==true) // Si puede estar en cualquier lugar
          {
            if (Pos==0) continue;   // No la contiene, continuar.
          }
        else
          {  // Tiene que estar al principio de la cadena
            if (Pos !=1) continue; // No fue al principio, continuar.
          }
      }
    StringGrid->RowCount=j+1;
    StringGrid->Cells[0][j]=j;
    if (CheckBHexAdress->Checked==true)
        StringGrid->Cells[1][j]=IntToHex(StrToInt(Address), 8);
    else
        StringGrid->Cells[1][j]=Address;
    StringGrid->Cells[2][j]=Str;
    j++;
  }
 StatusBar->Panels->Items[2]->Text=" Count = "+ IntToStr(j-1) + " of " + IntToStr(i);
 return j-1;
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::SetActiveInStringGrid(void)
{
        //TODO: Add your source code here
  AnsiString StrToSearch=EdStringSearch->Text;

  if (Executing==false) return;

  if (StrToSearch=="")
    {
      switch (TabControl->TabIndex)
      {
         case 0: PutAllStringsInStringGrid(ListASCII); break;
         case 1: PutAllStringsInStringGrid(ListASCIIZ); break;
         case 2: PutAllStringsInStringGrid(ListUNICODE); break;
//        case 3: PutAllStringsInStringGrid(ListALLSTRINGS); break;
      }
    }
  else
   {
        switch (TabControl->TabIndex)
        {
          case 0: PutStringsInStringGrid(ListASCII, StrToSearch); break;
          case 1: PutStringsInStringGrid(ListASCIIZ, StrToSearch); break;
          case 2: PutStringsInStringGrid(ListUNICODE, StrToSearch); break;
//        case 3: PutStringsInStringGrid(ListALLSTRINGS, StrToSearch); break;
        }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::StringGridMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
 int Column, Row;
  if (Executing==false) return;
  StringGrid->MouseToCell(X, Y, Column, Row);
  if (Column==2)
      ((TStringGrid*)Sender)->Hint = ((TStringGrid*)Sender)->Cells[Column][Row];
  else
      ((TStringGrid*)Sender)->Hint = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::TabControlChange(TObject *Sender)
{
 if (Executing==false) return;
 SetActiveInStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CheckBHexAdressClick(
      TObject *Sender)
{
 if (Executing==false) return;
 SetActiveInStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CheckBContainStringClick(
      TObject *Sender)
{
 if (Executing==false) return;
 SetActiveInStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::EdStringSearchChange(
      TObject *Sender)
{
  if (Executing==false) return;
  SetActiveInStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CreateStringListFormSelectRows(TStringList * List, int Alcance)
{
        //TODO: Add your source code here
  int i;
  AnsiString Str;
  int FirstRow=StringGrid->Selection.Top;
  int LastRow=StringGrid->Selection.Bottom;

  if (List==NULL) return;
  for (i=FirstRow; i<=LastRow; i++)
   {
      switch (Alcance)
      {
        case defALL:     Str=StringGrid->Cells[1][i]+":"+StringGrid->Cells[2][i]; break;
        case defADDRESS: Str=StringGrid->Cells[1][i]; break;
        case defSTRING:  Str=StringGrid->Cells[2][i]; break;
      }
      List->Add(Str);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CopyText1Click(TObject *Sender)
{
  // Copiar el los renglones seleccionados - All Text.
 TStringList *List = new TStringList();
 if (List)
   {
     CreateStringListFormSelectRows(List, defALL);
     Clipboard()->AsText=List->Text;
     delete List;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CopyAddress1Click(TObject *Sender)
{
  // Copiar el los renglones seleccionados - Solo la Direccion.
 TStringList *List = new TStringList();
 if (List)
   {
     CreateStringListFormSelectRows(List, defADDRESS);
     Clipboard()->AsText=List->Text;
     delete List;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::CopyString1Click(TObject *Sender)
{
  // Copiar el los renglones seleccionados - Solo el String.
 TStringList *List = new TStringList();
 if (List)
   {
     CreateStringListFormSelectRows(List, defSTRING);
     Clipboard()->AsText=List->Text;
     delete List;
   }  
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::SaveToFile1Click(TObject *Sender)
{
  // Salvar los renglones seleccionados a un archivo.
 TStringList *List = new TStringList();
 if (List)
   {
     CreateStringListFormSelectRows(List, defALL);
     if (SaveDialog->Execute())
         List->SaveToFile(SaveDialog->FileName);
     delete List;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::SaveAllToFile1Click(
      TObject *Sender)
{
  // Salvar los Todos los renglones a un archivo.
 TStringList *List = new TStringList();
 AnsiString Str;
 int i;
 if (List)
   {
     for (i=1; i<StringGrid->RowCount; i++)
     {
       Str=StringGrid->Cells[1][i]+":"+StringGrid->Cells[2][i];
       List->Add(Str);
     }
     if (SaveDialog->Execute())
         List->SaveToFile(SaveDialog->FileName);
     delete List;
  }
}
//--------------------------------------------------------------------------
void __fastcall TFormGrepStringsDialog::Execute(void)
{
        //TODO: Add your source code here
 TGrepStrings  *T;

 Executing=false; 
// ClearStringGrid();
 ListASCII->Clear();
 ListASCIIZ->Clear();
 ListUNICODE->Clear();
 ListALLSTRINGS->Clear();
 EdStringSearch->Text="";
 EdStringSearch->Enabled=true;
 CheckBContainString->Enabled=true;

 PutFileNameInCaption(DataOfFUU->Target_Filename);

 T= new TGrepStrings(DataOfFUU->Target_Filename);   // Ok!!

 if (T)
   {
     T->OnFoundAsciiStr   =Add_StrsASCII;
     T->OnFoundAsciiZStr  =Add_StrsASCIIZ;
     T->OnFoundUnicodeStr =Add_StrsUnicode;

     T->GrepAsciiSrings();
     T->GrepAsciiZSrings();
     T->GrepUnicodeSrings();

     Executing=true;

//     PutStringsInStringGrid(ListASCII, "");
     SetActiveInStringGrid();
//     EdStringSearch->SetFocus();
     delete T;
     this->ShowModal(); // Ok!!
   }
}
//---------------------------------------------------------------------------

