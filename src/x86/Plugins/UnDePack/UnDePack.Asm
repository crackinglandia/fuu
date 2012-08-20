; $Id: UnDePack.Asm 40 2010-07-11 22:38:37Z nahuelriva $

comment ~
	UndePack for dePack - LGPL 3.0
	
	Copyright (C) 2010   +NCR/CRC! [ReVeRsEr] http://crackinglandia.blogspot.com
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Author: +NCR/CRC! [ReVeRsEr]
 Date: May 04 th, 2010


[Supported Versions]
* dePack ALL (?)

[Changelog]
* First stable version

[Known Limitations]
* It does not support dll unpacking

~

.586
.model flat, stdcall
option casemap:none

include UnDepack.inc

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
	
	invoke GetUnpackerFolder
	
	invoke LogMessage, addr StartMsg
	invoke LogMessage, addr StartUnpackProcessMsg
 	invoke LogMessage, addr WebLinkMsg
 	
	invoke _DoUnpack, hMainDlg, szFname, cbFindPatterns, lpReserved, lpParam
	
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
			
				invoke GetPE32Data,szPathFileName,NULL,UE_IMAGEBASE
				mov dwImageBase,eax
				
				invoke GetPE32Data,szPathFileName,NULL,UE_OEP
				mov dwEntryPoint,eax
				
				invoke GetPE32Data,szPathFileName,NULL,UE_SIZEOFIMAGE
				mov dwSizeOfImage,eax
				
				invoke InitDebug, szPathFileName, NULL, NULL
				
				.if eax != NULL
					mov ebx, eax
					mov eax, dwCallBack
					mov cbInitCallBack, eax
					
					invoke RtlMoveMemory, addr ProcessInfo, ebx, sizeof PROCESS_INFORMATION
					invoke SetCustomHandler,UE_CH_CREATEPROCESS,addr cbGetEP
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

cbFindPatterns proc
	comment ~
	Function Name: cbFindPatterns
	Function Description: This function check for a given pattern in the runnning process.
							It is used to check if the given .exe or .dll is packed with the
							packer you selected.
	Function Parameters: None
	~

	LOCAL MemInfo: MEMORY_BASIC_INFORMATION
	
	pushad
	
	mov esi, dwLoadedBaseAddress
	add esi, dwEntryPoint

	invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], esi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
	mov edi, dword ptr[MemInfo.BaseAddress]
	add edi, dword ptr[MemInfo.RegionSize]
	
	invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], edi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
	add edi, dword ptr[MemInfo.RegionSize]
	sub edi, esi
	
	.if eax != NULL
		invoke Find, esi, edi, addr OEPPattern, OEPPatternSize, addr WildCard
		.if eax != NULL
			mov ebx, eax
			add ebx, 5
			mov OEPPatternBPX, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, OriginalEntryPointCB
		.else
			invoke LogMessage, addr PossibleNotPackedError
			invoke LogMessage, addr EndUnpackMsg
			invoke StopDebug
		.endif		
	.endif
	
	popad
	ret
	
cbFindPatterns endp


cbGetEP proc piPtr:DWORD
	comment ~
	Function Name: cbGetEP
	Function Description: This callback initialize the importer and returns the loaded base address. 
	Function Parameters:
		piPtr: DWORD
	~

	pushad
	mov eax, piPtr
	
	assume eax:ptr CREATE_PROCESS_DEBUG_INFO
		mov ebx, dword ptr[eax].lpBaseOfImage
		mov dwLoadedBaseAddress, ebx
	assume eax:nothing
	
	invoke SetCustomHandler, UE_CH_CREATEPROCESS, NULL
	
	mov ebx, dwLoadedBaseAddress
	add ebx, dwEntryPoint
	
	invoke SetBPX, ebx, UE_BREAKPOINT, cbInitCallBack
	invoke ImporterInit, 80 * 1024, dwLoadedBaseAddress
	
	popad
	ret
cbGetEP endp

