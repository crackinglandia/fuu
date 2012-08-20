; $Id: FUU.Asm 85 2010-07-27 15:26:16Z guan.dedio@gmail.com $

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

Hyperlink stuffs from: http://members.a1.net/ranmasaotome/masm32/Hyperlink.zip and 
translated to 64bits version
~

include FUU.inc
include Hiperlink.inc

include ..\External\funciones64.inc
include ..\External\ListaDoble64.inc
include CommunicationPlugin.inc



.code

function main

	invoke GetModuleHandle,NULL
	mov hInstance,rax
	
	invoke InitCommonControls
	
	invoke InitHyperLinkClass
	
	invoke GetCommandLine  ; Esto por el momento no vale para nada lo dejo por simulitud con el de la versión 32 o una futura ampliacion
	mov		CommandLine,rax
	
	
	invoke DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL

	invoke ExitProcess,0
exitf

;########################################################################

function DlgProc,hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	comment ~
	Function Name: DlgProc
	Function Description: Receive and process all WM. 
	Function Parameters:
		hWin: HWND
		uMsg: UINT
		wParam: WPARAM
		lParam: LPARAM
	~
	
	xor rax,rax
	mov eax,uMsg
	
	@IF <<cmp eax,WM_INITDIALOG>>, EQUAL?
		mov rax,hWin
		mov hMainHanlde,rax
		invoke Init, hWin, uMsg, wParam, lParam
		
	@ELSEIF <<cmp eax,WM_DROPFILES>>,EQUAL?
				
		invoke DragQueryFile, wParam, 0, addr GlobalBuffer, 1024
		invoke IsFile64Bits, addr GlobalBuffer
		@IF <<cmp rax, 20h>>,EQUAL?
			
			invoke SetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer
			invoke EnableWindow, hUnpackButton, TRUE ; Ver esto 
		@ELSE
			invoke EnableWindow, hUnpackButton, FALSE
			invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
		@ENDIF
	@ELSEIF <<cmp eax,WM_COMMAND>>,EQUAL?
		mov		eax,wParam
		mov		edx,eax
		shr		edx,16
		@IF <<cmp edx,BN_CLICKED>>,EQUAL?
			;Exit
			@IF <<cmp ax,IDM_FILE_EXIT>>,EQUAL?
				invoke SendMessage,hWin,WM_CLOSE,0,0
			@ELSEIF <<cmp ax, ExitBtn>>,EQUAL?
				invoke SendMessage,hWin,WM_CLOSE,0,0
			
			@ELSEIF <<cmp ax,IDM_HELP_SUPPORT>>,EQUAL?
			
				invoke ShellExecute, hWin,addr szOpen, addr szFUUGoogleGrupo, 0, 0, SW_SHOWNORMAL
	
			@ELSEIF <<cmp ax, IDM_HELP_HOME>>,EQUAL?
				invoke ShellExecute, hWin, addr szOpen, addr szFUUWEB, 0, 0, SW_SHOWNORMAL 
			
			;About
			@ELSEIF <<cmp ax,IDM_HELP_ABOUT>>,EQUAL?
				invoke MessageBox,hWin,addr msgText, addr msgTitle, MB_OK
			
			@ELSEIF <<cmp ax,AboutBtn>>,EQUAL?
				invoke MessageBox,hWin,addr  msgText,addr msgTitle, MB_OK
		
			; others
			@ELSEIF <<cmp ax,IDM_TOOLS_CRYPTSIGN>>,EQUAL?
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					;mov IsFileSelected, 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke DetectCryptoSignatures, hWin, addr GlobalBuffer, addr CryptoSignDllName		
				@ELSE
					;mov IsFileSelected, 0
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
				@ENDIF
				
			@ELSEIF <<cmp ax,IDM_TOOLS_DETECTOEP>>,EQUAL?
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					;mov IsFileSelected, 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke DetectOEP, hWin, addr GlobalBuffer, addr GenOEPDllName		
				@ELSE
					;mov IsFileSelected, 0
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
				@ENDIF
		
				
			@ELSEIF <<cmp ax,IDM_GENUNPACK>>,EQUAL?
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					;mov IsFileSelected, 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke GenericUnpacker, hWin, addr GlobalBuffer, addr GenUnpackerDllName		
				@ELSE
					;mov IsFileSelected, 0
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
				@ENDIF

				
			@ELSEIF <<cmp ax,IDM_IDENTIFY_SIGNATURE>>,EQUAL?
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					;mov IsFileSelected, 1
					invoke EnableWindow, hUnpackButton, TRUE
					invoke IdentifyPackerOrCompiler, hWin, addr GlobalBuffer, addr IdentifyPESignatureDllName		
				@ELSE
					;mov IsFileSelected, 0
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
				@ENDIF
			
			@ELSEIF << cmp ax,RefreshBtn>>,EQUAL?
				invoke SendMessage, hCombo, CB_RESETCONTENT, 0, 0
				invoke RefreshComboBox
		
			@ELSEIF <<cmp ax,UnpackBtn>>,EQUAL?
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					invoke EnableWindow, hUnpackButton, TRUE
					invoke SendMessage, hListBox, LB_RESETCONTENT, NULL, NULL
				
				;************************************************************
					invoke IsDlgButtonChecked, hWin, RealignPECheckBox
					@IF <<cmp eax,BST_CHECKED>>,EQUAL?	 
						mov rax, qword ptr[OptionsArray]
						mov dword ptr[rax],1
					@ELSE
						mov rax, qword ptr[OptionsArray]
						mov dword ptr[rax],0
					@ENDIF
					
					invoke IsDlgButtonChecked, hWin, CopyOverlayDataBt
					@IF<<cmp eax,BST_CHECKED>>,EQUAL?
						mov rax, qword ptr[OptionsArray+8]
						mov dword ptr[rax],1
					@ELSE
						mov rax, qword ptr[OptionsArray+8]
						mov dword ptr[rax],0
					@ENDIF
				;************************************************************
				
					mov rax, current_selection
				
					@IF <<cmp rax,CB_ERR>>,NOEQUAL?
						invoke InitializeUnpacker, hWin, addr GlobalBuffer, current_selection		
					@ELSE
						invoke MessageBox, hWin, addr SelectPluginError, addr ErrorMsgTitle, MB_ICONERROR
					@ENDIF
				@ELSE
					invoke EnableWindow, hUnpackButton, FALSE
					invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
				@ENDIF
			
			@ELSEIF<< cmp ax,BrowseFileBtn>>,EQUAL?
				invoke GetFileDialog
				@IF <<cmp rax,0>>,NOEQUAL?
					invoke IsFile64Bits, addr GlobalBuffer
					@IF <<cmp rax, 20h>>,EQUAL?
						
						invoke SetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer
						invoke EnableWindow, hUnpackButton, TRUE
					@ELSE
						invoke MessageBox, hWin, addr NotPEPlusFile, addr ErrorMsg, MB_ICONERROR
						invoke EnableWindow, hUnpackButton, FALSE
					@ENDIF
				@ENDIF
			@ENDIF	
		@ELSEIF <<cmp edx,CBN_SELCHANGE>>,EQUAL?	
			@IF <<cmp ax,PluginComboBox>>,EQUAL?
				invoke SendMessage, hCombo, CB_GETCURSEL, 0, 0
				@IF <<cmp rax,CB_ERR>>,NOEQUAL? 
					mov current_selection, rax
				@ENDIF
			@ENDIF
		@ELSEIF <<cmp edx, EN_CHANGE>>,EQUAL?
			@IF <<cmp ax, FileNameEdit>>,EQUAL?
				
				invoke GetDlgItemText, hWin, FileNameEdit, addr GlobalBuffer,1024
				invoke IsFile64Bits, addr GlobalBuffer
				@IF <<cmp rax, 20h>>,EQUAL?
					invoke EnableWindow, hUnpackButton, TRUE
				@ELSE
					invoke EnableWindow, hUnpackButton, FALSE
				@ENDIF
				
			@ENDIF
		
		@ENDIF 

	@ELSEIF <<cmp eax,WM_CLOSE>>,EQUAL?
		invoke DestroyHandles
		invoke EndDialog,hWin,0
	
	@ELSE
		return FALSE
	
	@ENDIF
	return TRUE
