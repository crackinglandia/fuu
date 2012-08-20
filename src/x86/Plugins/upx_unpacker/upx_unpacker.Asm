; $Id: upx_unpacker.Asm 43 2010-07-11 22:41:24Z nahuelriva $

comment ~
   UPX Unpacker for UPX 1.x - 3.x

   Copyright (C) 2010 ReversingLabs www.reversinglabs.com

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



	---------------------------------------------
	Modified version by +NCR/CRC! [ReVeRsEr]
	---------------------------------------------

[Supported Versions]
* UPX 1.x - 3.x

[Changelog]
* First stable version

[Known Limitations]
* It has some problems with file packed with UPX 1.24

~

.586
.model flat, stdcall
option casemap:none

include upx_unpacker.inc

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
	
	mov RealignPEFlag, eax
	mov CopyOverlayDataFlag, ebx
	
	mov eax, szFname
	invoke lstrlen, eax
	inc eax
	.if eax < 1024
		invoke lstrcpyn, addr PathFileName, szFname, eax 
	.endif
	
	invoke GetControlHandle, hMainDlg
	
	invoke GetUnpackerFolder
	
	invoke LogMessage, addr StartMsg
	invoke LogMessage, addr StartUnpackProcessMsg
	
	invoke _DoUnpack, hMainDlg, szFname, cbFindPatterns, lpReserved, lpParam
	ret
	
DoUnpack endp

_DoUnpack proc hMainDlg:DWORD, szFname:DWORD, dwCallBack:DWORD, lpReserved:DWORD, lpParam:DWORD
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
	mov eax, szFname
	.if eax != NULL && byte ptr[eax] != NULL
		invoke IsPE32FileValidEx, szFname, UE_DEPTH_DEEP, NULL
		
		.if eax == 1
			invoke GetPE32Data,szFname,NULL,UE_IMAGEBASE
			mov ImageBase,eax
			
			invoke GetPE32Data,szFname,NULL,UE_OEP
			mov EntryPoint,eax
			
			invoke GetPE32Data,szFname,NULL,UE_SIZEOFIMAGE
			mov SizeOfImage,eax
			
			invoke GetPE32Data, szFname, NULL, UE_SECTIONVIRTUALOFFSET
			mov SnapshootMemoryStartRVA, eax
			mov eax, EntryPoint
			sub eax, SnapshootMemoryStartRVA
			mov SnapShootMemorySize, eax
			
			invoke IsFileDLL, szFname, NULL
			mov _IsFileDll, al
			
			.if _IsFileDll == NULL
				invoke InitDebug, szFname, NULL, NULL
			.elseif _IsFileDll == 1
				invoke lstrcpy, addr SnapShoot1, addr UnpackerFolder
				invoke lstrcat, addr SnapShoot1, addr szSnapShoot1Name
				
				invoke lstrcpy, addr SnapShoot2, addr UnpackerFolder
				invoke lstrcat, addr SnapShoot2, addr szSnapShoot2Name
				
				invoke InitDLLDebug, szFname, 1, NULL, NULL, addr cbFindPatterns
				invoke DeleteFile, addr SnapShoot1
				invoke DeleteFile, addr SnapShoot2
			.else
				xor eax, eax
			.endif
			
			.if eax != NULL
				mov ebx, eax
				mov eax, dwCallBack
				mov cbInitCallBack, eax
				
				invoke RtlMoveMemory, addr ProcessInfo, ebx, sizeof PROCESS_INFORMATION
				.if _IsFileDll == NULL
					invoke SetCustomHandler,UE_CH_CREATEPROCESS,addr cbGetEP
				.endif
				invoke DebugLoop
			.else
				invoke LogMessage, addr ErrorMsg
				invoke LogMessage, addr EndUnpackMsg
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
	mov ofn.lpstrFile,offset GlobalBuffer
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
		mov LoadedBaseAddress, ebx
	assume eax:nothing
	invoke SetCustomHandler, UE_CH_CREATEPROCESS, NULL
	mov ebx, LoadedBaseAddress
	add ebx, EntryPoint
	invoke SetBPX, ebx, UE_BREAKPOINT, cbInitCallBack
	invoke ImporterInit, 80 * 1024, LoadedBaseAddress
	popad
	ret
cbGetEP endp

