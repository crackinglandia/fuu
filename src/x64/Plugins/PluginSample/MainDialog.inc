funcproto LOCAL,DlgProc,HWND,UINT,WPARAM,LPARAM
funcproto LOCAL,GetHandles,QWORD
funcproto LOCAL,FileAnalyze,QWORD
funcproto LOCAL,ShowData,QWORD
funcproto LOCAL,ShowSection,QWORD,WORD
funcproto LOCAL,ShowImport,QWORD
funcproto LOCAL,EnumIAT,QWORD
funcproto LOCAL,TrvAddNode,QWORD,QWORD
funcproto LOCAL,DataToLog,QWORD

.const
IDD_DLGMAIN		equ 1000
IDC_EPATH		equ 1002
IDC_HEADER		equ 1003
IDC_LVPEHEADER	equ 1004
IDC_IAT			equ 1006
IDC_LVSECTION	equ 1008
IDC_BSEND		equ 1009
IDC_BSAVE		equ 1010

.data
; Controls handle
hEPath			dq 0
hListHeader		dq 0
hTreeIAT		dq 0
hListSecction	dq 0
;****************


hLastFather		dq 0
szBufferDllName	db MAX_PATH dup(0)


Format8Hex	db "%08X",0
Format4Hex	db "%04X",0
Format16Hex	db "%016I64X",0 ; Para imprimir 64bits usar %I64X


szField	db "Field",0
szValue	db "Value",0

szName				db "Name",0
szVoffset			db "Virtual Offset",0
szVSize				db "Virtual Size",0
szRawOffet			db "Raw offset",0
szRawSize			db "Raw Size",0
szCharacteristic	db "Characterístic",0

szPE64	db "[PE 64] Header",0

;PE 64 Data
szPE64Offset				db "PE64Offset",0;
szImageBase					db "ImageBase",0;
szOriginalEntryPoint		db "OriginalEntryPoint",0;
szNtSizeOfImage				db "NtSizeOfImage",0;
szNtSizeOfHeaders			db "NtSizeOfHeaders",0;
szSizeOfOptionalHeaders		db "SizeOfOptionalHeaders",0;
szFileAlignment				db "FileAlignment",0;
szSectionAligment			db "SectionAligment",0;
szImportTableAddress		db "ImportTableAddress",0;
szImportTableSize			db "ImportTableSize",0;
szResourceTableAddress		db "ResourceTableAddress",0;
szResourceTableSize			db "ResourceTableSize",0;
szExportTableAddress		db "ExportTableAddress",0;
szExportTableSize			db "ExportTableSize",0;
szTLSTableAddress			db "TLSTableAddress",0;
szTLSTableSize				db "TLSTableSize",0;
szRelocationTableAddress	db "RelocationTableAddress",0;
szRelocationTableSize		db "RelocationTableSize",0;
szTimeDateStamp				db "TimeDateStamp",0;
szSectionNumber				db "SectionNumber",0;
szCheckSum					db "CheckSum",0;
szSubSystem					db "SubSystem",0;
szCharacteristics			db "Characteristics",0;
szNumberOfRvaAndSizes		db "NumberOfRvaAndSizes",0;


lpMainData	dq 0 ;Pionter to MAINSTRUCT defined in PluginSample.inc

szSaveLogTitle	db "Saving the log"
FileLogSaveFilter	db 	"Log",0,"*.log",0,\
              			"Text",0,"*.txt",0,0,0\

szOK		db "Log saved successfully",0
szError		db "Error",0
szTwoPoint	db ": ",0
              		
              		
szFile	db "Analized file: ",0   	

szlimit	db "---------------------------------------",0
szPeHeader	db "PE Header",0
szSection	db "Sections ",0
szIAT		db "IAT",0
szTab		db "    ",0
szEmpty		db 0,0
		
.code