exitf 

function Init,hWin:HWND, uMsg:UINT, wParam:LPARAM, lParam:LPARAM
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
	@IF <<cmp rax,0>>,EQUAL?
		invoke MessageBox, hWin,addr szErrorLista,addr szIntialError, MB_ICONERROR 
		invoke ExitProcess, -1
	@ENDIF
	
	mov hList, rax
	

	invoke CrearListaDoble, sizeof PluginInfo
	@IF <<cmp rax,0>>,EQUAL?
		invoke MessageBox, hWin,addr szErrorLista,addr szIntialError, MB_ICONERROR 
		invoke ExitProcess, -1
	@ENDIF
	
	mov hAuxList,rax
	
	invoke GetHandlesOfControls, hWin
	
	invoke CheckDlgButton, hWin, RealignPECheckBox, BST_CHECKED
	invoke CheckDlgButton, hWin, CopyOverlayDataBt, BST_CHECKED
	
	invoke LoadPlugins, hWin, uMsg, wParam, lParam

exitf

function GetHandlesOfControls,hWin:HWND
	comment ~
	Function Name: GetHandlesOfControls
	Function Description: Gets handles of every control in the UI 
	Function Parameters:
		hWin: HWND
	~
	
	invoke GetDlgItem, hWin, PluginComboBox
	mov hCombo,rax
	
	invoke GetDlgItem, hWin, OutputListBox
	mov hListBox, rax

	invoke GetDlgItem, hWin, EmailLink
	mov hEmailLink, rax
	
	invoke GetDlgItem, hWin, UnpackBtn
	mov hUnpackButton, rax
	
	
	invoke SetWindowText,hEmailLink,addr EmailAddress
	
	invoke SendMessage,hEmailLink,HLM_SETHOTCOLOR,0,0FF0000h
	invoke SendMessage,hEmailLink,HLM_SETTEXTCOLOR,0,0h
	invoke SendMessage,hEmailLink,HLM_SETUNDERLINE,0,TRUE
	
	invoke SendMessage,hEmailLink,HLM_SETSUBJECT,0,addr Subject
	invoke SendMessage,hEmailLink,HLM_SETBODY,0,addr Body

	invoke SendMessage,hEmailLink,HLM_SETTYPE,0,HLINK_EMAIL
	
	invoke GetDlgItem, hWin, BlogLinkClickable
	mov hBlogLink, rax
	
	invoke SetWindowText, hBlogLink, addr CrackinglandiaLink
	invoke SendMessage, hBlogLink,HLM_SETHOTCOLOR,0,0FF0000h
	invoke SendMessage, hBlogLink,HLM_SETTEXTCOLOR,0,0
	invoke SendMessage, hBlogLink,HLM_SETTYPE,0,HLINK_URL 
