; $Id: fuu.Asm 33 2010-07-11 22:24:00Z nahuelriva $

comment ~
Faster Universal Unpacker v0.1.1

Copyright (C) 2010 +NCR/CRC! [ReVeRsEr] http://crackinglandia.blogspot.com

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

FUU - Faster Universal Unpacker

Author: +NCR/CRC! [ReVeRsEr]
Date: Wednesday, June 28 th 2010

Every plugin will export these functions:

* GetPluginName - returns the plugin's name
DoUnpack - this routine does the magic to unpack :P

* DoUnpack will receive the path and filename, the
main dlg handle, an options array parameter, ID (FUU1) and lParam.

Thanks to all the people in CracksLatinoS!
for helping me answering my questions!

Special thanks to GUAN DE DIO and marciano

Hyperlink stuffs from: http://members.a1.net/ranmasaotome/masm32/Hyperlink.zip
~

.386
.model flat,stdcall
option casemap:none

include fuu.inc
; Hyperlink component
include Hyperlink.inc
; Externals
include .\External\Funciones.inc
include .\External\ListaDoble.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov    hInstance,eax
	
	invoke InitCommonControls
	invoke InitHyperLinkClass
	
	invoke GetCommandLine
	mov		CommandLine,eax
	
	invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	comment ~
	Function Name: WinMain
	Function Description: Creates the application's main UI 
	Function Parameters:
		hInst: HINSTANCE
		hPrevInst: HINSTANCE
		CmdLine: LPSTR
		CmdShow: DWORD
	~
	
	LOCAL	wc:WNDCLASSEX
	LOCAL	msg:MSG

	mov		wc.cbSize,sizeof WNDCLASSEX
	mov		wc.style,CS_HREDRAW or CS_VREDRAW
	mov		wc.lpfnWndProc,offset WndProc
	mov		wc.cbClsExtra,NULL
	mov		wc.cbWndExtra,DLGWINDOWEXTRA
	push	hInst
	pop		wc.hInstance
	mov		wc.hbrBackground,COLOR_BTNFACE+1
	mov		wc.lpszMenuName,IDM_MENU
	mov		wc.lpszClassName,offset ClassName
	
	invoke LoadIcon, hInstance, 500
	mov		wc.hIcon,eax
	mov		wc.hIconSm,eax
	
	invoke LoadCursor,NULL,IDC_ARROW
	mov		wc.hCursor,eax
	
	invoke RegisterClassEx,addr wc
	invoke CreateDialogParam,hInstance,IDD_DIALOG,NULL,addr WndProc,NULL
	
	invoke DragAcceptFiles, hWnd, TRUE
	
	invoke ShowWindow,hWnd,SW_SHOWNORMAL
	invoke UpdateWindow,hWnd
	.while TRUE
		invoke GetMessage,addr msg,NULL,0,0
	  .BREAK .if !eax
		invoke TranslateMessage,addr msg
		invoke DispatchMessage,addr msg
	.endw
	mov		eax,msg.wParam
	ret

WinMain endp

WndProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	comment ~
	Function Name: WndProc
	Function Description: Receive and process all WM. 
	Function Parameters:
		hWin: HWND
		uMsg: UINT
		wParam: WPARAM
		lParam: LPARAM
	~
	
	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		push	hWin
		pop		hWnd
		
		invoke Init, hWin, uMsg, wParam, lParam
			
	.elseif eax == WM_DROPFILES
		invoke DragQueryFile, wParam, NULL, addr GlobalBuffer, 1024
	;	mov IsFileSelected, 1
		invoke IsFile32Bits, addr GlobalBuffer
		.if eax == 1
			invoke SetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer
			invoke EnableWindow, hUnpackButton, TRUE
		.else
			invoke EnableWindow, hUnpackButton, FALSE
			invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
		.endif
	.elseif eax == WM_COMMAND
		mov		eax,wParam
		mov		edx,eax
		shr		edx,16
		and		eax,0FFFFh
		
		.if edx == BN_CLICKED
			.if ax==IDM_FILE_EXIT
				invoke SendMessage,hWin,WM_CLOSE,0,0
			.elseif ax == IDM_HELP_ABOUT
				invoke MessageBox,hWin,offset msgText, offset msgTitle, MB_OK
			.elseif ax == IDM_HELP_SUPPORT
				invoke ShellExecute, hWin, chr$("open"), chr$("http://groups.google.com/group/faster-universal-unpacker"), 0, 0, SW_SHOWNORMAL
			.elseif ax == IDM_HELP_HOME
				invoke ShellExecute, hWin, chr$("open"), chr$("http://code.google.com/p/fuu/"), 0, 0, SW_SHOWNORMAL 
			.elseif ax == IDM_TOOLS_CRYPTSIGN
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke DetectCryptoSignatures, hWin, addr GlobalBuffer, addr CryptoSignDllName
				.else
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
				.endif
			.elseif ax == IDM_TOOLS_DETECTOEP
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke DetectOEP, hWin, addr GlobalBuffer, addr GenOEPDllName
				.else
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
				.endif	
			.elseif ax == IDM_GENUNPACK
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke GenericUnpacker, hWin, addr GlobalBuffer, addr GenUnpackerDllName
				.else
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
				.endif		
			.elseif ax == IDM_IDENTIFY_SIGNATURE
				invoke SendMessage, hListBox, LB_RESETCONTENT, 0, 0
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke IdentifyPackerOrCompiler, hWin, addr GlobalBuffer, addr IdentifyPESignatureDllName
				.else
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
				.endif	
				
			.elseif ax == ExitBtn
				invoke SendMessage,hWin,WM_CLOSE,0,0
				
			.elseif ax == AboutBtn
				invoke MessageBox,hWin, offset msgText, offset msgTitle, MB_OK
			.elseif ax == RefreshBtn
				invoke SendMessage, hCombo, CB_RESETCONTENT, 0, 0
				invoke RefreshComboBox, hWin, uMsg, wParam, lParam
			.elseif ax == UnpackBtn
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke SendMessage, hListBox, LB_RESETCONTENT, NULL, NULL
					
					invoke IsDlgButtonChecked, hWin, RealignPECheckBox
					.if eax == BST_CHECKED
						mov eax, dword ptr[OptionsArray]
						mov dword ptr[eax], 1
					.else
						mov eax, dword ptr[OptionsArray]
						mov dword ptr[eax], 0
					.endif
					
					invoke IsDlgButtonChecked, hWin, CopyOverlayDataBt
					.if eax == BST_CHECKED
						mov eax, dword ptr[OptionsArray+4]
						mov dword ptr[eax], 1
					.else
						mov eax, dword ptr[OptionsArray+4]
						mov dword ptr[eax], 0
					.endif
					
					mov eax, current_selection
					.if current_selection != CB_ERR
						invoke InitializeUnpacker, hWin, addr GlobalBuffer, current_selection
					.else
						invoke MessageBox, hWin, offset SelectPluginError, offset ErrorMsgTitle, MB_ICONERROR
					.endif
				.elseif eax == 0
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
				.else
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, chr$("An unexpected error as occurred!"), chr$("Ooops! unexpected error!"), MB_ICONERROR
				.endif
				
			.elseif ax == BrowseFileBtn
				invoke GetFileDialog
				.if eax != 0
					invoke IsFile32Bits, addr GlobalBuffer
					.if eax == 1
						invoke SetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer
						invoke EnableWindow, hUnpackButton, TRUE
					.else
						
						.if eax == 0
							invoke MessageBox, hWin, chr$("The specified file is not a 32 bits PE file! (maybe PE+?)"), chr$("Not a PE32 file!"), MB_ICONERROR
						.else
							invoke MessageBox, hWin, chr$("An unexpected error as occurred!"), chr$("Ooops! unexpected error!"), MB_ICONERROR
						.endif
						invoke EnableWindow, hUnpackButton, FALSE
					.endif
				.endif
			.endif
		
		.elseif edx == CBN_SELCHANGE
			.if ax == PluginComboBox
				invoke SendMessage, hCombo, CB_GETCURSEL, 0, 0
				.if eax != CB_ERR
					mov current_selection, eax
				.endif
			.endif
		.elseif edx == EN_CHANGE
			.if ax == FileNameEdit
				
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile32Bits, addr GlobalBuffer
				.if eax == 1
					invoke EnableWindow, hUnpackButton, TRUE
				.else
					invoke EnableWindow, hUnpackButton, FALSE
				.endif
				
			.endif
		.endif
		
	.elseif eax==WM_CLOSE
		invoke DestroyHandles
		invoke DestroyWindow,hWin
		
	.elseif eax == WM_DESTROY
		invoke PostQuitMessage,NULL
	.else
		invoke DefWindowProc,hWin,uMsg,wParam,lParam
		ret
	.endif
	xor    eax,eax
	ret