function DlgProc,hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	begin_alloc
		alloc_var FileLogSave{MAX_PATH}:BYTE
	end_alloc

	xor rax,rax
	mov eax,uMsg
	
	@IF <<cmp eax,WM_INITDIALOG>>, EQUAL?
		invoke GetHandles,hWin ; Getting the handles of the control and making some inicialization.
		
		mov rax,lParam
		mov lpMainData,rax
		mov rax,[rax].MAINSTRUCT.lpFilePath
		invoke SetDlgItemText,hWin,IDC_EPATH,rax  ; Setting the file path in the Edit
		invoke FileAnalyze,lParam 
		
	@ELSEIF <<cmp eax,WM_COMMAND>>,EQUAL?
		mov rax,wParam
		@IF <<cmp ax,IDC_BSEND>>,EQUAL?
			;***** 1st we clean the log
			mov rbx,lpMainData
			mov rbx,[rbx].MAINSTRUCT.Object
			push rbx
			; ******** Clear the Log ***********
			ClearLog rbx	
			pop rbx
			
			invoke DataToLog,rbx   ; sending the information to the Listbox of the FUU GUI
			
		 
		@ELSEIF <<cmp ax,IDC_BSAVE>>,EQUAL?
		
			
			;******* Saving the log to a file ********
			invoke GuardarFicheroDlg,addr FileLogSave,addr szSaveLogTitle,addr FileLogSaveFilter,1,NULL

			@IF <<cmp rax,NULL>>,NOEQUAL?
				
				lea rsi,FileLogSave
				mov rbx,lpMainData
				mov rbx,[rbx].MAINSTRUCT.Object
				LogToFile rbx,rsi ,TRUE ; here the TRUE main overwrite the file 
				
				@IF <<cmp rax,0>>,NOEQUAL?
					
					
					mov rbx,lpMainData
					mov rbx,[rbx].MAINSTRUCT.Object
			
					GetMainHandle rbx
					mov rbx,rax
					invoke MessageBox,rbx,addr FileLogSave,addr szOK,MB_OK
			
				@ELSE
					mov rbx,lpMainData
					mov rbx,[rbx].MAINSTRUCT.Object

					GetMainHandle rbx
					mov rbx,rax
					invoke MessageBox,rbx,addr FileLogSave,addr szError,MB_OK or MB_ICONERROR
				
				@ENDIF	
			@ENDIF
			;*****************************************
		@ENDIF
	
		
	@ELSEIF <<cmp eax,WM_CLOSE>>,EQUAL?
		invoke EndDialog,hWin,0
	
	@ELSE
		return FALSE
	
	@ENDIF
	return TRUE
exitf 


function GetHandles,hWin:QWORD
	
	invoke GetDlgItem,hWin,IDC_EPATH	
	mov hEPath,rax

	invoke GetDlgItem,hWin,IDC_LVPEHEADER	
	mov hListHeader,rax

	invoke SendMessage,hListHeader,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT  or LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT or LVS_EX_GRIDLINES 
	; Creating the column of the ListView report
	invoke AnadirColumnaLW,hListHeader,addr szField,150
	invoke AnadirColumnaLW,hListHeader,addr szValue,140

	invoke GetDlgItem,hWin,IDC_IAT	
	mov hTreeIAT,rax

	invoke GetDlgItem,hWin,IDC_LVSECTION	
	mov hListSecction,rax
	
	; Creating the column of the ListView report
	invoke SendMessage,hListSecction,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT  or LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT or LVS_EX_GRIDLINES

	invoke AnadirColumnaLW,hListSecction,addr szName,100
	invoke AnadirColumnaLW,hListSecction,addr szVoffset,100
	invoke AnadirColumnaLW,hListSecction,addr szVSize,100
	invoke AnadirColumnaLW,hListSecction,addr szRawOffet,100
	invoke AnadirColumnaLW,hListSecction,addr szRawSize,100
	invoke AnadirColumnaLW,hListSecction,addr szCharacteristic,100

exitf

function FileAnalyze, lpObject:QWORD
	begin_alloc
		alloc_var PE64Bits:PE64Struct
		alloc_var lpFile:QWORD
	end_alloc
	
	mov rsi,lpObject
	mov rbx,[rsi].MAINSTRUCT.lpFilePath
	mov lpFile,rbx
	
	; Get PE+ Header information 
	invoke GetPE32DataEx,lpFile,addr PE64Bits
	@IF <<cmp rax,TRUE>>,EQUAL?
		; Showing the information in the ListView
		invoke ShowData,addr PE64Bits
	@ENDIF 	
					
	invoke ShowSection,lpFile,PE64Bits.PE64Struct.SectionNumber
	invoke ShowImport,lpFile					
	
exitf