exitf	


function DestroyHandles 
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
	
	
exitf

function GetFileDialog

	push rsi
	
   	mov ofn.OPENFILENAME.lStructSize,sizeof OPENFILENAME
   	lea rsi,FilterString
	mov ofn.OPENFILENAME.lpstrFilter,rsi
	lea rsi, GlobalBuffer
	mov ofn.OPENFILENAME.lpstrFile,rsi 
	
	; Checking if the File exists
    invoke CreateFile,addr GlobalBuffer,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
    @IF <<cmp eax,INVALID_HANDLE_VALUE>>,EQUAL?
    
    	;The File is not  in the HDD
    	lea rsi, GlobalBuffer
    	mov byte ptr [rsi],0  ; To avoid issue we set empty the buffer	
    @ELSE
 		;The File exists
    	invoke CloseHandle,rax
    @ENDIF
	
	mov ofn.OPENFILENAME.nMaxFile,1024
	mov ofn.OPENFILENAME.Flags, OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST or OFN_LONGNAMES or OFN_EXPLORER or OFN_HIDEREADONLY
	lea rsi,AppName
	mov ofn.OPENFILENAME.lpstrTitle,rsi 
	invoke GetOpenFileName,addr ofn
	pop rsi	
exitf


function InitializeUnpacker,hWin:HWND,lpFileName:QWORD,CurrentSelection:QWORD
	comment ~
	Function Name: InitializeUnpacker
	Function Description: This function calls the DoUnpack method of the selected plugin 
	Function Parameters:
		hWin: HWND
		lpFileName: QWORD  Pointer to ASCII String
		CurrentSelection: QWORD  Index using by the ComboBox
	~
	
	mov rax, CurrentSelection
	invoke GetItemByIndex,rax
	
	@AjustePila
	sub rsp,8*6 ; must be 16 bytes alignment  
    
    ;arg 1
	lea rcx,ComunicationObject  ; Send a pointer to de Communicatin Plugin Object
	;arg 2
	mov rdx,lpFileName
	;arg 3
	lea r8, OptionsArray
	;arg 4
	lea r9,FUUID
	
	;arg 5
	mov qword ptr [rsp+4*8],0
	
	call rax
			
   	add rsp,8*6
	@ReAjustePila
			