GetControlHandle proc hWin:HWND
	comment ~
	Function Name: GetControlHandle
	Function Description: Returns the handle of the main window.
	Function Parameters:
		hWin: DWORD
	~

	invoke FindWindowEx, hWin, NULL, offset ListBoxClassName, NULL
	.if eax != NULL
		mov hControl, eax
	.endif
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

cbFindPatterns proc
	comment ~
	Function Name: cbFindPatterns
	Function Description: This function check for a given pattern in the runnning process.
							It is used to check if the given .exe or .dll is packed with the
							packer you selected.
	Function Parameters: None
	~

	LOCAL MemInfo: MEMORY_BASIC_INFORMATION
	LOCAL Flag: DWORD
	
	pushad
	.if _IsFileDll == 1
		invoke GetDebuggedDLLBaseAddress
		mov LoadedBaseAddress, eax
		
		invoke ImporterInit, 50 * 1024, LoadedBaseAddress
		invoke RelocaterInit, 100 * 1024, ImageBase, LoadedBaseAddress
	.endif
	
	mov esi, LoadedBaseAddress
	add esi, EntryPoint
	
	invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], esi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
	mov edi, dword ptr[MemInfo.BaseAddress]
	add edi, dword ptr[MemInfo.RegionSize]
	
	invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], edi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
	add edi, dword ptr[MemInfo.RegionSize]
	sub edi, esi

	.if eax != NULL
	
		invoke Find, esi, edi, addr Pattern1, Pattern1Size, addr WildCard
		.if eax != NULL
			mov ebx, eax
			mov Pattern1BP, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, Pattern1CallBack
		.else
			invoke LogMessage, addr PossibleNotPackedError
			invoke LogMessage, addr EndUnpackMsg
			invoke StopDebug
			inc Flag
		.endif
		
		invoke Find, esi, edi, addr Pattern2, Pattern2Size, addr WildCard
		.if eax != NULL
			mov ebx, eax
			mov Pattern2BP, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, Pattern2CallBack
		.endif
		
		invoke Find, esi, edi, addr Pattern3, Pattern3Size, addr WildCard
		.if eax != NULL
			mov ebx, eax
			mov Pattern3BP, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, Pattern3CallBack
		.else
			.if Flag == NULL
				invoke LogMessage, addr PossibleNotPackedError
				invoke LogMessage, addr EndUnpackMsg
				invoke StopDebug
				inc Flag		
			.endif
		.endif
		
		invoke Find, esi, edi, addr Pattern4, Pattern4Size, addr WildCard
		.if eax != NULL
			mov ebx, eax
			add ebx, 2
			mov Pattern4BP, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, Pattern4CallBack
		.endif
		
		invoke Find, esi, edi, addr Pattern5, Pattern5Size, addr WildCard
		.if eax != NULL
			mov ebx, eax
			inc ebx
			mov Pattern5BP, ebx
			invoke SetBPX, ebx, UE_BREAKPOINT, Pattern5CallBack
		.else
			invoke Find, esi, edi, addr Pattern6, Pattern6Size, addr WildCard
			.if eax != NULL
				mov ebx, eax
				add ebx, 3
				mov Pattern6BP, ebx
				invoke SetBPX, ebx, UE_BREAKPOINT, Pattern6CallBack
			.else
				.if Flag == NULL
					invoke LogMessage, addr PossibleNotPackedError
					invoke LogMessage, addr EndUnpackMsg	
					invoke StopDebug
					inc Flag
				.endif
			.endif
		.endif
		
		.if _IsFileDll == 1
			invoke Find, esi, edi, addr Pattern7, Pattern7Size, addr WildCard
			.if eax != NULL
				mov ebx, eax
				sub ebx, 3
				mov Pattern7BP, ebx
				invoke SetBPX, ebx, UE_BREAKPOINT, Pattern7CallBack
			.else
				.if Flag == NULL
					invoke LogMessage, addr PossibleNotPackedError
					invoke LogMessage, addr EndUnpackMsg
					invoke StopDebug
					inc Flag
				.endif
			.endif
		.endif
	.endif
	
	popad
	ret

cbFindPatterns endp