function ShowData,lpPEHeader:QWORD

	invoke AnadirTextLW,hListHeader,addr szPE64Offset,0,-1 
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.PE64Offset
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1
	
	invoke AnadirTextLW,hListHeader,addr szImageBase,0,-1 
	mov rsi,lpPEHeader
	mov rbx,[rsi].PE64Struct.ImageBase
	invoke wsprintf,addr szBufferAux,addr Format16Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szOriginalEntryPoint,0,-1
	 
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.OriginalEntryPoint
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szNtSizeOfImage,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.NtSizeOfImage
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	
	invoke AnadirTextLW,hListHeader,addr szNtSizeOfHeaders,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.NtSizeOfHeaders
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1
	
		 
	invoke AnadirTextLW,hListHeader,addr szSizeOfOptionalHeaders,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov bx,[rsi].PE64Struct.SizeOfOptionalHeaders
	invoke wsprintf,addr szBufferAux,addr Format4Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szFileAlignment,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.FileAlignment
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szSectionAligment,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.SectionAligment
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szImportTableAddress,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ImportTableAddress
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szImportTableSize,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ImportTableSize
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szResourceTableAddress,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ResourceTableAddress
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szResourceTableSize,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ResourceTableSize
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szExportTableAddress,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ExportTableAddress
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szExportTableSize,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.ExportTableSize
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szTLSTableAddress,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.TLSTableAddress
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szTLSTableSize,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.TLSTableSize
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szRelocationTableAddress,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.RelocationTableAddress
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szRelocationTableSize,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.RelocationTableSize
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szTimeDateStamp,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.TimeDateStamp
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szSectionNumber,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov bx,[rsi].PE64Struct.SectionNumber
	invoke wsprintf,addr szBufferAux,addr Format4Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szCheckSum,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.CheckSum
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

	invoke AnadirTextLW,hListHeader,addr szSubSystem,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov bx,[rsi].PE64Struct.SubSystem
	invoke wsprintf,addr szBufferAux,addr Format4Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1
	invoke AnadirTextLW,hListHeader,addr szCharacteristics,0,-1
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov bx,[rsi].PE64Struct.Characteristics
	invoke wsprintf,addr szBufferAux,addr Format4Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1
	invoke AnadirTextLW,hListHeader,addr szNumberOfRvaAndSizes,0,-1 
	mov rsi,lpPEHeader
	xor rbx,rbx
	mov ebx,[rsi].PE64Struct.NumberOfRvaAndSizes
	invoke wsprintf,addr szBufferAux,addr Format8Hex,rbx
	invoke AnadirTextLW,hListHeader,addr szBufferAux,1,-1

exitf

function ShowSection, lpFileExePath:QWORD,NumerOfSecction:WORD
; There is a bug in the GetPE32Data API, so the workaroung is to use GetPE32DataFromMappedFile
		
	begin_alloc
		alloc_var Count:DWORD
		alloc_var hFile:QWORD
		alloc_var mFile:QWORD
		alloc_var pFile:QWORD
	end_alloc
	
	mov dword ptr Count,0

	invoke CreateFile,lpFileExePath,GENERIC_READ ,FILE_SHARE_READ ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
	@IF <<cmp rax, INVALID_HANDLE_VALUE>>,EQUAL?
		return NULL
	@ENDIF
	mov hFile,rax
	
	invoke CreateFileMapping,hFile,NULL,PAGE_READONLY,0,0,NULL
	@IF <<cmp rax,0>>,EQUAL?
		invoke CloseHandle,hFile
		return NULL
	@ENDIF
	
	mov mFile,rax
	
	invoke MapViewOfFile,mFile,FILE_MAP_READ,0,0,0
	@IF <<cmp rax,NULL>>,EQUAL?
		invoke CloseHandle,mFile
		invoke CloseHandle,hFile
		return NULL
	@ENDIF
	mov pFile,rax
	
ShowSection_otra:	
	mov eax,Count
	xor rbx,rbx
	mov bx,NumerOfSecction
	cmp eax,ebx
	je ShowSection_FIN
		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONNAME
		invoke lstrcpyn,addr szBufferAux,rax,8
		invoke AnadirTextLW,hListSecction,addr szBufferAux,0,-1
	
		
		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONVIRTUALOFFSET
		invoke wsprintf,addr szBufferAux,addr Format8Hex,rax
		invoke AnadirTextLW,hListSecction,addr szBufferAux,1,-1
		
		
		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONVIRTUALSIZE
		invoke wsprintf,addr szBufferAux,addr Format8Hex,rax
		invoke AnadirTextLW,hListSecction,addr szBufferAux,2,-1

		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONRAWOFFSET
		invoke wsprintf,addr szBufferAux,addr Format8Hex,rax
		invoke AnadirTextLW,hListSecction,addr szBufferAux,3,-1

		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONRAWSIZE
		invoke wsprintf,addr szBufferAux,addr Format8Hex,rax
		invoke AnadirTextLW,hListSecction,addr szBufferAux,4,-1

		invoke GetPE32DataFromMappedFile,pFile,Count,UE_SECTIONFLAGS
		invoke wsprintf,addr szBufferAux,addr Format8Hex,rax
		invoke AnadirTextLW,hListSecction,addr szBufferAux,5,-1
		
	
		inc dword ptr Count
		jmp ShowSection_otra
	