exitf


function GetItemByIndex,lpIndex:QWORD
	comment ~
	Function Name: GetItemByIndex
	Function Description: Returns the item pointed by lpIndex. 
	Function Parameters:
		lpIndex: DWORD
	~

	begin_alloc
		alloc_var TempBuff:PluginInfo 
	end_alloc
	

	invoke ItemPosByIndexListaDoble, hList, lpIndex
	mov rbx,rax
	invoke RecuperarItemListaDoble, hList, rbx , addr TempBuff	
	
	mov rax, TempBuff.PluginInfo.DoUnpackAddr
	
	return rax

exitf


function RefreshComboBox
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

exitf	


function DetectCryptoSignatures, hWin:HWND, szFileName:QWORD, szDllName:QWORD
	comment ~
	Function Name: DetectCryptoSignatures
	Function Description: Loads the DetectCryptoSignatures plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	invoke DoJob, hWin, szFileName, szDllName
exitf


function DetectOEP,hWin:HWND, szFileName:QWORD, szDllName:QWORD
	comment ~
	Function Name: DetectOEP
	Function Description: Loads the DetectOEP plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	invoke DoJob, hWin, szFileName, szDllName
exitf

function GenericUnpacker, hWin:HWND, szFileName:QWORD, szDllName:QWORD
	comment ~
	Function Name: GenericUnpacker
	Function Description: Loads the GenericUnpacker plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	invoke DoJob, hWin, szFileName, szDllName
exitf

function IdentifyPackerOrCompiler,hWin:HWND, szFileName:QWORD, szDllName:QWORD
	comment ~
	Function Name: IdentifyPackerOrCompiler
	Function Description: Loads the SignatureDetector plugin 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	invoke DoJob, hWin, szFileName, szDllName
exitf


function DoJob,hWin:HWND, szFileName:QWORD, szDllName:QWORD
	comment ~
	Function Name: DoJob
	Function Description: This function calls the DoJob method for the selected plugin tool 
	Function Parameters: 
		hWin: HWND
		szFileName: DWORD
		szDllName: DWORD
	~
	
	invoke GetModuleFileName, hInstance, addr CurrentDir, MAX_PATH
		
	lea rsi, CurrentDir
	invoke lstrlen,rsi
	add rsi, rax
		

DoJob_dir_otro:	
	mov bl, byte ptr [rsi]
    cmp bl,"\"
    je DoJob_dir_fin
		mov byte ptr [rsi],0
		dec rsi
		dec rax
	jmp DoJob_dir_otro
DoJob_dir_fin:
		
	sub rsi, rax
		
	invoke lstrlen, rsi
	inc rax
		
	@IF <<cmp rax,MAX_PATH>>,LESS?
		invoke lstrcpy, addr ToolsDir, addr CurrentDir
		invoke lstrlen, addr ToolsDir
		inc rax
		@IF <<cmp rax,MAX_PATH>>,LESS?
			invoke lstrcat, addr ToolsDir, addr ToolsDirName 
			invoke lstrlen, addr ToolsDir
			inc rax
			@IF <<cmp rax, MAX_PATH>>,LESS?
				lea rsi, ToolsDir
				add rsi, rax
				dec rsi
				mov byte ptr[rsi], 05Ch
					
				invoke lstrlen, addr ToolsDir
				inc rax 
				@IF <<cmp rax,MAX_PATH>>,LESS?
					invoke lstrcat, addr ToolsDir, szDllName

					invoke LoadLibrary, addr ToolsDir
					@IF <<cmp rax,NULL>>,NOEQUAL?
						mov hModule, rax
						mov rbx,rax
						invoke GetProcAddress, rbx, addr DoMyJobProcName
							
						@IF <<cmp rax,NULL>>,NOEQUAL?
							
							@AjustePila
							sub rsp,8*4  
     	
							;arg 1
							mov rcx,hWin
							;arg 2
							mov rdx,szFileName
							;arg 3
							mov r8, 50456944h ; PluginID
							;arg 4
							mov r9,0
							call rax
							add rsp,8*4
							@ReAjustePila
							
								
							invoke FreeLibrary, hModule
								
							invoke FreeString, addr CurrentDir
							invoke FreeString, addr ToolsDir
								
							@IF <<cmp rax,0>>,EQUAL?
								invoke MessageBox, hWin, chr$("Error: FreeLibrary Failed!"), chr$("Error freeing library"), MB_ICONERROR
							@ENDIF
						@ELSE
							invoke MessageBox, hWin, chr$("Error: GetProcAddress Failed!"), chr$("Error loading function"), MB_ICONERROR
						@ENDIF
					@ELSE
						invoke MessageBox, hWin, chr$("Error: LoadLibrary Failed!"), chr$("Error loading library"), MB_ICONERROR
					@ENDIF
				@ENDIF				
			@ENDIF
		@ENDIF
	@ENDIF		
