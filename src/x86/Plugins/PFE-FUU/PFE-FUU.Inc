; $Id: PFE-FUU.Inc 101 2011-02-18 22:04:37Z nahuelriva $

include kernel32.inc
include user32.inc
include comdlg32.inc
include SDK.inc
include masm32.inc

includelib comdlg32.lib
includelib kernel32.lib
includelib user32.lib
includelib TitanEngine_x86.lib
includelib masm32.lib

GetControlHandle PROTO :DWORD
LogMessage PROTO :DWORD
GetUnpackerFolder PROTO
GetSaveDialog PROTO
GetStackArgument PROTO :BYTE

cbFindPatterns PROTO
Dumper_cb PROTO

chr$ MACRO any_text:VARARG
LOCAL txtname
.data
  txtname db any_text,0
.code
EXITM <OFFSET txtname>
ENDM


.const
FilterString db "All Files",0,"*.*",0h,0h
FUUID db "FUU1",0

.data
PluginName db 'dePFE Unpacker for PFE_CX v0.1',0
StartMsg db '*** dePFE by "pastafr0la rce :)" ***',0
StartUnpackProcessMsg db '[+] Unpack Process Started ...',0
ErrorMsg db '[!!!] Error',0
NotValidPEMsg db '[!] The selected file is not a valid PE32 file',0
EndUnpackMsg db '[+] Unpack Process Finished',0
DLLUnpackNotAllowedMsg db '[!] DLL Unpacking is not supported, if you have one, submit it!',0
FileSaveFlag db 0
DumpingMsg db '[+] Dumping the PE Image to: ',0
AlignMsg db '[+] Align the PE Image... done',0
Signature db 50h,0E8h,'????',33h,0C0h,5Ah,59h,59h,64h,89h,10h,68h,'????',8Bh,45h,0E4h,50h,0E8h,'????',59h,0C3h
WildCard db '?'
MaybeNotPacker db '[-] Maybe this application is not protected with PFE-CX v0.1',0
ErrorNotFUU db 'This plugin only run in FUU unpacker',0Ah,0Dh,'Visit http://code.google.com/p/fuu/ for the original version',0Ah,0Dh,'Go to work Martik :)',0;13,10,10,'Visit http://code.google.com/p/fuu/',13,10,10'Go to work Martik :)',0

.data?
dwImageBase dd ?
;la carga GetControlHandle, handle de ventana log
hControl dd ?
;tildado alinear en GUI?
bRealignPEFlag dd ?
;tildado copiar overlay en GUI?
CopyOverlayDataFlag dd ?
;path al archivo que desensamblamos
PathFileName db 1024 dup(?)
;nombre del desempacado
UnpackedFileNameBuffer db 1024 dup(?)
;lo carga despues de InitDebugEx
ProcessInfo PROCESS_INFORMATION <?>
;carpeta donde esta el unpacker, se usa para algunas API's
UnpackerFolder db 1024 dup(?)
TempBuffer db 1024 dup(?)
;inicializa GetSaveFile (Guardar como...)
ofn OPENFILENAME <?>