ShowSection_FIN:
	
	invoke UnmapViewOfFile,pFile
	invoke CloseHandle,mFile
	invoke CloseHandle,hFile
	
	return TRUE
exitf


function ShowImport,lpFileName:QWORD
	; The impor is created in memmory
	; We clear the import first 
	invoke ImporterCleanup 
	; Taking the import from a file
	invoke ImporterLoadImportTable,lpFileName
	@IF <<cmp rax,TRUE>>,EQUAL?
		; Enumerating the import
		invoke ImporterEnumAddedData, addr EnumIAT
		
	@ENDIF

exitf


function EnumIAT,lpImportEnumData:QWORD
	
	mov rsi,lpImportEnumData
	mov rax,hLastFather
	@IF <<cmp rax,0>>,EQUAL?
		push rsi
		invoke lstrcpyn,addr szBufferDllName,[rsi].ImportEnumData.DLLName,MAX_PATH
		pop rsi
		push rsi
		invoke TrvAddNode,NULL,[rsi].ImportEnumData.DLLName
		mov hLastFather,rax
		pop rsi 
		invoke TrvAddNode,hLastFather,[rsi].ImportEnumData.APIName
	@ELSE
		push rsi
		invoke lstrcmp,addr szBufferDllName,[rsi].ImportEnumData.DLLName
		pop rsi
		@IF <<cmp rax,0>>,EQUAL?
			invoke TrvAddNode,hLastFather,[rsi].ImportEnumData.APIName
			
		@ELSE
			push rsi
			invoke lstrcpyn,addr szBufferDllName,[rsi].ImportEnumData.DLLName,MAX_PATH
			pop rsi
			push rsi
			invoke TrvAddNode,NULL,[rsi].ImportEnumData.DLLName
			mov hLastFather,rax
			pop rsi 
			invoke TrvAddNode,hLastFather,[rsi].ImportEnumData.APIName
		@ENDIF
	@ENDIF
		
exitf

function TrvAddNode, hPar:QWORD,lpString:QWORD
	begin_alloc
		alloc_var tvins:TV_INSERTSTRUCT 
	end_alloc
	

	mov		rax,hPar
    mov		tvins.TV_INSERTSTRUCT.hParent,rax
    mov		qword  ptr tvins.TV_INSERTSTRUCT.hInsertAfter,0	
    lea 	rsi,tvins.TV_INSERTSTRUCT.item
    mov		[rsi].TV_ITEM.imask,TVIF_TEXT  
	mov		rax,lpString
	mov		[rsi].TV_ITEM.pszText,rax
	invoke SendMessage,hTreeIAT,TVM_INSERTITEM,0,addr tvins
exitf


function DataToLog,ObjectComunication:QWORD
	begin_alloc
		alloc_var Buff2{MAX_PATH}:BYTE
		alloc_var countItem:DWORD
		alloc_var item:LV_ITEM
		alloc_var hItemTree:QWORD
		alloc_var hItemChild:QWORD
		alloc_var itemTree:TV_ITEM
	end_alloc
	
	lea rsi,szFile
	LogString ObjectComunication,rsi
	
	
	invoke SendMessage,hEPath,WM_GETTEXT,MAX_PATH,addr szBufferAux
	
	;*********** SendString To Log *******	
	lea rsi,szBufferAux
	LogString ObjectComunication,rsi

	lea rsi,szlimit
	LogString ObjectComunication,rsi

	lea rsi,szPeHeader
	LogString ObjectComunication,rsi
	
	lea rsi,szlimit
	LogString ObjectComunication,rsi


	;***********   PE Header ***************
	invoke SendMessage,hListHeader,LVM_GETITEMCOUNT,0,0
	mov countItem,eax
	
	xor rcx,rcx
