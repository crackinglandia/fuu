; "$Id: deExeFog.Inc 79 2010-07-16 22:07:35Z nahuelriva $"

include windows.inc
include kernel32.inc
include user32.inc
include comdlg32.inc
include TitanEngine.inc

includelib comdlg32.lib
includelib kernel32.lib
includelib user32.lib
includelib TitanEngine_x86.lib

_DoUnpack PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
GetControlHandle PROTO :DWORD
LogMessage PROTO :DWORD
MapFileEx PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
UnmapFileEx PROTO :DWORD, :DWORD, :DWORD, :DWORD
BuildUnpackedFileName PROTO :DWORD
GetUnpackerFolder PROTO
GetSaveDialog PROTO

; callbacks
cbFindPatterns PROTO
cbGetEP PROTO :DWORD
cbOriginalEntryPoint PROTO
cbLoadLibrary PROTO
cbGetProcAddress PROTO
cbHideDebuggerFromExeFog PROTO
cbDecryptionLoop PROTO

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
OEPPattern db 001h, 02Ch, 024h, 0C3h, 013h, 013h, 013h, 013h
OEPPatternSize dd sizeof OEPPattern
OEPPatternBPX dd 0
OEPPatternCallBack dd offset cbOriginalEntryPoint

LoadLibraryPattern db 08Bh, 059h, 00Ch, 001h, 0EBh, 051h, 053h, 0FFh, 0D7h
LoadLibraryPatternSize dd sizeof LoadLibraryPattern
LoadLibraryPatternBPX dd 0
LoadLibraryCallBack dd offset cbLoadLibrary

GetProcAddressPattern db 001h, 0E8h, 083h, 0C0h, 002h, 050h, 053h, 0FFh, 0D6h
GetProcAddressPatternSize dd sizeof GetProcAddressPattern
GetProcAddressPatternBPX dd 0
GetProcAddressCallBack dd offset cbGetProcAddress

IsDebuggerPresentTrickPattern db 031h, 0C9h, 083h, 0C1h, 000h, 0BBh, 000h, 000h, 000h, 
								000h, 064h, 08Bh, 083h, 000h, 000h, 000h, 000h, 08Bh, 
								044h, 048h, 010h, 00Fh, 0B6h, 040h, 002h, 0F7h, 0D0h, 
								083h, 0E0h, 001h
IsDebuggerPresentTrickSize dd sizeof IsDebuggerPresentTrickPattern
IsDebuggerPresentTrickPatternBPX dd 0
IsDebuggerPresentTrickCallback dd offset cbHideDebuggerFromExeFog

DecryptionLoopPattern db 0B9h, 0C8h, 000h, 000h, 000h, 0B0h, 000h, 030h, 004h, 00Bh, 
							08Ah, 004h, 00Bh, 0E2h, 0F8h
DecryptionLoopPatternSize dd sizeof DecryptionLoopPattern
DecryptionLoopPatternBPX dd 0
DecryptionLoopPatternCallback dd offset cbDecryptionLoop

PluginName db 'deExeFog - exeFog! Unpacker',0
FatalErrorMsg db '[!!!] Fatal Error',0
UnpackProcessDoneMsg db '[+] Unpack process terminated',0
CopyOverlayMsg db '[+] Overlay Data copied to file',0
RealignPEMsg db '[+] PE Image religned',0
ListBoxClassName db 'ListBox',0
IATFixedMsg db '[+] IAT Fixed',0
StartMsg db '*** exeFog Unpacker by +NCR/CRC! [ReVeRsEr] ***',0
MySection db ".Imports",0
DumpMsg db '[+] Process Dumped',0
WebLinkMsg db 'Web: http://crackinglandia.blogspot.com',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
ErrorMsg db '[!!!] Error',0
GetProcAddressBPX db '-> GetProcAddress Breakpoint at: %s',0
GetProcAddrBPX db '-> GetProcAddress Breakpoint at: %08X',0
NotValidPEMsg db '[!] The selected file is not a valid PE32 file',0
EndUnpackMsg db '[+] Unpack Process Finished',0
OepBPX db "[+] Original Entry Point (OEP) at: %08X",0
PasteHeaderMsg db '[+] PE32 Header Pasted',0
PossibleNotPackedError db '[!] The file seems to be not packed with exeFog',0
WildCard db 0
DLLUnpackNotAllowedMsg db '[!] DLL Unpacking is not supported, if you have one, submit it!',0
LoadLibraryBPX db '[+] LoadLibrary Breakpoint at: %s',0
NoOverlayDetected db "[!] No Overlay Data Detected!",0
NoDecryptionLoopFound db "[!] No decryption loop found (exeFog unsupported version?)",0
NoIsDbgPatternFound db "[!] No IsDebuggerPresent Pattern found!",0
IsDbgTrickPatched db "[!] IsDebuggerPresent trick patched OK!",0
DecryptLoopBpxSet db "[!] Decryption loop breakpoint placed OK!",0
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
