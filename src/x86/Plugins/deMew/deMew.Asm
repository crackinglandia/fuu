; $Id: deMew.Asm 98 2010-09-19 23:46:26Z nahuelriva $

comment ~
 deMew - MEW Unpacker for MEW - LGPL 3.0

 Copyright (C) 2010 +NCR/CRC! [ReVeRsEr] http://crackinglandia.blogspot.com

 This library is free software: you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library.  If not, see <http://www.gnu.org/licenses/>.

 [+] Port from ReversingLabs Mew10Detected Unpacker
 
 Author: +NCR/CRC! [ReVeRsEr]
 Date: July 16, 2010

[Supported Versions]
* MEW 5 (v0.1)
* MEW 10 (v1.0)
* MEW 11 SE 1.2

[Changelog]
* First stable version

[Known Limitations]
* Does not support dll unpacking (yet)

~

.586
.model flat, stdcall
option casemap:none

include deMew.inc

.code

LibMain proc hInstDLL:DWORD, reason:DWORD, unused:DWORD
	comment ~
	Function Name: LibMain
	Function Description: The main function of the dll 
	Function Parameters:
		hInstDLL: DWORD
		reason: DWORD
		unused: DWORD
	~

	mov eax, TRUE	
	ret
LibMain endp

GetPluginName proc
	comment ~
	Function Name: GetPluginName
	Function Description: Returns the plugin's name 
	Function Parameters: None
	~

	mov eax, offset PluginName
	ret

GetPluginName endp

DoUnpack proc hMainDlg:DWORD, szFname:DWORD, lpOptionsArray:DWORD, lpReserved:DWORD, lpParam:DWORD
	comment ~
	Function Name: DoUnpack
	Function Description: This function is a wrapper for _DoUnpack. This function makes an init() to 
							initialize all the variables and data structures needed by the dll. 
	Function Parameters:
		hMainDlg: DWORD
		szFname: DWORD
		lpOptionsArray: DWORD
		lpReserved: DWORD
		lpParam: DWORD
	~
	
	mov eax, dword ptr[lpReserved]
	invoke lstrcmp, eax, addr FUUID
	.if eax != 0
		invoke MessageBox, hMainDlg, chr$("IDERROR: This is not a FUU plugin :/"), chr$("ERROR!!!"), MB_ICONERROR
		ret 
	.endif
	
	mov edi, lpOptionsArray
	mov eax, dword ptr[edi]
	mov ebx, dword ptr[edi+4]
	
	mov eax, dword ptr[eax]
	mov ebx, dword ptr[ebx]
	
	mov bRealignPEFlag, eax
	mov CopyOverlayDataFlag, ebx
	
	mov eax, szFname
	invoke lstrlen, eax
	inc eax
	.if eax < 1024
		invoke lstrcpyn, addr PathFileName, szFname, 1024
	.endif
	
	invoke GetControlHandle, hMainDlg
	
	invoke LogMessage, addr StartMsg
	invoke LogMessage, addr StartUnpackProcessMsg
 	invoke LogMessage, addr WebLinkMsg
 	
	invoke _DoUnpack, hMainDlg, szFname, NULL, lpReserved, lpParam
	
	ret

DoUnpack endp

_DoUnpack proc hMainDlg:DWORD, szPathFileName:DWORD, dwCallBack:DWORD, lpReserved:DWORD, lpParam:DWORD
	comment ~
	Function Name: _DoUnpack
	Function Description: Makes the unpack things :). This function initialize the debug loop. 
	Function Parameters:
		hMainDlg: DWORD
		szFname: DWORD
		dwCallBack: DWORD
		lpReserved: DWORD
		lpParam: DWORD
	~

	pushad
	mov eax, szPathFileName
	.if eax != NULL && byte ptr[eax] != NULL
		invoke IsPE32FileValidEx, szPathFileName, UE_DEPTH_DEEP, NULL
		.if eax == 1
			invoke IsFileDLL, szPathFileName, NULL
			
			.if eax == NULL
				
				invoke InitDebugEx, szPathFileName, 0, 0, addr cbAnalyzePackerEntry
				
				.if eax != NULL
					invoke DebugLoop
				.else
					invoke LogMessage, addr ErrorMsg
					invoke LogMessage, addr EndUnpackMsg
				.endif
				
			.else
				invoke LogMessage, addr ErrorMsg
				invoke LogMessage, addr DLLUnpackNotAllowedMsg
			.endif
		.else
			invoke LogMessage, addr ErrorMsg
			invoke LogMessage, addr NotValidPEMsg
		.endif
	.else
		invoke LogMessage, addr ErrorMsg
		invoke LogMessage, addr EndUnpackMsg
	.endif
	
	popad
	ret
