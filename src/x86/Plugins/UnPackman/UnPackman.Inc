; $Id: UnPackman.Inc 42 2010-07-11 22:40:28Z nahuelriva $

include windows.inc
include comdlg32.inc
include kernel32.inc
include user32.inc
include SDK.inc

includelib comdlg32.lib
includelib kernel32.lib
includelib user32.lib
includelib TitanEngine_x86.lib

_DoUnpack PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
GetControlHandle PROTO :DWORD
LogMessage PROTO :DWORD
MapFileEx PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
UnmapFileEx PROTO :DWORD, :DWORD, :DWORD, :DWORD
OriginalEntryPointCB PROTO
LoadLibraryCB PROTO
GetProcAddressCB PROTO
cbGetEP PROTO :DWORD
BuildUnpackedFileName PROTO :DWORD
GetUnpackerFolder PROTO
cbFindPatterns PROTO
GetSaveDialog PROTO

chr$ MACRO any_text:VARARG
LOCAL txtname
.data
  txtname db any_text,0
.code
EXITM <OFFSET txtname>
ENDM

sSEH STRUCT
	OrgEsp dd ?
	OrgEbp dd ?
	SaveEip dd ?
sSEH ENDS

KillSehFrame MACRO
	POP  FS:[0]
	ADD  ESP, 4
ENDM

InstSEHFrame MACRO ContinueAddr
	ASSUME FS : NOTHING

	MOV  SEH.SaveEip, ContinueAddr
	MOV  SEH.OrgEbp, EBP
	PUSH OFFSET SehHandler
	PUSH FS:[0]
	MOV  SEH.OrgEsp, ESP
	MOV  FS:[0], ESP
ENDM

DLL_RET_MSG struct
	szMsgText		dd 0
	szMsgHead		dd 0
	dRetVal			dd 0
	dRetExVal		dd 0
	dFlags			dd 0
DLL_RET_MSG ends

.const
FilterString db "All Files",0,"*.*",0h,0h
FUUID db "FUU1",0

.data
WildCard db 0

OEPPattern db 061h, 0E9h, 000h, 000h, 000h, 000h, 059h, 05Fh, 05Eh, 058h, 051h, 057h
OEPPatternSize dd 12
OEPPatternBPX dd 0
OEPPatternCallBack dd offset OriginalEntryPointCB

OEPPattern2 db 061h, 0E9h, 000h, 000h, 000h, 000h, 055h, 08Bh, 0ECh, 000h, 000h, 000h
OEPPatternSize2 dd 12
OEPPatternBPX2 dd 0
OEPPatternCallBack2 dd offset OriginalEntryPointCB

LoadLibraryPattern db 003h, 003h, 050h, 0FFh, 055h, 000h
LoadLibraryPatternSize dd 6
LoadLibraryPatternBPX dd 0
LoadLibraryCallBack dd offset LoadLibraryCB

GetProcAddressPattern db 003h, 00Bh, 041h, 041h, 050h, 051h, 050h, 0FFh, 055h, 004h
GetProcAddressPatternSize dd 10
GetProcAddressPatternBPX dd 0
GetProcAddressCallBack dd offset GetProcAddressCB

PluginName db 'UnPackman for Packman 1.0',0
FatalErrorMsg db 'Fatal Error',0
UnpackProcessDoneMsg db '[+] Unpack process terminated',0
CopyOverlayMsg db 'Overlay Data copied to file',0
RealignPEMsg db 'PE Image religned',0
ListBoxClassName db 'ListBox',0
IATFixedMsg db 'IAT Fixed',0
StartMsg db '*** UnPackman Unpacker by +NCR/CRC! [ReVeRsEr] ***',0
MySection db ".Imports",0
DumpMsg db 'Process Dumped',0
WebLinkMsg db 'Web: http://crackinglandia.blogspot.com',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
UnpackedFileNameFormat db '%s.unpacked.%s',0
ErrorMsg db 'Error',0
GetProcAddressBPX db 'GetProcAddress Breakpoint at: %s',0
GetProcAddrBPX db 'GetProcAddress Breakpoint: %08X',0
NotValidPEMsg db 'The selected file is not a valid PE32 file',0
EndUnpackMsg db 'Unpack Process Finished',0
OepBPX db "Entry Point at: %08X",0
PasteHeaderMsg db 'PE32 Header Pasted',0
PossibleNotPackedError db 'The file seems to be not packed with Packman',0
DLLUnpackNotAllowedMsg db 'DLL Unpacking is not supported, if you have one, please, send it to me :)',0
LoadLibraryBPX db 'LoadLibrary Breakpoint at: %s',0
NoOverlayDetected db "No Overlay Data Detected!",0
FileSaveFlag db 0

.data?
hControl dd ?
bRealignPEFlag dd ?
CopyOverlayDataFlag dd ?
dwImageBase dd ?
dwEntryPoint dd ?
dwSizeOfImage dd ?
cbInitCallBack dd ?
dwLoadedBaseAddress dd ?
StringData db 256 dup(?)
PathFileName db 1024 dup(?)
TempBuffer db 1024 dup(?)
UnpackedFileNameBuffer db 1024 dup(?)
ProcessInfo PROCESS_INFORMATION <?>
SEH sSEH <?>
MAJOR_DEBUG_ERROR_EXIT dd ?
UnpackerFolder db 1024 dup(?)
ofn OPENFILENAME <?>
