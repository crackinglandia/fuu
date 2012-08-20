; $Id: FUU.Inc 85 2010-07-27 15:26:16Z guan.dedio@gmail.com $

include Alt_IF_en.mac
include x64calling.inc
include WINDOWS.INC

include kernel32.inc
include user32.inc
include Comctl32.inc
include comdlg32.inc
include shell32.inc
include gdi32.inc

includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
includelib shell32.lib
includelib ComDlg32.Lib
includelib Gdi32.Lib

; ************   Prototipos ****************
funcproto local,DlgProc,HWND,UINT,WPARAM,LPARAM
funcproto LOCAL,Init,HWND,UINT,LPARAM,LPARAM

funcproto LOCAL,GetHandlesOfControls,HWND
funcproto LOCAL,GetFileDialog

funcproto LOCAL,GetStructPtr,QWORD,QWORD
funcproto LOCAL,InitializeUnpacker,HWND,QWORD,QWORD
funcproto LOCAL,RefreshComboBox
funcproto LOCAL,AddElementToList,QWORD,QWORD
funcproto LOCAL,IsElementInList,QWORD,QWORD
funcproto LOCAL,GetElementFromList,QWORD,QWORD
funcproto LOCAL,GetNumberOfItems,QWORD
funcproto LOCAL,PopulateList,QWORD
funcproto LOCAL,DetectCryptoSignatures,HWND,QWORD,QWORD
funcproto LOCAL,DetectOEP,HWND,QWORD,QWORD
funcproto LOCAL,GenericUnpacker,HWND,QWORD,QWORD
funcproto LOCAL,IdentifyPackerOrCompiler,HWND,QWORD,QWORD
funcproto LOCAL,DoJob,HWND,QWORD,QWORD
funcproto LOCAL,FreeString,QWORD
funcproto LOCAL,LoadPlugins,HWND,UINT,WPARAM,LPARAM

funcproto LOCAL,IsFile64Bits,QWORD
funcproto LOCAL,GetItemByIndex,QWORD
funcproto LOCAL,InsertItemInList,QWORD,QWORD
funcproto LOCAL,DestroyHandles
;*********** Macros *****************
chr$ MACRO any_text:VARARG
LOCAL txtname
.data
  txtname db any_text,0
.code
EXITM <addr txtname>
ENDM
;******************************************

;Revisar es posible que algo cambie a QWORD
PluginInfo STRUCT
	_Index			dq ?   ; se añade un guion para evitar probemas del compilador con otras variables Index en declaraciones de prototipos, ... 
	DoUnpackAddr	dq ?
	GetPlugNameAddr	dq ?
	DllName			db MAX_PATH dup(?)
	PluginName 		db MAX_PATH dup(?)
PluginInfo ENDS




.const


IDM_MENU				equ 10000
IDM_FILE_EXIT			equ 10001
IDM_HELP_ABOUT			equ 10101
IDM_TOOLS_CRYPTSIGN 	equ 10003
IDM_TOOLS_DETECTOEP 	equ 10002
IDM_GENUNPACK			equ 10004
IDM_IDENTIFY_SIGNATURE 	equ 10005
IDM_HELP_SUPPORT		equ 10006
IDM_HELP_HOME			equ 10007

IDD_DIALOG1			equ 101
FileNameEdit		equ 1001
ExitBtn				equ 1007
AboutBtn			equ 1006
UnpackBtn			equ 1003
PluginComboBox		equ 1008
BrowseFileBtn		equ 1005
OutputListBox		equ 1004
RealignPECheckBox	equ 1012
CopyOverlayDataBt	equ 1014
RefreshBtn			equ 1010
BlogLinkEdit		equ 1011
BlogLinkClickable	equ 1013
EmailLink			equ 1011


;#########################################################################


.data
;***************** String ****************** 
;ClassName					db "DLGCLASS",0   Ya no se requiere
AppName						db "FUU - Faster Universal Unpacker",0
AboutMsg					db "FUU - Faster Uiversal Unpacker",13,10,"Copyright © NCR 2010",0
msgText						db "FUU - Faster Universal Unpacker by +NCR/CRC! [ReVeRsEr]",13,10,13,10,
									"Thanks to: marciano, Guan De Dio and InDuLgEo.",13,10,13,10,
									"Web: http://crackinglandia.blogspot.com",13,10,
									"@: nahuelriva[at]gmail[dot]com",0
msgTitle					db "FUU - Copyright © NCR 2010",0
fPattern					db "*.dll",0
DoUnpackName				db "DoUnpack",0
GetPluginName				db "GetPluginName",0
SelectPluginError			db "You must select a plugin first",0
ErrorMsgText				db "An error has ocurred while loading plugins",0
ErrorMsgTitle				db "Fatal Error",0
FilterString 				db "All Files",0,"*.*",0h,0h
ErrorMsg					db "Error",0
FUUID						db "FUU1",0
ToolsDirName				db "Tools",0
;Pluginsx86DirName			db "Plugins\x86",0
Pluginsx64DirName			db "Plugins\x64",0
CryptoSignDllName			db "kanal.dll",0
GenOEPDllName				db "GenOEP.dll",0
GenUnpackerDllName			db "ZDRx.dll",0
IdentifyPESignatureDllName 	db "Detect_Signatures.dll",0
DoMyJobProcName				db "DoMyJob",0
SelectionFileErrorMsg 		db "You must select a file first",0
CrackinglandiaLink			db "http://crackinglandia.blogspot.com",0
EmailAddress				db "nahuelriva@gmail.com",0
Subject						db "FUU",0
Body						db "A message about FUU",0

szOpen						db "open",0
szFUUGoogleGrupo			db "http://groups.google.com/group/faster-universal-unpacker",0
szFUUWEB					db "http://code.google.com/p/fuu/",0
szErrorLista				db "INITERROR: Failed to build internal list object",0
szIntialError				db "Initialize Error",0
;******************************


DoUnpackAddrs		dq 0
GetPluginNameAddrs	dq 0
counter				dq 0
current_selection	dq CB_ERR
CurrentDir			db MAX_PATH dup(0)
ToolsDir			db MAX_PATH dup(0)
TempDllName			db MAX_PATH dup(0)
pInfo				PluginInfo 255 dup(<>)
AuxList				PluginInfo 255 dup(<>)
;IsFileSelected		dq 0
;RealignPEFlag		dq 0


hListBox			dq 0
hCombo				dq 0
fHandle				dq 0
hUnpackButton		dq 0
hList				dq 0
hAuxList			dq 0
hModule				dq 0
hBlogLink			dq 0
hEmailLink			dq 0
CommandLine			dq 0
hMainHanlde			dq 0
_lpItem				dq 0


GlobalBuffer 		db 1024 dup(0)
ofn 				OPENFILENAME <>


szMZ						db "MZ",0
szPE						db "PE",0

NotPEPlusFile				db "Error: That's not a PE+ File",0


REALIGNPE			dd 1h
COPYOVERLAYDATA 	dd 1h
OptionsArray		dq 2 dup(REALIGNPE,COPYOVERLAYDATA)
PIList				PluginInfo <>
PIAuxList			PluginInfo <>
.data?

hInstance			dq ?

;#########################################################################