_DoUnpack endp

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

GetControlHandle proc hWin:HWND
	comment ~
	Function Name: GetControlHandle
	Function Description: Returns the handle of the main window.
	Function Parameters:
		hWin: DWORD
	~

	pushad
	
	invoke FindWindowEx, hWin, NULL, offset ListBoxClassName, NULL
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

cbAnalyzePackerEntry proc
	
	LOCAL lpLoadedBaseAddress:DWORD
	LOCAL lpBuffer:DWORD
	LOCAL lpBytesWritten:DWORD
	LOCAL EIP:DWORD
	LOCAL pi:DWORD
	LOCAL mi:MEMORY_BASIC_INFORMATION
	LOCAL OEPPatternAddress:DWORD
	LOCAL OEP:DWORD
	LOCAL BytesWritten:DWORD
	
	invoke GetDebuggedFileBaseAddress
	mov lpLoadedBaseAddress, eax
	
	push lpLoadedBaseAddress
	push offset LoadedBaseAddressMsg
	push offset TempBuffer
	call wsprintf
	add esp, 12
	invoke LogMessage, addr TempBuffer
	
	invoke GetProcessInformation
	mov pi, eax
	
	invoke GetContextData, UE_EIP
	mov EIP, eax
	
	invoke GetMEWVersion
	.if al == 5 ; MEW 5 (v0.1)
		mov IsMew5, 1
		
		invoke LogMessage, addr Mew5Detected
		invoke GetContextData, UE_EIP
		mov EIP, eax
		
		invoke GetProcessInformation
		mov pi, eax
		
		mov edx, pi
		
		mov ebx, dword ptr[EIP]
		inc ebx
		invoke ReadProcessMemory, dword ptr[edx + PROCESS_INFORMATION.hProcess], ebx, addr lpBuffer, 4, addr BytesWritten
		
		;invoke VirtualQueryEx, dword ptr[edx + PROCESS_INFORMATION.hProcess], dword ptr[EIP], addr mi, sizeof MEMORY_BASIC_INFORMATION
		;mov edi, dword ptr[mi.BaseAddress]
		;add edi, dword ptr[mi.RegionSize]
		
		;mov edx, pi
		
		;invoke VirtualQueryEx, dword ptr[edx + PROCESS_INFORMATION.hProcess], dword ptr[EIP], addr mi, sizeof MEMORY_BASIC_INFORMATION
		;add edi, dword ptr[mi.RegionSize]
		;sub edi, esi
		
		.if eax != 0
		
			mov eax, dword ptr[lpBuffer]
			dec eax
			
			invoke SetHardwareBreakPoint, eax, 0, UE_HARDWARE_EXECUTE, UE_HARDWARE_SIZE_1, addr OnOEP
			mov eax, TRUE
			ret
			
			;mov ebx, EIP
			;invoke Find, ebx, edi, addr Mew5JumpPattern, sizeof Mew5JumpPattern, addr WildCard
			
			;.if eax != NULL
			;	add eax, 1
			;	mov edx, pi
			;	invoke GetJumpDestination, dword ptr[edx + PROCESS_INFORMATION.hProcess], eax
				
			;	.if eax != NULL
			;		invoke SetHardwareBreakPoint, eax, 0, UE_HARDWARE_EXECUTE, UE_HARDWARE_SIZE_1, addr OnOEP
			;		mov eax, TRUE
			;		ret
			;	.endif
			;.endif			 
		.else
			invoke LogMessage, addr ReadProcessMemoryFailed
		.endif
			
	.elseif al == 10 ; MEW 10 (v1.0)
		invoke LogMessage, addr Mew10Detected
		mov IsMew10, 1
		
		mov edx, pi
		
		lea ebx, EIP
		sub dword ptr[ebx], sizeof DWORD
		
		invoke ReadProcessMemory, dword ptr[edx + PROCESS_INFORMATION.hProcess], dword ptr[ebx], addr lpBuffer, sizeof WORD, addr lpBytesWritten
		
		.if eax != 0
			.if dword ptr[lpBytesWritten] == sizeof WORD
				invoke SetHardwareBreakPoint, dword ptr[lpBuffer], 0, UE_HARDWARE_EXECUTE, UE_HARDWARE_SIZE_1, addr cbOnOEPLayer
				
				.if eax == TRUE
					ret
				.endif
			.else
				invoke LogMessage, addr CantReadMemory
			.endif
		.else
			invoke LogMessage, addr CantReadMemory
		.endif
		
	.elseif al == 11 ; MEW 11 SE 1.2
		invoke LogMessage, addr Mew11Detected
		
		invoke GetContextData, UE_EIP
		mov ebx, eax
		mov edx, pi
		
		invoke GetJumpDestination, dword ptr[edx + PROCESS_INFORMATION.hProcess], ebx
		
		.if eax != NULL
			invoke OEPLayer, eax
			
			.if eax == TRUE
				ret
			.endif
			
		.endif 
	.else
		; no luck :( not packed with MEW?
		invoke LogMessage, addr PossibleNotPackedError
		invoke Abort
	.endif
	ret
	
cbAnalyzePackerEntry endp

cbOnOEPLayer proc

	invoke LogMessage, addr MewLayerProcessed
	invoke OEPLayer, NULL
	
	.if eax == TRUE
		ret
	.endif
	
	invoke LogMessage, addr PatterMissing
	invoke Abort
	
	
	ret

cbOnOEPLayer endp

OEPLayer proc lpStart:DWORD

	LOCAL iOEPIndex:DWORD
	LOCAL iLength:DWORD
	LOCAL Buffer[5]:BYTE
	LOCAL IO:DWORD
	LOCAL OEP:DWORD
	LOCAL pi:DWORD
	
	mov iOEPIndex, 1
	mov iLength, 5
	
	invoke GetProcessInformation
	mov pi, eax
	
	.if lpStart == NULL
		invoke GetContextData, UE_EIP
		mov ebx, eax
		mov edx, pi
		invoke ReadProcessMemory, dword ptr[edx + PROCESS_INFORMATION.hProcess], ebx, addr Buffer, iLength, addr IO
	.else
		mov edx, pi
		invoke ReadProcessMemory, dword ptr[edx + PROCESS_INFORMATION.hProcess], lpStart, addr Buffer, iLength, addr IO 
	.endif
	
	.if eax != 0
		mov eax, dword ptr[iLength]
		.if dword ptr[IO] == eax
			movzx eax, byte ptr[IsMew10]
			mov ecx, dword ptr[Buffer+1]
			
			lea edx, dword ptr[ecx+eax*4+4]
			
			mov ebx, pi
			invoke ReadProcessMemory, dword ptr[ebx + PROCESS_INFORMATION.hProcess], edx, addr OEP, sizeof OEP, addr IO
			
			.if eax != 0
				.if dword ptr[IO] == sizeof OEP
					invoke SetHardwareBreakPoint, dword ptr[OEP], 0, UE_HARDWARE_EXECUTE, UE_HARDWARE_SIZE_1, addr OnOEP
					mov eax, TRUE
					ret 
				.else
					invoke LogMessage, NoEnoughBytes
				.endif
			.else
				invoke LogMessage, addr CantReadMemory
			.endif 
		.endif
	.else
		invoke LogMessage, addr CantReadMemory
	.endif
	ret

OEPLayer endp

OnOEP proc
	LOCAL OEP:DWORD
	LOCAL pi:DWORD
	LOCAL lBase:DWORD	
	LOCAL IATStart:DWORD
	LOCAL IATSize:DWORD
	LOCAL OverlayStart :DWORD
	LOCAL OverlaySize :DWORD
	
	invoke GetSaveDialog
	.if FileSaveFlag == 1
		invoke RemoveAllBreakPoints, UE_OPTION_REMOVEALL
		
		.if IsMew5 == 1
			invoke GetContextData, UE_EBX
			mov OEP, eax
		.else
		
			invoke GetContextData, UE_EIP
			mov OEP, eax
		.endif
		
		push OEP
		push offset OEPFound
		push offset TempBuffer
		call wsprintf
		add esp, 12
		invoke LogMessage, addr TempBuffer
		
		invoke GetProcessInformation
		mov pi, eax
		
		invoke GetDebuggedFileBaseAddress
		mov lBase, eax
		
		mov edx, pi 
		invoke PastePEHeader, dword ptr[edx + PROCESS_INFORMATION.hProcess], dword ptr[lBase], addr PathFileName
		
		mov edx, pi
	
		invoke DumpProcess, dword ptr[edx + PROCESS_INFORMATION.hProcess], dword ptr[lBase], addr UnpackedFileNameBuffer, dword ptr[OEP] 
		
		.if eax == TRUE
			invoke LogMessage, addr ProcessDumped
			
			invoke MakeAllSectionsRWE, addr UnpackedFileNameBuffer
			
			invoke GetPE32Data, addr PathFileName, 0, UE_SIZEOFIMAGE
			
			mov ebx, eax
			
			mov edx, pi
			
			invoke ImporterAutoSearchIAT, dword ptr[edx + PROCESS_INFORMATION.hProcess], addr UnpackedFileNameBuffer, dword ptr[lBase], dword ptr[lBase], ebx, addr IATStart, addr IATSize
			
			mov edx, pi
			invoke ImporterAutoFixIATEx, dword ptr[edx + PROCESS_INFORMATION.hProcess], addr UnpackedFileNameBuffer, offset MySection, FALSE, byte ptr[bRealignPEFlag], dword ptr[OEP], dword ptr[lBase], dword ptr[IATStart], dword ptr[IATSize], sizeof DWORD, FALSE, FALSE, 0
			
			.if eax != 400h	; 0x400 == ERROR_SUCCESS
				invoke LogMessage, addr CantFixImports
				invoke Abort
				ret
			.else
				invoke LogMessage, addr ImportsFixed
				
				.if CopyOverlayDataFlag == 1
					invoke FindOverlay, addr PathFileName, addr OverlayStart, addr OverlaySize
					.if eax == 1
						invoke CopyOverlay, addr PathFileName, addr UnpackedFileNameBuffer
						invoke LogMessage, addr OverlayCopied
					.else
						invoke LogMessage, addr NoOverlayDetected
					.endif
				.endif
				
				.if bRealignPEFlag == TRUE
					invoke RealignPEEx, addr UnpackedFileNameBuffer, 0, 0
					
					.if eax != 0
						invoke LogMessage, addr PERealigned
					.else
						invoke LogMessage, addr PERealignedFailed
					.endif
				.endif
				
				invoke LogMessage, addr FileUnpackedSuccessfully
			.endif
		.else
			invoke LogMessage, addr CantDumpProcess
		.endif
	.endif
	
	invoke StopDebug
	invoke LogMessage, addr DebugStoped
	ret

OnOEP endp

Abort proc
	
	invoke StopDebug
	invoke LogMessage, addr UnpackingProcessAborted
	ret

Abort endp

GetMEWVersion proc
	
	LOCAL wRet:WORD
	LOCAL lpBuff:WORD
	LOCAL lpBytesWritten:DWORD
	
	invoke GetContextData, UE_EIP
	mov ebx, eax
		
	invoke GetProcessInformation
	mov edx, eax
	
	invoke ReadProcessMemory, dword ptr[edx + PROCESS_INFORMATION.hProcess], ebx, addr lpBuff, sizeof lpBuff, addr lpBytesWritten
	
	.if eax != 0
		lea eax, lpBuff
		.if word ptr[eax] == 0C033h
			mov wRet, 10
		.elseif byte ptr[eax] == 0E9h
			mov wRet, 11
		.elseif word ptr[eax] == 5BBEh
			mov wRet, 5
		.else
			mov wRet, 0
		.endif
	.else
		invoke LogMessage, addr CantReadMemory
	.endif
	
	mov ax, word ptr[wRet]
	ret

GetMEWVersion endp

end LibMain