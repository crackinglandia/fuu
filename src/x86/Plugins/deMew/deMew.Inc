; $Id: deMew.Inc 98 2010-09-19 23:46:26Z nahuelriva $

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
GetSaveDialog PROTO
GetMEWVersion PROTO
Abort PROTO

; callbacks
OEPLayer PROTO :DWORD
OnOEP PROTO
cbOnOEPLayer PROTO
cbAnalyzePackerEntry PROTO

chr$ MACRO any_text:VARARG
LOCAL txtname
.data
  txtname db any_text,0
.code
EXITM <OFFSET txtname>
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
WildCard db 0

.data
Mew5JumpPattern db 061h, 0E9h, 000h, 000h, 000h, 000h

; flags
FileSaveFlag db 0
IsMew10 db 0
IsMew5 db 0

; imports section name
MySection db ".fuu",0

; log messages
PluginName db 'deMew - Mew Unpacker for MEW',0
ListBoxClassName db 'ListBox',0
StartMsg db '*** MEW Unpacker by +NCR/CRC! [ReVeRsEr] ***',0
WebLinkMsg db '-> Web: http://crackinglandia.blogspot.com',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
ErrorMsg db '[!!!] Error',0
NotValidPEMsg db '[!] The selected file is not a valid PE32 file',0
EndUnpackMsg db '[+] Unpack Process Finished',0
PossibleNotPackedError db '[!] The file seems to be not packed with MEW',0
DLLUnpackNotAllowedMsg db '[!] DLL Unpacking is not supported, if you have one, please, submit it :)',0
CantReadMemory db "[!!!] Cannot read memory of the process",0
LoadedBaseAddressMsg db "[+] File loaded base address: %08X",0
Mew5Detected db "[+] MEW 5 (v0.1) version detected",0
Mew10Detected db "[+] MEW 10 (v1.0) version detected",0
Mew11Detected db "[+] MEW 11 (SE 1.2) (or newer) version detected",0
UnpackingProcessAborted db "[!!!] Unpacking process aborted",0
MewLayerProcessed db "[+] Mew layer processed",0
PatterMissing db "[!!!] Pattern missing, probably not packed with a supported version",0
NoEnoughBytes db "[!!!] Cannot read necessary bytes", 0
OEPFound db "[+] OEP Found at: %08X",0
CantDumpProcess db "[!!!] Cannot dump process",0
ProcessDumped db "[+] Process dumped OK!",0
CantFixImports db "[!!!] Cannot fix imports", 0
ImportsFixed db "[+] Imports fixed", 0
NoOverlayDetected db "[!] No overlay data detected", 0
OverlayCopied db "[+] Overlay data copied to the file", 0
PERealigned db "[+] PE file religned OK!", 0
PERealignedFailed db "[!!!] PE realigned failed!", 0
FileUnpackedSuccessfully db "[+] File unpacked successfully", 0
DebugStoped db "[!] Process debug stoped", 0
ReadProcessMemoryFailed db "[!!!] VirtualQuery failed!", 0
 
.data?
ofn OPENFILENAME <?>

hControl dd ?
bRealignPEFlag dd ?
CopyOverlayDataFlag dd ?
dwLoadedBaseAddress dd ?
PathFileName db 1024 dup(?)
TempBuffer db 1024 dup(?)
UnpackedFileNameBuffer db 1024 dup(?)