LoadLibraryCallBack proc
	comment ~
	Function Name: LoadLibraryCallBack
	Function Description: This is the callback where the plugin gets the libraries imported
							by the packed program in order to re-build the IAT later on.
	Function Parameters: None
	~
	
	LOCAL MemInfo: MEMORY_BASIC_INFORMATION
	LOCAL NumberOfBytes: DWORD
	
	pushad
	xor esi, esi
	invoke GetContextData, UE_EIP
	.if eax	 == Pattern1BP
		invoke GetContextData, UE_EAX
		mov esi, eax
	.endif
	
	.if esi > LoadedBaseAddress
		invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], esi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
		mov edi, dword ptr[MemInfo.BaseAddress]
		add edi, dword ptr[MemInfo.RegionSize]
		
		invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], edi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
		add edi, dword ptr[MemInfo.RegionSize]
		sub edi, esi
		.if edi > 256
			mov edi, 256
		.endif
		 
		invoke ReadProcessMemory, dword ptr[ProcessInfo.hProcess], esi, addr StringData, edi, addr NumberOfBytes
		.if eax != NULL
			invoke ImporterAddNewDll, addr StringData, NULL
			invoke RtlZeroMemory, addr TempBuffer, 1024
			push offset StringData
			push offset LoadLibraryBPX
			push offset TempBuffer
			call wsprintf
			add esp, 12
			invoke LogMessage, addr TempBuffer 
		.endif
	.endif
	popad
	ret

LoadLibraryCallBack endp

GetProcAddressCallBack proc
	comment ~
	Function Name: GetProcAddressCallBack
	Function Description: This function gets all the imported APIs used by the packed program
							in order to re-build the IAT later on.
	Function Parameters: None
	~
	
	LOCAL MemInfo: MEMORY_BASIC_INFORMATION
	LOCAL NumberOfBytes: DWORD
	
	pushad
	xor esi, esi
	invoke GetContextData, UE_EIP
	.if eax == Pattern2BP
		invoke GetContextData, UE_EAX
		mov esi, eax
		invoke GetContextData, UE_EBX
		mov ebx, eax
	.elseif eax == Pattern3BP
		invoke GetContextData, UE_EDI
		mov esi, eax
		invoke GetContextData, UE_EBX
		mov ebx, eax
	.elseif eax == Pattern4BP
		invoke GetContextData, UE_EDI
		mov esi, eax
		invoke GetContextData, UE_EBX
		mov ebx, eax 
	.endif
	
	.if esi > LoadedBaseAddress
		invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], esi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
		mov edi, dword ptr[MemInfo.BaseAddress]
		add edi, dword ptr[MemInfo.RegionSize]
		
		invoke VirtualQueryEx, dword ptr[ProcessInfo.hProcess], edi, addr MemInfo, sizeof MEMORY_BASIC_INFORMATION
		add edi, dword ptr[MemInfo.RegionSize]
		sub edi, esi
		.if edi > 256
			mov edi, 256
		.endif
		
		invoke ReadProcessMemory, dword ptr[ProcessInfo.hProcess], esi, addr StringData, edi, addr NumberOfBytes
		.if eax != NULL
			invoke ImporterAddNewAPI, addr StringData, ebx
			invoke RtlZeroMemory, addr TempBuffer, 1024
			
			push offset StringData
			push offset GetProcAddressBPX
			push offset TempBuffer
			call wsprintf
			add esp, 12
			invoke LogMessage, addr TempBuffer
		.endif
	.else
		invoke ImporterAddNewAPI, esi, ebx
		invoke RtlZeroMemory, addr TempBuffer, 1024
		
		push esi
		push offset GetProcAddrBPX
		push offset TempBuffer
		call wsprintf
		add esp, 12
		
		invoke LogMessage, addr TempBuffer
	.endif
	popad
	ret

GetProcAddressCallBack endp

