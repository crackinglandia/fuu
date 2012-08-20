funcproto LOCAL,LogString,QWORD
funcproto LOCAL,ClearLog
funcproto LOCAL,LogToFile,QWORD,DWORD
funcproto LOCAL,GetMainHandle
	


COMUNICATIONPLUGIN STRUC
	LogString		dq ?
	ClearLog		dq ?
	LogToFile		dq ?
	GetMainHandle	dq ?
COMUNICATIONPLUGIN ends


.const

.data

ComunicationObject COMUNICATIONPLUGIN<LogString,ClearLog,LogToFile,GetMainHandle>

szLFCR_ListBox	db 13,10,0

.code

function LogString, lpString:QWORD 
	
	mov rax,lpString
	@IF <<cmp rax,0>>,NOEQUAL?
		mov rax,hListBox
		@IF <<cmp rax,0>>,NOEQUAL?
			
			invoke SendMessage,hListBox,LB_ADDSTRING,0,lpString
			@IF <<cmp rax,LB_ERR>>,EQUAL?
				mov rax,FALSE
			@ELSE
				mov rax,TRUE
			@ENDIF
		
		@ELSE
			mov rax,FALSE	
		@ENDIF
		
	@ELSE
		mov rax,FALSE	
		
	@ENDIF	
	
	
	return rax
exitf 

function ClearLog


	mov rax,hListBox
	@IF <<cmp rax,0>>,NOEQUAL?
	
ClearLog_otro:	
		invoke SendMessage,hListBox,LB_GETCOUNT,0,0
		@IF <<cmp rax,LB_ERR>>,NOEQUAL?
			@IF <<cmp rax,0>>,NOEQUAL?
				invoke SendMessage,hListBox,LB_DELETESTRING,0,0
				jmp ClearLog_otro
			@ENDIF
		@ENDIF
	
		mov rax,TRUE
	@ELSE
	
		mov rax,FALSE	
	@ENDIF

	return TRUE
exitf 


function LogToFile,lpFilePath:QWORD,OverWrite:DWORD
	begin_alloc
		alloc_var hFileLog:QWORD
		alloc_var ByteWrittenLog:DWORD
		alloc_var CountItemListBox:DWORD
		alloc_var lpBuffAuxListBox:QWORD
	end_alloc	
	
	mov rax,hListBox
	@IF <<cmp rax,0>>,NOEQUAL?
	
		; Creating the file
		mov eax,OverWrite
		@IF <<cmp eax,TRUE>>,EQUAL?
			
			invoke CreateFile,lpFilePath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL
		@ELSE
			invoke CreateFile,lpFilePath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE,NULL
		@ENDIF 
		
		@IF <<cmp rax, INVALID_HANDLE_VALUE>>,NOEQUAL?
			mov hFileLog,rax

			invoke SendMessage,hListBox,LB_GETCOUNT,0,0
			@IF <<cmp rax,LB_ERR>>,NOEQUAL?
				mov CountItemListBox,eax
				xor rcx,rcx
LogToFile_otro:					
				cmp ecx, CountItemListBox
				je LogToFile_Fin 
					push rcx
					mov rdi,rcx
					push rdi
					invoke SendMessage,hListBox,LB_GETTEXTLEN,rdi,0
					
					inc rax
					invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,eax
					mov lpBuffAuxListBox,rax
					
					pop rdi
					invoke SendMessage,hListBox,LB_GETTEXT,rdi,lpBuffAuxListBox
						
					invoke lstrlen,lpBuffAuxListBox
					mov rdi,rax
					invoke WriteFile,hFileLog,lpBuffAuxListBox,edi,addr ByteWrittenLog,NULL	
					invoke WriteFile,hFileLog,addr szLFCR_ListBox,2,addr ByteWrittenLog,NULL	
				
					invoke LocalFree,lpBuffAuxListBox
					
					pop rcx
					inc rcx
					jmp LogToFile_otro 
				
				
LogToFile_Fin:
				invoke CloseHandle,hFileLog
				mov rax,TRUE
				
			@ELSE
				invoke CloseHandle,hFileLog
				mov rax,FALSE
			@ENDIF
				
		@ELSE
			mov rax,FALSE
		@ENDIF
	@ELSE
		mov rax,FALSE
	@ENDIF
	
	return rax
	
exitf

function GetMainHandle
	
	
	
	mov rax,hMainHanlde
	return rax
	
exitf