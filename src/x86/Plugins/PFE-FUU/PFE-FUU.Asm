; $Id: PFE-FUU.Asm 101 2011-02-18 22:04:37Z nahuelriva $

comment ~
PFE Unpacker for PFE

Copyright (C) 2011 pastafr0la rce

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

Author: el tio pastafrola
Date: February 18, 2011

~

.586
.model flat, stdcall
option casemap:none

include PFE-FUU.inc

.code

LibMain proc hInstDLL:DWORD, reason:DWORD, unused:DWORD

	mov eax, TRUE	
	ret
LibMain endp

GetPluginName proc

	mov eax, offset PluginName
	ret

GetPluginName endp

DoUnpack proc hMainDlg:DWORD, szFname:DWORD, lpOptionsArray:DWORD, lpReserved:DWORD, lpParam:DWORD
	LOCAL address_code: DWORD
	
	mov eax, dword ptr[lpReserved]
	invoke lstrcmp, eax, addr FUUID
	.if eax != 0
		invoke MessageBox, hMainDlg, chr$("IDERROR: This is not a FUU plugin :/"), chr$("ERROR!!!"), MB_ICONERROR
		ret 
	.endif
	
	;mov edi, lpOptionsArray
	;mov eax, dword ptr[edi]
	;mov ebx, dword ptr[edi+4]
	
	;mov eax, dword ptr[eax]
	;mov ebx, dword ptr[ebx]
	
	;mov bRealignPEFlag, eax
	;mov CopyOverlayDataFlag, ebx
	
	mov eax, szFname
	invoke lstrlen, eax
	inc eax
	.if eax < 1024
		invoke lstrcpyn, addr PathFileName, szFname, 1024
	.endif
	
	invoke GetControlHandle, hMainDlg
	invoke GetUnpackerFolder
	
	invoke LogMessage, addr StartMsg
	invoke LogMessage, addr StartUnpackProcessMsg
 	
 	invoke IsPE32FileValidEx, addr PathFileName, UE_DEPTH_DEEP, NULL
 	.if eax == TRUE
 		invoke IsFileDLL, addr PathFileName, NULL
 		.if eax == NULL
 			invoke InitDebugEx, szFname, NULL, NULL, cbFindPatterns
 			.if eax != NULL
 				invoke RtlMoveMemory, addr ProcessInfo, eax, sizeof PROCESS_INFORMATION
 				invoke GetPE32Data, addr PathFileName, NULL, UE_IMAGEBASE
 				mov dwImageBase, eax
 				invoke GetPE32Data, addr PathFileName, NULL, UE_SECTIONVIRTUALOFFSET
 				add eax, dwImageBase
 				mov address_code, eax
 				
 				invoke GetPE32Data, addr PathFileName, NULL, UE_SECTIONVIRTUALSIZE
 				invoke Find, address_code, eax, addr Signature, 30, addr WildCard
 				.if eax==NULL
 					invoke LogMessage, addr ErrorMsg
 					invoke LogMessage, addr MaybeNotPacker
 					invoke StopDebug
 					ret
 				.endif
 				
 				invoke DebugLoop
 			.else
 				invoke LogMessage, addr ErrorMsg
 				invoke LogMessage, chr$("[-] Can't create debugge... Aborting")
 				invoke LogMessage, addr EndUnpackMsg
 			.endif
 		.else
 			invoke LogMessage, addr DLLUnpackNotAllowedMsg
 		.endif
 	.else
 		invoke LogMessage, addr NotValidPEMsg
 	.endif

	ret

DoUnpack endp

cbFindPatterns proc
	invoke SetAPIBreakPoint, chr$("kernel32.dll"), chr$("WriteProcessMemory"), UE_BREAKPOINT, UE_APISTART, addr Dumper_cb
	ret
	
cbFindPatterns endp