DataToLog_PEHEADER_otro:	
	cmp ecx,countItem
	je DataToLog_PEHEADER_FIN
		push rcx
		
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,0
		lea rsi,szBufferAux
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListHeader,LVM_GETITEM,0,addr item
		
		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,1
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListHeader,LVM_GETITEM,0,addr item
		
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,addr szBufferAux,addr Buff2
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi
		
		pop rcx
		inc rcx
		jmp DataToLog_PEHEADER_otro
DataToLog_PEHEADER_FIN:	

	lea rsi,szlimit
	LogString ObjectComunication,rsi

    ; PE SECCTION

	lea rsi,szSection
	LogString ObjectComunication,rsi
	lea rsi,szlimit
	LogString ObjectComunication,rsi


	invoke SendMessage,hListSecction,LVM_GETITEMCOUNT,0,0
	mov countItem,eax
	
	xor rcx,rcx
DataToLog_SECTION_otro:	
	cmp ecx,countItem
	je DataToLog_SECTION_FIN
		push rcx
		
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,0 ;Name
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item
		
		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szName
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi
		
		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,1 
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item

		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szVoffset
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi

		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,2 
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item

		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szVSize
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi

		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,3 
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item

		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szRawOffet
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi

		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,4 
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item

		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szRawSize
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi

		pop rcx
		push rcx
		
		mov item.LV_ITEM.imask,LVIF_TEXT	
		mov item.LV_ITEM.iItem,ecx
		mov item.LV_ITEM.iSubItem,5 
		lea rsi,Buff2
		mov item.LV_ITEM.pszText,rsi
		mov item.LV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hListSecction,LVM_GETITEM,0,addr item

		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr szCharacteristic
		invoke lstrcat,addr szBufferAux,addr szTwoPoint
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi

		lea rsi,szEmpty
		LogString ObjectComunication,rsi
	
		pop rcx
		inc rcx
		jmp DataToLog_SECTION_otro
DataToLog_SECTION_FIN:	

	lea rsi,szlimit
	LogString ObjectComunication,rsi

	;***** IAT ************************************************ 

	lea rsi,szIAT
	LogString ObjectComunication,rsi
	lea rsi,szlimit
	LogString ObjectComunication,rsi
	
	invoke SendMessage,hTreeIAT,TVM_GETNEXTITEM,TVGN_ROOT,NULL
DataToLog_DLL_OTRO:
	cmp rax,NULL
	je DataToLog_FIN
		mov hItemTree,rax
		mov itemTree.TV_ITEM.imask,	TVIF_HANDLE	 or TVIF_TEXT	
		mov rax,hItemTree
		mov itemTree.TV_ITEM.hItem,rax
		lea rax,Buff2
		mov itemTree.TV_ITEM.pszText,rax
		mov itemTree.TV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hTreeIAT,TVM_GETITEM,0,addr itemTree
		
		lea rsi,Buff2
		LogString ObjectComunication,rsi
		
		; Taken the APIs
		invoke SendMessage,hTreeIAT,TVM_GETNEXTITEM,TVGN_CHILD,hItemTree

DataToLog_API_OTRO:	
		mov hItemChild,rax
		
		
		mov itemTree.TV_ITEM.imask,	TVIF_HANDLE	 or TVIF_TEXT	
		mov itemTree.TV_ITEM.hItem,rax
		lea rax,Buff2
		mov itemTree.TV_ITEM.pszText,rax
		mov itemTree.TV_ITEM.cchTextMax,MAX_PATH
		
		invoke SendMessage,hTreeIAT,TVM_GETITEM,0,addr itemTree
		invoke lstrcpy,addr szBufferAux,addr szTab
		invoke lstrcat,	addr szBufferAux,addr Buff2
		
		lea rsi,szBufferAux
		LogString ObjectComunication,rsi
		
		invoke SendMessage,hTreeIAT,TVM_GETNEXTITEM,TVGN_NEXT,hItemChild
		cmp rax,NULL
		jne DataToLog_API_OTRO
		
		lea rsi,szEmpty
		LogString ObjectComunication,rsi
		
		invoke SendMessage,hTreeIAT,TVM_GETNEXTITEM,TVGN_NEXT,hItemTree
		jmp  DataToLog_DLL_OTRO

DataToLog_FIN:
	
exitf