WndProc endp

Init proc hWin:HWND, uMsg:UINT, wParam:LPARAM, lParam:LPARAM
	comment ~
	Function Name: Init
	Function Description: Create all the internal variables and data structures. 
	Function Parameters:
		hwin: HWND
		uMsg: UINT
		wParam: LPARAM
		CmdShow: LPARAM
	~
	
	invoke CrearListaDoble, sizeof PluginInfo
	.if eax == 0
		invoke MessageBox, hWin, chr$("INITERROR: Failed to build internal list object"), chr$("Initialize Error"), MB_ICONERROR 
		invoke ExitProcess, -1
	.endif
	
	mov hList, eax
	

	invoke CrearListaDoble, sizeof PluginInfo
	.if eax == 0
		invoke MessageBox, hWin, chr$("INITERROR: Failed to build internal list object"), chr$("Initialize Error"), MB_ICONERROR 
		invoke ExitProcess, -1
	.endif
	
	mov hAuxList, eax
	
	invoke GetHandlesOfControls, hWin
	
	invoke CheckDlgButton, hWin, RealignPECheckBox, BST_CHECKED
	invoke CheckDlgButton, hWin, CopyOverlayDataBt, BST_CHECKED
	
	invoke LoadPlugins, hWin, uMsg, wParam, lParam

	ret
Init endp 

IsFile32Bits proc szFilePath:DWORD
	comment ~
	Function Name: IsFile32Bits
	Function Description: Checks if a given file is a 32 bits executable 
	Function Parameters:
		szFilePath: DWORD   Pointer to ASCII String within Path of the target file
	~

	LOCAL hFile:HWND
	LOCAL FileSize:DWORD
	LOCAL lpNumberOfBytesRead:DWORD
	LOCAL pFileMemoryBuffer:DWORD
	
	invoke CreateFile, szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL
	.if eax != INVALID_HANDLE_VALUE
		mov hFile, eax
		invoke GetFileSize, hFile, NULL
		.if eax != INVALID_FILE_SIZE
			mov FileSize, eax
			invoke GlobalAlloc, GMEM_ZEROINIT, eax
			.if eax != NULL
				mov pFileMemoryBuffer, eax
				invoke ReadFile, hFile, dword ptr[pFileMemoryBuffer], dword ptr[FileSize], addr lpNumberOfBytesRead, NULL
				.if eax != 0
					mov eax, dword ptr[pFileMemoryBuffer]
					mov edx, eax
					mov ax, word ptr[eax]
					.if ax == 5A4Dh
						mov ebx, edx
						add edx, 3Ch ; offset to "Offset to PE signature" field
						mov edx, dword ptr[edx] ; offset to PE signature
						add ebx, edx ; PE Signature
						mov ax, word ptr[ebx]
						.if ax == 4550h 
							mov ax, word ptr[ebx+18h] ; Magic Number
							.if ax == 010bh
								invoke CloseHandle, dword ptr[hFile]
								invoke LocalFree, dword ptr[pFileMemoryBuffer]
								mov eax, 1
								ret
							.elseif ax == 020bh
								invoke CloseHandle, dword ptr[hFile]
								invoke LocalFree, dword ptr[pFileMemoryBuffer]
								mov eax, 0
								ret
							.else
								invoke CloseHandle, dword ptr[hFile]
								invoke LocalFree, dword ptr[pFileMemoryBuffer]
							.endif
						.else
					;		invoke MessageBox, hWnd, chr$("The file does not have a valid PE signature"), chr$("Bad PE signature"), MB_ICONERROR
							invoke CloseHandle, dword ptr[hFile]
							invoke LocalFree, dword ptr[pFileMemoryBuffer]
						.endif
					.else
					;	invoke MessageBox, hWnd, chr$("The specified file is not a valid PE file"), chr$("Not a valid PE file!"), MB_ICONERROR
						invoke CloseHandle, dword ptr[hFile]
						invoke LocalFree, dword ptr[pFileMemoryBuffer]
					.endif
				.else
				;	invoke MessageBox, hWnd, chr$("ReadFile Error: Cannot read the specified file!"), chr$("ReadFileError!"), MB_ICONERROR
					invoke CloseHandle, dword ptr[hFile]
					invoke LocalFree, dword ptr[pFileMemoryBuffer]
				.endif
			.else
			;	invoke MessageBox, hWnd, chr$("GlobalAlloc Error: Cannot allocate memory!"), chr$("No Memory!"), MB_ICONERROR
				invoke CloseHandle, dword ptr[hFile]
			.endif
		.else
		;	invoke MessageBox, hWnd, chr$("GetFileSize Error: INVALID_FILE_SIZE"), chr$("INVALID_FILE_SIZE"), MB_ICONERROR
			invoke CloseHandle, dword ptr[hFile]
		.endif
	.else
		;invoke MessageBox, hWnd, chr$("CreateFile Error: Cannot open the specified file!"), chr$("INVALID_HANDLE_VALUE"), MB_ICONERROR
	.endif
	xor eax, eax
	dec eax
	ret