OriginalEntryPointCB proc
	comment ~
	Function Name: OriginalEntryPointCB
	Function Description: This function is in charge of dump the process, relign the PE, copies
							the overlay data (if it is present) and does many other things related
							to re-build the binary to its original state.
	Function Parameters: None
	~

	LOCAL UnpackedOEP :DWORD
	LOCAL FileHandle :DWORD
	LOCAL FileSize :DWORD
	LOCAL FileMap :DWORD
	LOCAL FileMapVA :DWORD
	LOCAL NumberOfBytes :DWORD
	LOCAL OverlayStart :DWORD
	LOCAL OverlaySize :DWORD
	
	mov MAJOR_DEBUG_ERROR_EXIT,offset __MAJOR_DEBUG_ERROR_EXIT
	InstSEHFrame <offset SehHandler>
	
	invoke GetContextData, UE_EAX
	mov UnpackedOEP, eax
	
	invoke RtlZeroMemory, addr TempBuffer, 1024
	push UnpackedOEP
	push offset OepBPX
	push offset TempBuffer
	call wsprintf
	add esp, 12
	invoke LogMessage, addr TempBuffer
	
	invoke PastePEHeader, dword ptr[ProcessInfo.hProcess], dwLoadedBaseAddress, addr PathFileName
	invoke LogMessage, addr PasteHeaderMsg
	
	invoke GetSaveDialog
	.if FileSaveFlag == 1
		invoke DumpProcess, dword ptr[ProcessInfo.hProcess], dwLoadedBaseAddress, addr UnpackedFileNameBuffer, UnpackedOEP
		invoke LogMessage, addr DumpMsg
		
		invoke StopDebug
		
		invoke MapFileEx, addr UnpackedFileNameBuffer, NULL, addr FileHandle, addr FileSize, addr FileMap, addr FileMapVA
		
		.if FileMapVA > NULL 
			invoke ConvertVAtoFileOffset, FileMapVA, ebx, 1
		
			invoke ImporterCopyOriginalIAT, addr PathFileName, addr UnpackedFileNameBuffer  
			invoke LogMessage, addr IATFixedMsg
		
			.if bRealignPEFlag == TRUE
				invoke RealignPE, FileMapVA, FileSize, 2
				mov FileSize, eax
				invoke LogMessage, addr RealignPEMsg
			.endif
			
			invoke UnmapFileEx, FileHandle, FileSize, FileMap, FileMapVA
			invoke MakeAllSectionsRWE, addr UnpackedFileNameBuffer
			.if CopyOverlayDataFlag == 1
				invoke FindOverlay, addr TempBuffer, addr OverlayStart, addr OverlaySize
				.if eax == 1
					invoke CopyOverlay, addr TempBuffer, addr UnpackedFileNameBuffer
					invoke LogMessage, addr CopyOverlayMsg
				.endif
			.else
				invoke LogMessage, addr NoOverlayDetected
			.endif	
			invoke LogMessage, addr UnpackProcessDoneMsg
			KillSehFrame
		.else
			__MAJOR_DEBUG_ERROR_EXIT:
			KillSehFrame
			invoke ForceClose
			
			.if FileMapVA > NULL
				invoke UnmapFileEx, FileHandle, FileSize, FileMap, FileMapVA
			.endif
			
			invoke DeleteFile, addr UnpackedFileNameBuffer
			invoke LogMessage, addr FatalErrorMsg
			invoke LogMessage, addr EndUnpackMsg
		.endif
	.endif 
	ret

OriginalEntryPointCB endp

SehHandler proc C Except:DWORD,Frame:DWORD,Context:DWORD,Dispatch:DWORD
	comment ~
	Function Name: SehHandler
	Function Description: This function sets an exception handler.
	Function Parameters:
		Except: DWORD
		Frame: DWORD
		Context: DWORD
		Dispatch: DWORD
	~

	mov eax,Context
	assume eax:ptr CONTEXT
		push MAJOR_DEBUG_ERROR_EXIT
		pop [eax].regEip
		push SEH.OrgEsp
		pop [eax].regEsp
		push SEH.OrgEbp
		pop [eax].regEbp
		mov eax,ExceptionContinueExecution
	assume eax:nothing
	
SehHandler endp

MapFileEx proc fName:DWORD,ReadOrWrite:DWORD,FileHandle:DWORD,FileSize:DWORD,FileMap:DWORD,FileMapVA:DWORD
	comment ~
	Function Name: MapFileEx
	Function Description: This function creates a map file of a given file.
	Function Parameters:
		fName: DWORD
		ReadOrWrite: DWORD
		FileHandle: DWORD
		FileSize: DWORD
		FileMap: DWORD
		FileMapVA: DWORD
	~

	LOCAL Return :DWORD
	pushad
	mov Return,0
	invoke CreateFile,fName,GENERIC_READ+GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL
	.if eax == -1
		mov ebx,FileMapVA
		mov dword ptr[ebx],0
		mov Return,-1
		popad
		mov eax,Return
		ret
	.endif
	mov ebx,FileHandle
	mov dword ptr[ebx],eax
	invoke GetFileSize,eax,NULL
	mov ebx,FileSize
	mov dword ptr[ebx],eax
	mov eax,FileHandle
	invoke CreateFileMapping,dword ptr[eax],NULL,4,NULL,dword ptr[ebx],NULL
	mov ebx,FileMap
	mov dword ptr[ebx],eax
	invoke MapViewOfFile,dword ptr[ebx],2,NULL,NULL,NULL
	mov ebx,FileMapVA
	mov dword ptr[ebx],eax
	popad
	mov eax,Return
	ret
MapFileEx endp

UnmapFileEx proc FileHandle:DWORD,FileSize:DWORD,FileMap:DWORD,FileMapVA:DWORD
	comment ~
	Function Name: UnmapFileEx
	Function Description: This function erase the map file created by MapFileEx
	Function Parameters:
		FileHandle: DWORD
		FileSize: DWORD
		FileMap: DWORD
		FileMapVA: DWORD
	~

	pushad
	
	invoke UnmapViewOfFile,FileMapVA
	invoke CloseHandle,FileMap
	invoke SetFilePointer,FileHandle,FileSize,NULL,NULL
	invoke SetEndOfFile,FileHandle
	invoke CloseHandle,FileHandle
	
	popad
	ret
UnmapFileEx endp

end LibMain

comment ~
 OEP
0046B036    B8 B0714200     MOV EAX,UnPackMe.004271B0
0046B03B  - FFE0            JMP EAX                                  ; UnPackMe.004271B0
0046B03D    55              PUSH EBP
0046B03E    8BEC            MOV EBP,ESP
~
