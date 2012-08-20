; $Id: upx_unpacker.Inc 43 2010-07-11 22:41:24Z nahuelriva $

include windows.inc
include kernel32.inc
include user32.inc
include comdlg32.inc
include SDK.inc

includelib comdlg32.lib
includelib kernel32.lib
includelib user32.lib
includelib TitanEngine_x86.lib


_DoUnpack PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
cbGetEP PROTO :DWORD
GetControlHandle PROTO :DWORD
LogMessage PROTO :DWORD
BuildUnpackedFileName PROTO :DWORD	
cbFindPatterns PROTO
LoadLibraryCallBack PROTO
GetProcAddressCallBack PROTO
EntryPointCallBack PROTO
SehHandler PROTO C :DWORD,:DWORD,:DWORD,:DWORD
SnapShoot1CallBack PROTO
MapFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
UnmapFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetUnpackerFolder PROTO
GetSaveDialog PROTO

chr$ MACRO any_text:VARARG
LOCAL txtname
.data
  txtname db any_text,0
.code
EXITM <OFFSET txtname>
ENDM

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

sSEH STRUCT
	OrgEsp dd ?
	OrgEbp dd ?
	SaveEip dd ?
sSEH ENDS

WildCard db 0

Pattern1 db 050h,083h,0C7h,008h,0FFh
Pattern1Size dd 5
Pattern1CallBack dd offset LoadLibraryCallBack
Pattern1BP dd 0

Pattern2 db 050h,047h,000h,057h,048h,0F2h,0AEh
Pattern2Size dd 7
Pattern2CallBack dd offset GetProcAddressCallBack
Pattern2BP dd 0

Pattern3 db 057h,048h,0F2h,0AEh,000h,0FFh
Pattern3Size dd 6
Pattern3CallBack dd offset GetProcAddressCallBack
Pattern3BP dd 0

Pattern4 db 089h,0F9h,057h,048h,0F2h,0AEh,052h,0FFh
Pattern4Size dd 8 
Pattern4CallBack dd offset GetProcAddressCallBack
Pattern4BP dd 0

Pattern5 db 061h,0E9h
Pattern5Size dd 2
Pattern5CallBack dd offset EntryPointCallBack
Pattern5BP dd 0

Pattern6 db 083h,0ECh,000h,0E9h
Pattern6Size dd 4
Pattern6CallBack dd offset EntryPointCallBack
Pattern6BP dd 0

Pattern7 db 031h,0C0h,08Ah,007h,047h,009h,0C0h,074h,022h,03Ch,0EFh,
		      077h,011h,001h,0C3h,08Bh,003h,086h,0C4h,0C1h,0C0h,010h,
		      086h,0C4h,001h,0F0h,089h,003h,0EBh,0E2h,024h,00Fh,0C1h,
		      0E0h,010h,066h,08Bh,007h,083h,0C7h,002h,0EBh,0E2h
Pattern7Size dd 43
Pattern7CallBack dd offset SnapShoot1CallBack
Pattern7BP dd 0

SeconSnapShootOnEP db 1

StartMsg db '*** UPX v1.x - 3.x Unpacker ***',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
PossibleNotPackedError db 'The file seems to be not packed with UPX',0
PluginName db 'UPX v1.x - 3.x Unpacker',0
ErrorMsg db 'Error',0
NotValidPEMsg db 'The selected file is not a valid PE32 file',0
LoadLibraryBPX db 'LoadLibrary Breakpoint at: %s',0
GetProcAddressBPX db 'GetProcAddress Breakpoint at: %s',0
GetProcAddrBPX db 'GetProcAddress Breakpoint: %08X',0
OepBPX db "Entry Point at: %08X",0
PasteHeaderMsg db 'PE32 Header Pasted',0
DumpMsg db 'Process dumped',0
MySection db ".Imports",0
IATFixedMsg db 'IAT Fixed',0
ExportRelocationMsg db 'Exporting Relocations',0
RealignPEMsg db 'PE Realigned',0
NoOverlayDetected db 'No Overlay Data Detected!',0
RelocationChangeBaseMsg db 'Rebase File Image',0
CopyOverlayMsg db 'Copying overlay data to unpacked file',0 
UnpackProcessDoneMsg db 'Done. File Unpacked',0
EndUnpackMsg db 'Unpack Process Finished',0
FatalErrorMsg db 'Fatal Error Ocurred',0
ListBoxClassName db 'ListBox',0
UnpackedFileNameFormat db '%s.unpacked.%s',0
szSnapShoot1Name db "snap.1",0
szSnapShoot2Name db "snap.2",0
hControl dd 0
FileSaveFlag db 0

.data?
cbInitCallBack dd ?
LoadedBaseAddress dd ?
_IsFileDll db ?
RealignPEFlag dd ?
CopyOverlayDataFlag dd ?
ImageBase dd ?
EntryPoint dd ?
SizeOfImage dd ?
SnapshootMemoryStartRVA dd ?
MAJOR_DEBUG_ERROR_EXIT dd ?
SnapShootMemorySize dd ? 	
ProcessInfo PROCESS_INFORMATION <?>
StringData db 256 dup(?)
SEH sSEH <?>
TempBuffer db 1024 dup(?)
TempBuffer2 db 1024 dup(?)
PathFileName db 1024 dup(?)
UnpackedFileNameBuffer db 1024 dup(?)
SnapShoot1 db 1024 dup(?)
SnapShoot2 db 1024 dup(?)
UnpackerFolder db 1024 dup(?)
GlobalBuffer db 1024 dup(?)
ofn OPENFILENAME <?>