IsFile32Bits endp

GetHandlesOfControls proc hWin:HWND
	comment ~
	Function Name: GetHandlesOfControls
	Function Description: Gets handles of every control in the UI 
	Function Parameters:
		hWin: HWND
	~
	
	invoke GetDlgItem, hWin, PluginComboBox
	mov hCombo,eax
	
	invoke GetDlgItem, hWin, OutputListBox
	mov hListBox, eax

	invoke GetDlgItem, hWin, EmailLink
	mov hEmailLink, eax
	
	invoke GetDlgItem, hWin, UnpackBtn
	mov hUnpackButton, eax
	
	invoke SetWindowText,hEmailLink,offset EmailAddress
	
	invoke SendMessage,hEmailLink,HLM_SETHOTCOLOR,0,0FF0000h
	invoke SendMessage,hEmailLink,HLM_SETTEXTCOLOR,0,0
	invoke SendMessage,hEmailLink,HLM_SETUNDERLINE,0,TRUE
	
	invoke SendMessage,hEmailLink,HLM_SETSUBJECT,0,offset Subject
	invoke SendMessage,hEmailLink,HLM_SETBODY,0,offset Body

	invoke SendMessage,hEmailLink,HLM_SETTYPE,0,HLINK_EMAIL
	
	invoke GetDlgItem, hWin, BlogLinkClickable
	mov hBlogLink, eax
	
	invoke SetWindowText, hBlogLink, offset CrackinglandiaLink
	invoke SendMessage, hBlogLink,HLM_SETHOTCOLOR,0,0FF0000h
	invoke SendMessage, hBlogLink,HLM_SETTEXTCOLOR,0,0
	invoke SendMessage, hBlogLink,HLM_SETTYPE,0,HLINK_URL 
	ret

GetHandlesOfControls endp

DestroyHandles proc
	comment ~
	Function Name: DestroyHandles
	Function Description: Close all handles opened by the application 
	Function Parameters: None
	~
	
	invoke BorrarListaDoble,hList
	invoke BorrarListaDoble,hAuxList
	invoke CloseHandle, hListBox
	invoke CloseHandle, hCombo
	invoke CloseHandle, fHandle
	invoke CloseHandle, hModule
	invoke CloseHandle, hBlogLink
	invoke CloseHandle, hInstance
	invoke CloseHandle, hEmailLink
	invoke CloseHandle, hWnd
	;invoke CloseHandle, hTahoma
	ret

DestroyHandles endp

GetFileDialog proc
	comment ~
	Function Name: GetFileDialog
	Function Description: Create the File Dialog window 
	Function Parameters: None
	~
	
;	pushad
	mov ofn.lStructSize,sizeof ofn
	mov ofn.lpstrFilter,offset FilterString
	mov ofn.lpstrFile,offset GlobalBuffer
	mov ofn.nMaxFile,1024
	mov ofn.Flags, OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST or OFN_LONGNAMES or OFN_EXPLORER or OFN_HIDEREADONLY
	mov ofn.lpstrTitle,offset AppName
	mov ofn.lpstrInitialDir, NULL
	invoke GetOpenFileName,addr ofn
;	.if eax != 0
;		mov IsFileSelected, 1  Try to avoid global variables
;	.endif
;	popad
	ret

GetFileDialog endp

InitializeUnpacker proc hWin:HWND,FileName:DWORD,CurrentSelection:DWORD
	comment ~
	Function Name: InitializeUnpacker
	Function Description: This function calls the DoUnpack method of the selected plugin 
	Function Parameters:
		hWin: HWND
		FileName: DWORD  Pointer to ASCII String
		CurrentSelection: DWORD  Index using by the ComboBox
	~