exitf

function FreeString, szString:QWORD
	comment ~
	Function Name: FreeString
	Function Description: Clear a buffer with a string 
	Function Parameters: 
		szString: DWORD  (ASCII String Pointer)
	~
	push rsi
	push rbx
	
	mov rsi, szString

FreeString_otro:
	mov bl, byte ptr [rsi]
	cmp bl,0
	je FreeString_fin
		mov byte ptr [rsi],0
		inc rsi
	jmp FreeString_otro	

FreeString_fin:
	pop rbx
	pop rsi
exitf

function InsertItemInList, List:QWORD, lpItem:QWORD
	comment ~
	Function Name: InsertItemInList
	Function Description: Insert a given item into a list 
	Function Parameters: 
		List: QWORD
		lpItem: QWORD
	~
	
	invoke UltimoNodoListaDoble, List
	invoke AnadirItemListaDoble, List, lpItem, rax
exitf



function LoadPlugins,hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	comment ~
	Function Name: LoadPlugins
	Function Description: This function loads the application plugins
	Function Parameters: 
		hWin: HWND
		uMsg: UINT
		wParam: WPARAM
		lParam: LPARAM
	~
	
	begin_alloc 
		alloc_var findData:WIN32_FIND_DATA
	end_alloc
	
	
	invoke GetModuleFileName, hInstance, addr CurrentDir, MAX_PATH

	lea rsi,CurrentDir
	invoke lstrlen,rsi
	add rsi, rax

LoadPlugins_dir_otro:	
		mov bl, byte ptr [rsi]
    	cmp bl,"\"
    	je LoadPlugins_dir_fin
			mov byte ptr [rsi],0
			dec rsi
			dec rax
		jmp LoadPlugins_dir_otro
LoadPlugins_dir_fin:

	sub rsi, rax
	
	invoke lstrlen, rsi
	
	@IF <<cmp rax,MAX_PATH>>,LESS?
		invoke lstrcat, rsi, addr Pluginsx64DirName ; Cambiado
		invoke SetCurrentDirectory, rsi  
	
		invoke FindFirstFile,addr fPattern, addr findData
		@IF <<cmp rax, INVALID_HANDLE_VALUE>>,NOEQUAL?
			mov fHandle, rax

LoadPlugins_otro:		
			cmp rax,0
			je LoadPlugins_fin
				invoke LoadLibrary,addr findData.WIN32_FIND_DATA.cFileName
				@IF <<cmp rax,NULL>>,NOEQUAL?
					mov hModule, rax
					mov rbx,rax
					invoke GetProcAddress,rbx, addr DoUnpackName
					@IF <<cmp rax,NULL>>,NOEQUAL?
						mov  PIList.DoUnpackAddr,rax
						invoke GetProcAddress, hModule, addr GetPluginName
						@IF <<cmp rax,NULL>>,NOEQUAL?
							mov PIList.GetPlugNameAddr,rax
							
							;invoke GetStructPtr, addr pInfo, counter
							mov rbx, counter
							inc rbx
							mov PIList._Index, rbx
							
							invoke lstrlen,addr findData.WIN32_FIND_DATA.cFileName
							inc rax
							
							@IF <<cmp rax, MAX_PATH>>,LESS?
								invoke lstrcpyn,addr PIList.DllName, addr findData.WIN32_FIND_DATA.cFileName, eax
								
								@AjustePila
								sub rsp,8*4  
								mov rax,PIList.GetPlugNameAddr
								call rax
     							add rsp,8*4
								@ReAjustePila
								
								
								mov rbx, rax
								invoke lstrlen,rax
								inc rax
								@IF <<cmp rax,MAX_PATH>>,LESS?
									invoke lstrcpyn,addr PIList.PluginName, rbx, eax
										
									invoke SendMessage, hCombo, CB_ADDSTRING, 0, rbx	
									invoke InsertItemInList, hList, addr PIList							
								@ENDIF
							@ENDIF
						@ENDIF 
					@ENDIF
				@ENDIF
				invoke FindNextFile, fHandle, addr findData
			jmp LoadPlugins_otro
