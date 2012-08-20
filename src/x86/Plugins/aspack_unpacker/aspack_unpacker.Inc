; $Id: aspack_unpacker.Inc 37 2010-07-11 22:35:38Z nahuelriva $

include windows.inc
include kernel32.inc
include user32.inc
include comdlg32.inc
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
FUUID db "FUU1",0
FilterString db "All Files",0,"*.*",0h,0h

.data
OEPPattern db 089h, 085h, 000h, 000h, 000h, 000h, 061h, 075h, 000h, 
			0B8h, 001h, 000h, 000h, 000h, 0C2h, 000h, 000h, 068h, 
			000h, 000h, 000h, 000h, 0C3h
OEPPatternSize dd 23
OEPPatternBPX dd 0
OEPPatternCallBack dd offset OriginalEntryPointCB

LoadLibraryPattern db 003h, 0C2h, 08Bh, 0D8h, 050h, 0FFh, 095h, 
					000h, 000h, 000h, 000h
LoadLibraryPatternSize dd 11
LoadLibraryPatternBPX dd 0
LoadLibraryCallBack dd offset LoadLibraryCB

GetProcAddressPattern db 053h, 0FFh, 0B5h, 000h, 000h, 000h, 000h, 
						0FFh, 095h, 000h, 000h, 000h, 000h, 085h, 0C0h, 05Bh
GetProcAddressPatternSize dd 16
GetProcAddressPatternBPX dd 0
GetProcAddressCallBack dd offset GetProcAddressCB

PluginName db 'ASPack 2.x Unpacker',0
FatalErrorMsg db 'Fatal Error!!!',0
UnpackProcessDoneMsg db '[+] Unpack process terminated',0
CopyOverlayMsg db '-> Overlay Data copied to file',0
RealignPEMsg db '-> PE Image religned',0
ListBoxClassName db 'ListBox',0
IATFixedMsg db '-> IAT Fixed',0
StartMsg db '*** ASPack Unpacker by +NCR/CRC! [ReVeRsEr] ***',0
MySection db ".Imports",0
DumpMsg db '-> Process Dumped',0
WebLinkMsg db 'Web: http://crackinglandia.blogspot.com',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
UnpackedFileNameFormat db '%s.unpacked.%s',0
ErrorMsg db 'Error!!!',0
GetProcAddressBPX db '++ GetProcAddress Breakpoint at: %s',0
GetProcAddrBPX db '++ GetProcAddress Breakpoint: %08X',0
NotValidPEMsg db '! The selected file is not a valid PE32 file',0
EndUnpackMsg db '[+] Unpack Process Finished',0
OepBPX db "-> Entry Point at: %08X",0
PasteHeaderMsg db '-> PE32 Header Pasted',0
PossibleNotPackedError db '! The file seems to be not packed with ASPack',0
LoadLibraryBPX db '++ LoadLibrary Breakpoint at: %s',0
NoOverlayDetected db "No Overlay Data Detected!",0
WildCard db 0
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