;	.if IsFileSelected == 1   The checking is done before calling the function
		mov eax, CurrentSelection
		invoke GetItemByIndex, eax
		.if eax != NULL
			push 0
			push offset FUUID
			push offset OptionsArray
			push FileName
			push hWin
			call eax
		.else
			invoke MessageBox, hWin, chr$("Error: Selection Error!"), chr$("Error"), MB_ICONERROR
		.endif		
;	.else
;		invoke MessageBox, hWin, offset SelectionFileErrorMsg, offset ErrorMsg, MB_ICONERROR
;	.endif
	ret

InitializeUnpacker endp

GetItemByIndex proc Index:DWORD
	comment ~
	Function Name: GetItemByIndex
	Function Description: Returns the item pointed by lpIndex. 
	Function Parameters:
		Index: DWORD 
	~

	LOCAL TempBuff:PluginInfo
	
	invoke ItemPosByIndexListaDoble, hList, Index
	mov ebx,eax
	invoke RecuperarItemListaDoble, hList, ebx , addr TempBuff	
	
	mov eax, TempBuff.DoUnpackAddr
	ret

GetItemByIndex endp

RefreshComboBox proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	comment ~
	Function Name: RefreshComboBox
	Function Description: Refresh the ComboBox control when the 'Refresh' button is pressed
	Function Parameters: 
		hWin: HWND
		uMsg: UINT
		wParam: WPARAM
		lParam: LPARAM
	~
	
	invoke VaciarListaDoble, hList
	invoke LoadPlugins, hWin, uMsg, wParam, lParam
	ret

RefreshComboBox endp

DetectCryptoSignatures proc hWin:HWND, szFileName:DWORD, szDllName:DWORD
	comment ~
	Function Name: DetectCryptoSignatures
	Function Description: Loads the DetectCryptoSignatures plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~

	invoke DoJob, hWin, szFileName, szDllName
	ret
	
DetectCryptoSignatures endp

DetectOEP proc hWin:HWND, szFileName:DWORD, szDllName:DWORD
	comment ~
	Function Name: DetectOEP
	Function Description: Loads the DetectOEP plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	
	invoke DoJob, hWin, szFileName, szDllName
	ret
	
DetectOEP endp

GenericUnpacker proc hWin:HWND, szFileName:DWORD, szDllName:DWORD
	comment ~
	Function Name: GenericUnpacker
	Function Description: Loads the GenericUnpacker plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	
	invoke DoJob, hWin, szFileName, szDllName
	ret

GenericUnpacker endp

IdentifyPackerOrCompiler proc hWin:HWND, szFileName:DWORD, szDllName:DWORD
	comment ~
	Function Name: IdentifyPackerOrCompiler
	Function Description: Loads the SignatureDetector plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	
	invoke DoJob, hWin, szFileName, szDllName
	ret

IdentifyPackerOrCompiler endp

DoJob proc hWin:HWND, szFileName:DWORD, szDllName:DWORD
	comment ~
	Function Name: DoJob
	Function Description: This function calls the DoJob method for the selected plugin tool 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	
	;.if IsFileSelected == 1   The checking is done before calling the function
		invoke GetModuleFileName, hInstance, addr CurrentDir, MAX_PATH
		
		mov esi, offset CurrentDir
		invoke lstrlen, esi
		add esi, eax
		.while byte ptr[esi] != "\"
			mov byte ptr [esi], 0
			dec esi
			dec eax
		.endw
		
		sub esi, eax
		
		invoke lstrlen, esi
		inc eax
		
		.if eax < MAX_PATH
			invoke lstrcpy, addr ToolsDir, addr CurrentDir
			invoke lstrlen, addr ToolsDir
			inc eax
			.if eax < MAX_PATH
				invoke lstrcat, addr ToolsDir, addr ToolsDirName
				invoke lstrlen, addr ToolsDir
				inc eax
				.if eax < MAX_PATH
					lea esi, ToolsDir
					add esi, eax
					dec esi
					mov byte ptr[esi], 05ch
					
					invoke lstrlen, addr ToolsDir
					inc eax 
					.if eax < MAX_PATH
						invoke lstrcat, addr ToolsDir, szDllName
					
						invoke LoadLibrary, addr ToolsDir
						.if eax != NULL
							mov hModule, eax
							
							invoke GetProcAddress, eax, addr DoMyJobProcName
							
							.if eax != NULL
								push 0
								push 50456944h ; PluginID
								push szFileName
								push hWin
								call eax
								
								invoke FreeLibrary, hModule
								
								invoke FreeString, addr CurrentDir
								invoke FreeString, addr ToolsDir
								
								.if eax == 0
									invoke MessageBox, hWin, chr$("Error: FreeLibrary Failed!"), chr$("Error freeing library"), MB_ICONERROR
								.endif
							.else
								invoke MessageBox, hWin, chr$("Error: GetProcAddress Failed!"), chr$("Error loading function"), MB_ICONERROR
							.endif
						.else
							invoke MessageBox, hWin, chr$("Error: LoadLibrary Failed!"), chr$("Error loading library"), MB_ICONERROR
						.endif
					.endif				
				.endif
			.endif
		.endif		
	;.else
	;	invoke MessageBox, hWin, offset SelectionFileErrorMsg, offset ErrorMsg, MB_ICONERROR
	;.endif
	
	ret
	