LoadPlugins_fin:

		@ELSE
			invoke MessageBox, hWin, addr ErrorMsgText, addr ErrorMsgTitle, MB_ICONERROR
		@ENDIF
	@ENDIF
	
	invoke FreeString, addr CurrentDir
exitf

;*****************************************
;
;  Return 10 => 32 bits
;  Return 20 => 64 bits
;  Return 0  => Error fichero erroneo o no se puede leer
;
;******************************************
function IsFile64Bits,lpFileAnaliz:QWORD
	begin_alloc
		alloc_var hFile3:QWORD 
		alloc_var Buff{4}:BYTE
		alloc_var ByteRead:DWORD
		alloc_var SizeHeader:DWORD
		alloc_var Dato2:WORD 
		
		alloc_var Buff2{MAX_PATH}:BYTE
	end_alloc
	
	invoke CreateFile,lpFileAnaliz,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
	@IF <<cmp rax,INVALID_HANDLE_VALUE>>,NOEQUAL?
		mov hFile3,rax
		
		invoke SetFilePointer,hFile3,0,0,FILE_BEGIN	
		invoke ReadFile,hFile3,addr Buff,2,addr ByteRead,NULL
		lea rsi,Buff
		mov byte ptr [rsi+2],0
		invoke lstrcmp,addr szMZ,addr Buff
		@IF <<cmp rax,0>>,EQUAL?
			;; Es un fichero ejecutable
			
			invoke SetFilePointer,hFile3,03Ch,NULL,FILE_BEGIN	; Nos situamos en el campo e_lfanew
			@IF <<cmp eax,-1>>,NOEQUAL?
				invoke ReadFile,hFile3,addr SizeHeader,sizeof DWORD,addr ByteRead,NULL ;leemos el valor de comienzo de la estructura PE
				
				invoke SetFilePointer,hFile3,SizeHeader,NULL,FILE_BEGIN
				@IF <<cmp eax,-1>>,NOEQUAL?
				
					invoke ReadFile,hFile3,addr Buff,2,addr ByteRead,NULL
					
					lea rsi,Buff
					mov byte ptr [rsi+2],0
					
					invoke lstrcmp,addr szPE,addr Buff
					@IF <<cmp rax,0>>,EQUAL?
						mov rax, sizeof IMAGE_FILE_HEADER 
						add rax,2  ; La Firma PE son 4 Bytes y solo hemos leido 2 
						; offset para llegar al Magic Word de OPTIONAL_HEADER 
				
						invoke SetFilePointer,hFile3,eax,NULL,FILE_CURRENT	
						@IF <<cmp eax,-1>>,NOEQUAL?
						
							invoke ReadFile,hFile3,addr Dato2,sizeof WORD,addr ByteRead,NULL
							mov eax,ByteRead
							@IF <<cmp eax, sizeof  WORD>>,EQUAL?
								
																						
								invoke CloseHandle,hFile3
										
								mov ax,Dato2
								@IF <<cmp ax,10bh>>,EQUAL?
									return 10h  ;PE
								@ELSEIF <<cmp ax,20bh>>,EQUAL?
									return 20h  ;PE+
								@ELSE
									return NULL;
								@ENDIF
								
							@ELSE
								invoke CloseHandle,hFile3
								return NULL
							@ENDIF
						
						@ELSE
							
							invoke CloseHandle,hFile3
							return NULL
						@ENDIF
					@ELSE
				
						invoke CloseHandle,hFile3
						return NULL
					@ENDIF
				@ELSE
					
					invoke CloseHandle,hFile3
					return NULL
				@ENDIF
			@ELSE
				
				invoke CloseHandle,hFile3
				return NULL
			@ENDIF
		@ELSE
				
			invoke CloseHandle,hFile3
			return NULL
		@ENDIF
	@ELSE
		
		return NULL	
	@ENDIF
exitf



end