EntryPointCallBack proc
	comment ~
	Function Name: EntryPointCallBack
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
	
	invoke GetContextData, UE_EIP
	lea esi, dword ptr[eax+1]
	invoke ReadProcessMemory, dword ptr[ProcessInfo.hProcess], esi, addr UnpackedOEP, 4, addr NumberOfBytes
	add UnpackedOEP, esi
	add UnpackedOEP, 4
	
	invoke RtlZeroMemory, addr TempBuffer, 1024
	push UnpackedOEP
	push offset OepBPX
	push offset TempBuffer
	call wsprintf
	add esp, 12
	invoke LogMessage, addr TempBuffer
	
	.if _IsFileDll != 1
		invoke PastePEHeader, dword ptr[ProcessInfo.hProcess], LoadedBaseAddress, addr PathFileName
		invoke LogMessage, addr PasteHeaderMsg
	.else
		mov esi, SnapshootMemoryStartRVA
		add esi, LoadedBaseAddress
		.if SeconSnapShootOnEP == 1
			invoke RelocaterMakeSnapshot, dword ptr[ProcessInfo.hProcess], addr SnapShoot2, esi,SnapShootMemorySize
		.endif
		invoke RelocaterCompareTwoSnapshots, dword ptr[ProcessInfo.hProcess], LoadedBaseAddress, SizeOfImage, addr SnapShoot1, addr SnapShoot2, esi
	.endif
	
	invoke GetSaveDialog
	.if FileSaveFlag == 1
	
		invoke DumpProcess, dword ptr[ProcessInfo.hProcess], LoadedBaseAddress, addr GlobalBuffer, UnpackedOEP
		invoke LogMessage, addr DumpMsg
		
		invoke StopDebug
		invoke ImporterEstimatedSize
		lea ebx, dword ptr[eax+200]
		invoke AddNewSection, addr GlobalBuffer, addr MySection, ebx
		add eax, LoadedBaseAddress
		mov ebx, eax
		
		.if _IsFileDll == 1
			invoke RelocaterEstimatedSize
			lea ecx, dword ptr[eax+200]
			invoke AddNewSection, addr GlobalBuffer, addr MySection, ecx
			mov edi, eax
			mov esi, eax
		.endif
		
		invoke MapFileEx, addr GlobalBuffer, NULL, addr FileHandle, addr FileSize, addr FileMap, addr FileMapVA
		.if FileMapVA > NULL 
			invoke ConvertVAtoFileOffset, FileMapVA, ebx, 1
			mov ebx, eax
			
			invoke ImporterExportIAT, ebx, FileMapVA
			invoke LogMessage, addr IATFixedMsg
			
			.if _IsFileDll == 1
				add esi, FileMapVA
				invoke RelocaterExportRelocation, esi, edi, FileMapVA
				invoke LogMessage, addr ExportRelocationMsg
			.endif
			
			.if RealignPEFlag == TRUE
				invoke RealignPE, FileMapVA, FileSize, 2
				mov FileSize, eax
				invoke LogMessage, addr RealignPEMsg
			.endif
			
			invoke UnmapFileEx, FileHandle, FileSize, FileMap, FileMapVA
			invoke MakeAllSectionsRWE, addr GlobalBuffer
			
			.if _IsFileDll == 1
				invoke RelocaterChangeFileBase, addr GlobalBuffer, ImageBase
				invoke LogMessage, addr RelocationChangeBaseMsg
			.endif
			
			.if CopyOverlayDataFlag == TRUE
				invoke FindOverlay, addr TempBuffer, addr OverlayStart, addr OverlaySize
				.if eax == 1
					invoke CopyOverlay, addr TempBuffer, addr GlobalBuffer
					invoke LogMessage, addr CopyOverlayMsg
				.else
					invoke LogMessage, addr NoOverlayDetected
				.endif
			.endif
			
			invoke LogMessage, addr UnpackProcessDoneMsg
			
			KillSehFrame
		.else
			__MAJOR_DEBUG_ERROR_EXIT:
			KillSehFrame
			invoke ForceClose
			invoke ImporterCleanup
			
			.if FileMapVA > NULL
				invoke UnmapFileEx, FileHandle, FileSize, FileMap, FileMapVA
			.endif
			
			invoke DeleteFile, addr GlobalBuffer
			invoke LogMessage, addr FatalErrorMsg
			invoke LogMessage, addr EndUnpackMsg
		.endif
	.endif 
	ret

EntryPointCallBack endp

SnapShoot1CallBack proc
	comment ~
	Function Name: SnapShoot1CallBack
	Function Description: This function takes a snapshoot of the running process.
	Function Parameters: None
	~
	
	pushad
	
	mov esi,SnapshootMemoryStartRVA
	add esi,LoadedBaseAddress
	invoke RelocaterMakeSnapshot,dword ptr[ProcessInfo.hProcess],addr SnapShoot1,esi,SnapShootMemorySize
	
	popad
	ret

SnapShoot1CallBack endp

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