DoJob endp

FreeString proc szString:DWORD
	comment ~
	Function Name: FreeString
	Function Description: Clear a buffer with a string 
	Function Parameters: 
		szString: DWORD  (ASCII String Pointer)
	~
	
	mov esi, szString
	.while byte ptr[esi] != 0
		mov byte ptr[esi], 0
		inc esi
	.endw
	
	ret

FreeString endp

InsertItemInList proc List:DWORD, lpItem:DWORD
	comment ~
	Function Name: InsertItemInList
	Function Description: Insert a given item into a list 
	Function Parameters: 
		List: Handler of the list
		lpItem: DWORD (Point to  PluginInfo)
	~
	
	invoke UltimoNodoListaDoble, List
	invoke AnadirItemListaDoble, List, lpItem, eax

	ret

InsertItemInList endp

LoadPlugins proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	comment ~
	Function Name: LoadPlugins
	Function Description: This function loads the application plugins
	Function Parameters: 
		hWin: HWND
		uMsg: UINT
		wParam: WPARAM
		lParam: LPARAM
	~
	
	LOCAL findData:WIN32_FIND_DATA
	
	invoke GetModuleFileName, hInstance, addr CurrentDir, MAX_PATH

	mov esi, offset CurrentDir
	invoke lstrlen, esi
	add esi, eax
	.while byte ptr[esi] != "\"
		mov byte ptr [esi], 0
		dec esi
		dec eax
	.endw
	
	sub esi, eax
	
	invoke lstrlen, esi
	
	.if eax < MAX_PATH
		invoke lstrcat, esi, addr Pluginsx86DirName
		invoke SetCurrentDirectory, esi  
	
		invoke FindFirstFile,addr fPattern, addr findData
		.if eax != INVALID_HANDLE_VALUE
			mov fHandle, eax
			.while eax !=0
				invoke LoadLibrary,addr findData.cFileName
				.if eax != NULL
					mov hModule, eax
					invoke GetProcAddress,eax, offset DoUnpackName
					.if eax != NULL
						mov PIList.DoUnpackAddr, eax
						invoke GetProcAddress, hModule, offset GetPluginName
						.if eax != NULL
							mov PIList.GetPlugNameAddr, eax
							
							mov ebx, counter
							inc ebx
							mov PIList.Index, ebx
							
							invoke lstrlen,addr findData.cFileName
							inc eax
							.if eax < MAX_PATH
								invoke lstrcpyn,addr PIList.DllName, addr findData.cFileName, eax
								
								call PIList.GetPlugNameAddr
								mov ebx, eax
								invoke lstrlen,eax
								inc eax
								.if eax < MAX_PATH
									invoke lstrcpyn,addr PIList.PluginName, ebx, eax
									
									invoke SendMessage, hCombo, CB_ADDSTRING, 0, ebx
									
									invoke InsertItemInList, hList, addr PIList
									
								.endif
							.endif
						.endif 
					.endif
				.endif
				invoke FindNextFile, fHandle, addr findData
			.endw
		.else
			invoke MessageBox, hWin, offset ErrorMsgText, offset ErrorMsgTitle, MB_ICONERROR
		.endif
	.endif
	
	invoke FreeString, addr CurrentDir
	
	ret

LoadPlugins endp


end start