Dumper_cb proc
	LOCAL buffer: DWORD
	LOCAL bytes_to_write: DWORD
	LOCAL contador_i: DWORD
	LOCAL virtual_offset: DWORD
	LOCAL virtual_size: DWORD
	
	LOCAL readed[3]: BYTE
	LOCAL pe32[1000h]: BYTE
	LOCAL offset_print[5]: BYTE
	LOCAL section_name[10]: BYTE
	pushad
	
	invoke GetStackArgument,0Ch
	mov buffer, eax
	invoke GetStackArgument,10h
	mov bytes_to_write, eax
	
	invoke ReadProcessMemory, ProcessInfo.hProcess, buffer, addr readed, 2, NULL
	invoke lstrcmp, addr readed, chr$("MZ")
	.if eax == 0
	
		invoke wsprintf, addr TempBuffer, chr$("[+] Found unpacked program in address: %i"), buffer
		invoke LogMessage, addr TempBuffer

		; alinear en memoria ;)
		invoke ReadProcessMemory, ProcessInfo.hProcess, buffer, addr pe32, 1000h, NULL
		invoke GetPE32DataFromMappedFile, addr pe32, NULL, UE_SECTIONNUMBER
		mov contador_i, eax
		
		.while contador_i > 0
			dec contador_i
			invoke GetPE32DataFromMappedFile, addr pe32, contador_i, UE_SECTIONVIRTUALOFFSET
			mov virtual_offset, eax
			invoke GetPE32DataFromMappedFile, addr pe32, contador_i, UE_SECTIONNAME
			invoke lstrcpy, addr section_name, eax
			
			invoke SetPE32DataForMappedFile, addr pe32, contador_i, UE_SECTIONRAWOFFSET, virtual_offset
			invoke wsprintf, addr TempBuffer, chr$("[+] Fix Raw offset of section %s to %i"), addr section_name, virtual_offset
			invoke LogMessage, addr TempBuffer
			
			
			 
			invoke GetPE32DataFromMappedFile, addr pe32, contador_i, UE_SECTIONVIRTUALSIZE
			mov virtual_size, eax
			invoke SetPE32DataForMappedFile, addr pe32, contador_i, UE_SECTIONRAWSIZE, eax
			invoke wsprintf, addr TempBuffer, chr$("[+] Fix Raw Size of section %s to %i bytes"), addr section_name, virtual_size
			invoke LogMessage, addr TempBuffer
		.endw
		
		invoke WriteProcessMemory, ProcessInfo.hProcess, buffer, addr pe32, 1000h, NULL
		invoke LogMessage, addr AlignMsg
		
		
		invoke GetSaveDialog
		invoke DumpMemory, ProcessInfo.hProcess, buffer, bytes_to_write, addr UnpackedFileNameBuffer
		invoke lstrcat, addr DumpingMsg, addr UnpackedFileNameBuffer
		invoke LogMessage, addr DumpingMsg
		invoke LogMessage, addr EndUnpackMsg
		invoke StopDebug
	.endif 
	popad
	ret

Dumper_cb endp

GetStackArgument proc argument:BYTE
	LOCAL zone:DWORD
	LOCAL value:DWORD

	invoke GetContextData, UE_ESP
	movzx ebx, argument
	add eax, ebx
	mov zone, eax
	
	invoke GetProcessInformation
	mov ebx, eax
	assume ebx:ptr PROCESS_INFORMATION
		invoke ReadProcessMemory, dword ptr[ebx].hProcess, zone, addr value, 4, NULL
	assume ebx:NOTHING
	
	mov eax, value
	ret

GetStackArgument endp

GetControlHandle proc hWin:HWND
	comment ~
	return the handle of log window or -1 in error
	arguments:
	* hMainDlg
	~
	pushad
	
	invoke FindWindowEx, hWin, NULL, chr$("Listbox"), NULL
	.if eax != NULL
		mov hControl, eax
	.endif
	
	popad
	ret

GetControlHandle endp

LogMessage proc LogMsg:DWORD
	comment ~
	Function Name: LogMessage
	Function Description: Function lo log all what happens during the unpack process.
	Function Parameters:
		LogMsg: DWORD
	~
	
	pushad
	
	invoke SendMessage, hControl, LB_ADDSTRING, NULL, LogMsg
	invoke SendMessage, hControl, LB_GETCOUNT, NULL, NULL
	dec eax
	
	invoke SendMessage, hControl, LB_SETCURSEL, eax, NULL
	
	popad
	ret

LogMessage endp

GetUnpackerFolder proc
	comment ~
	Function Name: GetUnpackFolder
	Function Description: Retuns the full path of the current folder where FUU is running.
	Function Parameters: None
	~

	pushad
	invoke GetModuleHandle, NULL
	
	invoke GetModuleFileName, eax, addr UnpackerFolder, 1024
	mov esi, offset UnpackerFolder
	invoke lstrlen, esi
	add esi, eax
	.while byte ptr [esi] != "\"
		mov byte ptr[esi], 0
		dec esi
	.endw
	popad
	ret

GetUnpackerFolder endp

GetSaveDialog proc
	comment ~
	Function Name: GetSaveDialog
	Function Description: Create the Save File Dialog window 
	Function Parameters: None
	~
	
	pushad
	mov ofn.lStructSize,sizeof ofn
	mov ofn.lpstrFilter,offset FilterString
	mov ofn.lpstrFile,offset UnpackedFileNameBuffer
	mov ofn.nMaxFile,1024
	mov ofn.Flags, OFN_SHOWHELP or OFN_OVERWRITEPROMPT
	mov ofn.lpstrTitle,offset StartMsg
	invoke GetSaveFileName,addr ofn
	.if eax != 0
		mov FileSaveFlag, 1
	.endif
	popad
	ret

GetSaveDialog endp

end LibMain