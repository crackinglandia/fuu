; $Id: Funciones.inc 35 2010-07-11 22:31:57Z nahuelriva $

;Fichero con ciertas funciones genericas 
include comdlg32.inc
include gdi32.inc

includelib COMDLG32.LIB
includelib GDI32.LIB

;Prototipos
AbrirFicheroDlg     		PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GuardarFicheroDlg   		PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DirectorioDLG				PROTO :DWORD,:DWORD,:DWORD
setmem 						PROTO :DWORD,:DWORD,:BYTE
memcpy 						PROTO :DWORD,:DWORD, :DWORD
memcpm 						PROTO :DWORD,:DWORD,:DWORD

ListBoxClean 				PROTO :DWORD
ComboBoxClean 				PROTO :DWORD

GetPathOrName 				PROTO :DWORD,:DWORD,:DWORD,:DWORD ; Parece que esta función no funciona en Vista 64
GetExtension 				PROTO :DWORD,:DWORD
SetExtension 				PROTO :DWORD,:DWORD
CheckExtension 				PROTO :DWORD,:DWORD   ;si no tiene extensión se le añaderá el suministrado

TopXY 						PROTO :DWORD,:DWORD
CadenaToInt					PROTO :DWORD
HexToInt 					PROTO :DWORD

CargarRecursoAMemoria 		PROTO :DWORD,:DWORD,:DWORD

RangoProgressBar 			PROTO :DWORD,:DWORD
NuevaPosicionProgressBar 	PROTO :DWORD,:DWORD

CrearFicheroEnBlanco 		PROTO :DWORD,:DWORD,:DWORD

AnadirColumnaLW				PROTO :DWORD,:DWORD,:DWORD
BorrarTodasLasColumnasLW	proto :DWORD
GetColumCountLW 			PROTO :DWORD
AnadirTextLW 				PROTO :DWORD,:DWORD,:DWORD
InsertarTextoLW 			proto :DWORD,:DWORD,:DWORD,:DWORD
GetItemCountLW 				PROTO :DWORD
BorrarItemsLW				PROTO :DWORD

FindPosCharInStr 			PROTO :DWORD,:Byte,:DWORD,:DWORD,:DWORD
GetCampoString 				PROTO :BYTE,:DWORD,:DWORD,:DWORD
DrawLine 					PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
isprint 					PROTO :BYTE
isalpha 					proto :BYTE
isalnum						proto :BYTE
isdigit 					proto :BYTE
isxdigit					proto :BYTE
strnicmp					proto :DWORD,:DWORD,:DWORD
pow10						proto :DWORD

PosicionCaret 				PROTO :DWORD,:DWORD
ObtenerSubTextEdit 			PROTO :DWORD,:DWORD,:DWORD,:DWORD

AnadirImagen  				PROTO :DWORD,:DWORD
AnadirImagenBMP 			proto :DWORD,:DWORD
DrawRect 					PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

SetEditHex					PROTO :HWND
UnSetEditHex				PROTO :HWND
EditHexProc					PROTO :HWND,:UINT,:WPARAM,:LPARAM
AsciiHexToInt				PROTO :DWORD

IsMenuItemCheck 			proto :DWORD,:DWORD

NodoArbloTV 				proto :DWORD,:DWORD,:DWORD,:DWORD	

TSIZE STRUC
	Ancho dd ?
	Alto dd ?
TSIZE ends

EDITPOS STRUC
	lin 	dd ?
	col 	dd ?
	
EDITPOS ends

RGB MACRO red, green, blue
	xor eax, eax
	mov al, blue    ; blue
	rol eax, 8
	mov al, green   ; green
	rol eax, 8
	mov al, red     ; red
ENDM

MODULO	MACRO Divisor,Dividendo
	push edx
	push ebx

	xor edx,edx
	mov eax,Divisor
	mov ebx,Dividendo
	div ebx

	mov eax,edx   ; EN EDX se tiene el módulo de la division 
	
	pop ebx
	pop edx
endm

.data

 szBufferAux 	db MAX_PATH dup (0)
.code

;Dialogo AbrirFichero
AbrirFicheroDlg PROC lpFichero:DWORD,lpTitulo :DWORD,lpFiltro:DWORD,nFiltro:DWORD,hWinOwn:DWORD
	LOCAL ofn_Fun:OPENFILENAME
		
			invoke setmem, ADDR ofn_Fun,sizeof OPENFILENAME,0
			 	   
            ; inicializando la estructura del openDialogo
            mov ofn_Fun.lStructSize,        sizeof OPENFILENAME
            mov eax,hWinOwn
            mov ofn_Fun.hwndOwner,eax; hWndOwner,eax
            mov eax,hInstance
            mov ofn_Fun.hInstance,eax
            mov eax, lpFiltro
            mov ofn_Fun.lpstrFilter,eax
            mov eax,nFiltro
            mov ofn_Fun.nFilterIndex,eax
            
            mov eax, lpFichero
            mov ofn_Fun.lpstrFile, eax
            
            ; Verificamos si el fichero existe
    		invoke CreateFile,lpFichero,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
    		.if eax == -1
		    	;Fichero no existe
    			mov eax, lpFichero
    			mov byte ptr ds:[eax],0  ; Para evitar problemas si el fichero indica no existe borramos el buffer	
    		.else
		 		;Fichero existe
    			invoke CloseHandle,eax
    		.endif
    
            mov ofn_Fun.nMaxFile, 260 
            mov eax,lpTitulo
            mov ofn_Fun.lpstrTitle,eax
            mov ofn_Fun.Flags,   OFN_EXPLORER or OFN_FILEMUSTEXIST or  OFN_LONGNAMES
            lea eax,ofn_Fun
            invoke GetOpenFileName,eax 
ret
AbrirFicheroDlg endp


;Dialogo GuardarFichero
GuardarFicheroDlg PROC lpFichero:DWORD,lpTitulo :DWORD,lpFiltro:DWORD,nFiltro:DWORD,hWinOwn:DWORD
	LOCAL ofn_Fun:OPENFILENAME
		
			invoke setmem,ADDR ofn_Fun,sizeof OPENFILENAME,0
    
            ; inicializando la estructura del openDialogo
            mov ofn_Fun.lStructSize,        sizeof OPENFILENAME
            mov eax,hWinOwn
            mov ofn_Fun.hWndOwner, eax
            mov eax,hInstance
            mov ofn_Fun.hInstance,eax
            mov eax, lpFiltro
            mov ofn_Fun.lpstrFilter,eax
            mov eax,nFiltro
            mov ofn_Fun.nFilterIndex,eax
            
            mov eax, lpFichero
            mov ofn_Fun.lpstrFile, eax
     
            ; Verificamos si el fichero existe
    		invoke CreateFile,lpFichero,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
    		.if eax == -1
		    	;Fichero no existe
    			mov eax, lpFichero
    			mov byte ptr ds:[eax],0  ; Para evitar problemas si el fichero indica no existe borramos el buffer	
    		.else
		 		;Fichero existe
    			invoke CloseHandle,eax
    		.endif
    
            mov ofn_Fun.nMaxFile, 260 
            mov eax,lpTitulo
            mov ofn_Fun.lpstrTitle,eax
            mov ofn_Fun.Flags,   OFN_EXPLORER or OFN_FILEMUSTEXIST or  OFN_LONGNAMES
            invoke GetSaveFileName,ADDR ofn_Fun
ret
GuardarFicheroDlg endp

;Dialogo de elección de directorio
DirectorioDLG PROC hWinOwn:DWORD,lpTitulo :DWORD,lpDir:DWORD

	LOCAL PListaItems:DWORD
	LOCAL Dir:BROWSEINFO
		 mov eax,hWinOwn
		 mov Dir.hwndOwner,eax
         mov eax,lpTitulo
         mov Dir.lpszTitle,eax
		 mov eax,lpDir
		 mov Dir.pszDisplayName,eax
		 mov Dir.pidlRoot,0
		 mov Dir.ulFlags,BIF_RETURNONLYFSDIRS
		 mov Dir.lpfn,0
		 invoke SHBrowseForFolder,addr Dir	
         mov PListaItems, eax
         .if eax != 0
			invoke setmem,lpDir,MAX_PATH,0
        	invoke SHGetPathFromIDList,PListaItems,lpDir
         .endif
	ret
DirectorioDLG endp
; SetMem
setmem PROC Address:DWORD,Len:DWORD,Char:BYTE

	pushfd
	push ecx
	push edi
	push eax
	
			mov ecx, Len
			mov edi, Address
setmem_BorraMemoria:
			mov al,Char
			mov byte ptr [edi],al
			inc edi
			loop setmem_BorraMemoria
	pop eax
	pop edi
	pop ecx
	popfd
	
	ret

setmem endp
;memcpy
memcpy PROC Des:DWORD,Src:DWORD, Len:DWORD
	
    push ecx
    push esi
    push edi
    cld		; set direction flag forward
    mov esi, Src	; put address into the source index
    mov edi, Des	; put address into the destination index

    mov ecx, Len	; put the number of bytes to copy in ecx
  ; --------------------------------------------------
  ; repeat copying bytes from ESI to EDI until ecx = 0
  ; --------------------------------------------------
    rep movsb		

    pop edi
    pop esi
    pop ecx
	
	ret

memcpy endp


; Función de comparación 
; EAX = 1 Todo igual 
; EAX = 0 No igual
memcpm PROC Bytes1:DWORD,Bytes2:DWORD,BlockSize:DWORD
 
    push ecx
    push esi
    push edi
    cld		; set direction flag forward
    mov esi, Bytes1	
    mov edi, Bytes2	

    mov ecx, BlockSize	
  
    repe cmpsb
    
    .if ecx !=0
    	mov eax,0
    .else
    	mov eax,1
    .endif		

    pop edi
    pop esi
    pop ecx
	
	ret 

memcpm endp
; Borrar los Items de un ListBOx
ListBoxClean PROC hObject:DWORD
	

ListBoxClean_otro:	
	invoke SendMessage,hObject,LB_GETCOUNT,0,0
	.if eax != LB_ERR
		.if eax !=0
			invoke SendMessage,hObject,LB_DELETESTRING,0,0
			jmp ListBoxClean_otro
		.endif
	.endif
	
	ret

ListBoxClean endp

ComboBoxClean PROC hObject:DWORD
	

ComboBoxClean_otro:	
	invoke SendMessage,hObject,CB_GETCOUNT,0,0
	.if eax != LB_ERR
		.if eax !=0
			invoke SendMessage,hObject,CB_DELETESTRING,0,0
			jmp ComboBoxClean_otro
		.endif
	.endif
	
	ret

ComboBoxClean endp


;Obtener Path o Nombre de un fichero 
; Funcion usa szBufferAux como buffer auxiliar
GetPathOrName Proc FullPath: DWORD, FullPathSize:DWORD, Des:DWORD, NameOrPath:DWORD
	LOCAL Pos:DWORD
; Con esto puedo obtener el Nombre y el Path del fichero seleccionado

  
	invoke GetFullPathName,FullPath,FullPathSize,addr szBufferAux,addr Pos
	.if NameOrPath == 0 ;Nombre
		mov eax,Pos
		lea ebx,szBufferAux
		sub eax,ebx
		mov ebx,eax
		push ebx
		invoke lstrlen,addr szBufferAux
		pop ebx
		sub eax,ebx
		
		mov edx,Pos	
	.else ; Path
		mov eax,Pos
		mov byte ptr ds:[eax],0
		mov eax,Pos
		lea ebx,szBufferAux
		sub eax,ebx
		lea edx,szBufferAux
	.endif
	
	push eax
	invoke memcpy,Des,edx,eax
	pop eax
	mov ebx,Des
	add ebx,eax
	mov byte ptr ds:[ebx],0

			
ret
GetPathOrName endp

;*******************************************************************************
;   Scr: puntero a la cadena
;   Char:  Caracter
;   InitPos: Posición inicial de búsqueda
;   Pos: Puntero a DWORD donde se guarda la posición 
;   Dir: Dirección de búsqueda dentro de la string TRUE  => Incrementando
;                                                  FALSE => Decrementando 
;*******************************************************************************
FindPosCharInStr Proc Scr:DWORD, Char:Byte, InitPos:DWORD, Pos:DWORD, Dir:DWORD



	.if Dir == TRUE
		invoke lstrlen,Scr
		mov ecx,eax; Tamaño de la string
		add ecx,Scr	
	.else
		mov ecx,Scr
	.endif
	
	mov edi,Scr
	add edi,InitPos
	
	
FindPosCharInStr_Check:	
	
	.if Dir == TRUE
		cmp edi,ecx
		jg FindPosCharInStr_fin_WORNG
	.else
		cmp edi,ecx
		jl FindPosCharInStr_fin_WORNG
	.endif

	mov al, byte ptr ds:[edi]
	cmp al,Char
	jz FindPosCharInStr_fin_OK

	.if Dir == TRUE
		inc edi
	.else
		dec edi
	.endif 
	jmp FindPosCharInStr_Check 
	
FindPosCharInStr_fin_OK:
	sub edi,Scr
	mov eax,Pos
	mov dword ptr ds:[eax],edi
	mov eax,1
	jmp FindPosCharInStr_fin

FindPosCharInStr_fin_WORNG:	
	mov eax,Pos
	mov dword ptr ds:[eax],0
	xor eax,eax
	
FindPosCharInStr_fin:	
	
	ret
FindPosCharInStr endp

GetExtension PROC File:DWORD, Exten:DWORD
	
	LOCAL PosPunto:DWORD
	invoke lstrlen,File
	mov edx,eax
	push edx
	invoke FindPosCharInStr,File,'.',edx,addr PosPunto,FALSE
	.if PosPunto == 0
		pop edx
		xor eax,eax
	.else
		;Comprobamos que sea una extensión, para eso la diferencia ha de ser 3 o menor 
		pop edx
		mov eax,PosPunto
		sub edx,eax
		.if edx <= 4 ;el punto se cuenta
			mov eax,File
			add eax,PosPunto
			invoke lstrcpy,Exten,eax
			mov eax,1
		.else
			xor eax,eax
		.endif
	.endif
	ret

GetExtension endp

SetExtension PROC File:DWORD, Exten:DWORD
	
	invoke GetExtension,File,addr szBufferAux
	.if eax == 0 
		invoke lstrcat,File,Exten
	.else
		invoke lstrlen,File
		mov edx,eax
		push edx
		invoke lstrlen,addr szBufferAux
		pop edx
		sub edx,eax
		add edx,File
		invoke lstrcpy,edx,Exten
	.endif
	
	ret

SetExtension endp

TopXY proc wDim:DWORD, sDim:DWORD

    shr sDim, 1      ; divide screen dimension by 2
    shr wDim, 1      ; divide window dimension by 2
    mov eax, wDim    ; copy window dimension into eax
    sub sDim, eax    ; sub half win dimension from half screen dimension

    mov eax,sDim
    ret
TopXY endp

CargarRecursoAMemoria PROC ResourceID:DWORD,TypeResource:DWORD, lpResSize:DWORD
	
	LOCAL hRes:DWORD
	LOCAL HGRes:DWORD
	
	invoke FindResource,NULL, ResourceID, TypeResource
	.if eax == 0
		ret
	.endif
	mov hRes,eax
	
	invoke LoadResource,NULL,hRes
	.if eax == 0
		ret
	.endif

	mov HGRes,eax
	invoke SizeofResource,NULL,hRes
	mov edx,lpResSize
	mov [edx],eax
	invoke LockResource,HGRes
	
	ret

CargarRecursoAMemoria endp
; Función que recibe una cadena y la transforma en su valor numérico correspondiente
; Se tomará como terminador de cadena cualquier carracter distinto de los numéricos (0-9)
CadenaToInt				PROC Scr:DWORD
		
		mov edi,Scr
		xor eax,eax
CadenaToInt_otro:
		xor ebx,ebx
		mov bl,byte ptr ds:[edi]
		sub bl,30h
		cmp bl,0
		jl CadenaToInt_FIN
		cmp bl,9
		jg CadenaToInt_FIN
		imul eax,10	
		add eax,ebx
		inc edi
		jmp CadenaToInt_otro
		
CadenaToInt_FIN:	
	ret

CadenaToInt endp

; Función que recibe una cadena hexagesimal y la transforma en su valor numérico correspondiente
; Se tomará como terminador de cadena cualquier carracter distinto de los numéricos (0..9, a..f,A..F)
HexToInt PROC Scr:DWORD

		mov edi,Scr
		xor eax,eax

HexToInt_otro:
		xor ebx,ebx
		mov bl,byte ptr ds:[edi]
		cmp bl,39h
		jg HexToInt_Alfabeto 
; Numero
			sub bl,30h
			cmp bl,0
			jl HexToInt_FIN
			cmp bl,9
			jg HexToInt_FIN
			jmp HexToInt_itera
HexToInt_Alfabeto:
		and bl,11011111b ;pasamos a mayuscula 
		sub bl,37h 
		cmp bl, 10
		jl 	HexToInt_FIN
		cmp bl,15
		jg HexToInt_FIN				
			
HexToInt_itera:		
		imul eax,10h	
		add eax,ebx
		inc edi
		jmp HexToInt_otro
		
HexToInt_FIN:	
	ret

	
	ret

HexToInt endp

RangoProgressBar PROC HandelProcess:DWORD,Tamano:DWORD

	invoke SetWindowLong, HandelProcess,GWL_USERDATA,Tamano
	
	mov eax,0FFFF0000h
	;shl eax,16
  	invoke SendMessage,HandelProcess,PBM_SETRANGE ,0,eax
	
	
	ret

RangoProgressBar endp

NuevaPosicionProgressBar PROC HandleProcess:DWORD, Pos:DWORD
	LOCAL Tam:DWORD
	LOCAL Aux:DWORD
	mov Aux,0FFFFh
	invoke GetWindowLong,HandleProcess,GWL_USERDATA	
	.if eax != 0
		mov Tam,eax
					
		FINIT	
		FILD Pos
		FILD Aux
		FMUL 
		FILD Tam
		FDIVP st(1),st
		FISTP Pos
	.endif
	
	mov eax,Pos
	
	
	invoke SendMessage,HandleProcess,PBM_SETPOS,eax,0
	ret

NuevaPosicionProgressBar endp

; Función que crea un fichero del tamaño indicado por SizeFile
; Si Machar = 1 en caso de encontrarse un fichero con el mismo nombre se lo carga
; eax = 0 Error
; eax = 1 OK
CrearFicheroEnBlanco PROC Nombre:DWORD, SizeFile:DWORD,Machacar:DWORD 
	
	LOCAL HFile:DWORD 
	
	mov eax, Machacar
	.if eax == 1
		invoke CreateFile,Nombre,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL
	.else
		invoke CreateFile,Nombre,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE,NULL	
	.endif
	
	.if eax == INVALID_HANDLE_VALUE
		xor eax,eax
		ret
	.endif
	mov HFile,eax
	
	invoke SetFilePointer,HFile, SizeFile,NULL,FILE_BEGIN
	.if eax == -1
		invoke CloseHandle,HFile
		xor eax,eax
		ret
	.endif

	invoke SetEndOfFile,HFile
	.if eax == 0
		invoke CloseHandle,HFile
		xor eax,eax
		ret
	.endif
	
	invoke CloseHandle,HFile
	mov eax,1	
	
	ret

CrearFicheroEnBlanco endp


; Función para búsqueda de cadenas
BusquedaCad PROC PBloque:DWORD,lonBloque:DWORD,IniIndex:DWORD,PCad:DWORD

		LOCAL Pos:DWORD
		LOCAL Flag:DWORD
		LOCAL LengCad:DWORD
		LOCAL PosBus:DWORD
		LOCAL buff:DWORD
        
        mov Pos,0
        mov Flag,0
        
        mov esi,PBloque
        add esi,IniIndex 
        mov PosBus,esi


		invoke lstrlen,PCad
		mov LengCad,eax 

		inc eax
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,eax
		mov buff,eax
        
BusquedaCad_INI_While:

		mov esi,PBloque
		add esi,lonBloque
		
		cmp esi,PosBus
		jle BusquedaCad_FIN_While

		mov eax,Flag
		cmp eax,1
		je BusquedaCad_FIN_While
		
	       	mov esi,PosBus
			mov edi,PCad
            mov al, byte ptr ds:[esi]
            mov bl,byte ptr ds:[edi]
            .if al == bl
                
               mov edi,LengCad
               inc edi
               invoke memcpy,buff,PosBus,edi
                        
               invoke lstrcmp,buff,PCad
               .if eax == 0
                   	mov Flag,1
              .endif

           .endif
           inc PosBus
        jmp BusquedaCad_INI_While

BusquedaCad_FIN_While:
        
        .if Flag == 1
        	mov eax,PosBus
        	sub eax,PBloque
        	dec eax
        	mov Pos,eax
        .else
        	mov Pos,-1
        .endif
        
        invoke LocalFree,buff
        

	mov eax,Pos
	ret 
ret
BusquedaCad endp

AnadirColumnaLW			PROC Handle:DWORD,NameCol:DWORD,WidthCol:DWORD

	LOCAL Columna_Aux:LV_COLUMN
	LOCAL Index:DWORD
	
	invoke GetColumCountLW,Handle
	mov Index,eax
	
	mov Columna_Aux.imask,LVCF_TEXT	or LVCF_FMT	or LVCF_WIDTH	
	mov eax,WidthCol
	mov Columna_Aux.lx,eax
	mov Columna_Aux.fmt,LVCFMT_LEFT
	mov eax,Index		
	mov Columna_Aux.iSubItem,eax
	
	mov eax,NameCol
	mov Columna_Aux.pszText,eax 
	invoke lstrlen,NameCol
	mov Columna_Aux.cchTextMax,eax
	
	invoke SendMessage,Handle,LVM_INSERTCOLUMN,Index,addr Columna_Aux

	mov eax,Index
ret
AnadirColumnaLW endp
BorrarTodasLasColumnasLW	proc Handle:DWORD
	
	.if Handle !=NULL
	
BorrarTodasLasColumnasLW_BorraColumnas:		
		invoke SendMessage,Handle,LVM_DELETECOLUMN,0,0
		cmp eax,TRUE
		je BorrarTodasLasColumnasLW_BorraColumnas
		
	.endif
	
	
	ret

BorrarTodasLasColumnasLW endp

GetColumCountLW PROC Handle:DWORD
	
	LOCAL Index:DWORD
	LOCAL Columna_Aux:LV_COLUMN
	mov Index,0
	
	mov Columna_Aux.imask,LVCF_WIDTH
GetColumCountLW_Otra:
	 
	invoke SendMessage,Handle,LVM_GETCOLUMN,Index,addr Columna_Aux 
	.if eax != 0
		inc Index
		jmp GetColumCountLW_Otra
	.endif
	
	mov eax,Index
	ret

GetColumCountLW endp

AnadirTextLW PROC Handle:DWORD,NameItem:DWORD,NCol:DWORD
	LOCAL Index:DWORD
	LOCAL Item_Aux:LV_ITEM
	
	
		
	invoke GetItemCountLW,Handle
	dec eax
	
	cmp eax,0
	jge	AnadirTextLW_IndexOK
		xor eax,eax
AnadirTextLW_IndexOK:
	mov ebx,NCol
	.if ebx == 0
		inc eax
	.endif	
	mov Index,eax
	
	mov Item_Aux.imask,LVIF_TEXT
	mov eax,Index
	mov Item_Aux.iItem,eax
	mov eax,NCol
	mov Item_Aux.iSubItem,eax
	mov eax,NameItem
	mov Item_Aux.pszText,eax
	invoke lstrlen,eax
	inc eax
	mov Item_Aux.cchTextMax,eax
	mov Item_Aux.iImage,0
	mov Item_Aux.lParam,0

	mov eax,NCol	
	.if eax == 0
		invoke SendMessage,Handle,LVM_INSERTITEM,0,addr Item_Aux
	.else
		invoke SendMessage,Handle,LVM_SETITEM,0,addr Item_Aux
	.endif

	ret

AnadirTextLW endp

InsertarTextoLW proc Handle:DWORD,NameItem:DWORD,Pos:DWORD,NCol:DWORD
	LOCAL Item_Aux:LV_ITEM
	
	mov eax,Pos
	cmp eax,0
	jge InsertarTextoLW_IndexOK
		xor eax,eax
		ret
		
InsertarTextoLW_IndexOK:
	mov ebx,NCol
	.if ebx == 0
		inc eax
	.endif	
		
	mov Item_Aux.imask,LVIF_TEXT
	mov eax,Pos
	mov Item_Aux.iItem,eax
	mov eax,NCol
	mov Item_Aux.iSubItem,eax
	mov eax,NameItem
	mov Item_Aux.pszText,eax
	invoke lstrlen,eax
	inc eax
	mov Item_Aux.cchTextMax,eax
	mov Item_Aux.iImage,0
	mov Item_Aux.lParam,0

	mov eax,NCol	
	.if eax == 0
		invoke SendMessage,Handle,LVM_INSERTITEM,0,addr Item_Aux
	.else
		invoke SendMessage,Handle,LVM_SETITEM,0,addr Item_Aux
	.endif


ret
InsertarTextoLW endp

GetItemCountLW PROC Handle:DWORD
	
	
	invoke SendMessage,Handle,LVM_GETITEMCOUNT,0,0
	
	ret

GetItemCountLW endp

BorrarItemsLW PROC Handle:DWORD
	
	invoke SendMessage,Handle,LVM_DELETEALLITEMS,0,0
	
	ret

BorrarItemsLW endp


GetCampoString PROC Delimitador:BYTE,Index:DWORD,pStringIn:DWORD,pStringOUT:DWORD
	LOCAL len:DWORD
	
	; Buscamos el Índice del campo a buscar
	
	invoke lstrlen,pStringIn
	mov len,eax
	
	mov esi,pStringIn
	mov edi,pStringOUT 
	
	xor ebx,ebx ;indice para el String de Entrada
	
	xor ecx,ecx ; Control de Delimitadores encontrados

GetCampoString_cmp_Index:

	cmp ecx,Index
	je  GetCampoString_copia  ; Si hemos llegado al delimitador pasamos a copiar

	cmp ebx,len
	je GetCampoString_FIN      ; Si hemos llegado al tope de la cadena FIN
GetCampoString_sigue_index:		
		mov al,byte ptr ds:[esi+ebx]
		inc ebx               ; Incrementamos el contador 
		cmp al,Delimitador
		je GetCampoString_incIndex ; Si es un delimitador incrementamos y comprobamos 
		
		
		jmp GetCampoString_sigue_index  ; Pasamos a comprobar el siguiente dato

GetCampoString_incIndex:
		inc ecx
		jmp GetCampoString_cmp_Index 	
	
GetCampoString_copia:
; Se realiza la copia mientras no se llege a otro delimitador o Fin de String 
	cmp ebx,len
	je GetCampoString_FIN
	
		mov al,byte ptr ds:[esi+ebx]
		inc ebx               ; Incrementamos el contador 
		cmp al,Delimitador
		je GetCampoString_FIN
		
			mov byte ptr ds:[edi],al ; Copiamos el dato 
			inc edi
		jmp GetCampoString_copia

GetCampoString_FIN:	
	mov byte ptr ds:[edi],0 ; Fin de String

ret
GetCampoString endp


PosicionCaret PROC hCtlEdit:DWORD, pPos:DWORD
    LOCAL cpMin:DWORD
    LOCAL cpMax:DWORD
    LOCAL BUFF[32]  :BYTE
	LOCAL lin:DWORD
	LOCAL col:DWORD
	    
    invoke SendMessage,hCtlEdit,EM_GETSEL,addr cpMin,ADDR cpMax
    invoke SendMessage,hCtlEdit,EM_LINEFROMCHAR,cpMin,0
    mov lin,eax
    invoke SendMessage,hCtlEdit,EM_LINEINDEX,-1,0
    
    mov ebx,cpMin
    sub ebx,eax
    mov col,ebx
    
    mov esi,pPos
    assume esi: ptr EDITPOS
    	mov eax,lin
    	mov [esi].lin,eax
    	mov eax,col
    	mov [esi].col,eax
    assume esi:NOTHING
    
ret
PosicionCaret  endp

isprint PROC char:BYTE

	xor eax,eax
	mov al,char
	
	.if al < 20h
		xor eax,eax
		ret
	.elseif ( (al> 7Eh && al < 0A1h) && al != 91h && al != 92 )
			xor eax,eax
			ret
	.else
			mov eax,1
	
	.endif
	
	ret

isprint endp

isalpha proc char:BYTE
	
	xor eax,eax
	mov al,char
	.if (al >= 41h && al<=5ah) || (al>= 61h && al<=7Ah)
		mov eax,TRUE
	.else
		mov eax,FALSE
	.endif
	
	ret

isalpha endp

isalnum	proc char:BYTE

	xor eax,eax
	mov al,char
	.if (al >= 30h && al<=39h) || (al >= 41h && al<=5ah) || (al>= 61h && al<=7Ah)
		mov eax,TRUE
	.else
		mov eax,FALSE
	.endif
	
	ret
	
isalnum endp

isdigit proc char:BYTE
	
	xor eax,eax
	mov al,char
	.if (al >= 30h && al<=39h) 
		mov eax,TRUE
	.else
		mov eax,FALSE
	.endif
	
	
	ret

isdigit endp

isxdigit proc char:BYTE

	xor eax,eax
	mov al,char
	.if (al >= 30h && al<=39h) || (al >=41h && al<=46h) || (al >=61h && al <=66h) 
		mov eax,TRUE
	.else
		mov eax,FALSE
	.endif
	
	
	ret

isxdigit endp

strnicmp	proc lpStr1:DWORD,lpStr2:DWORD,lenBlock:DWORD
	LOCAL str1Local:DWORD
	LOCAL str2Local:DWORD
	
	mov edx,lenBlock
	inc edx
	push edx
	push edx
	push edx
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
	mov str1Local,eax

	pop edx
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
	mov str2Local,eax
	
	pop edx
	invoke lstrcpyn,str1Local,lpStr1,edx
	
	pop edx
	invoke lstrcpyn,str2Local,lpStr2,edx
	
	invoke lstrcmpi,str1Local,str2Local
	push eax
	
	invoke LocalFree,str2Local
	invoke LocalFree,str1Local
	pop eax
	
	ret

strnicmp endp

DrawLine PROC hDC:DWORD,x1:DWORD,y1:DWORD,x2:DWORD,y2:DWORD
	
	
	invoke MoveToEx,hDC,x1,y1,NULL
	invoke LineTo,hDC,x2,y2
	ret

DrawLine endp

DrawRect PROC hDC:DWORD,x1:DWORD,y1:DWORD,x2:DWORD,y2:DWORD

	invoke DrawLine,hDC,x1,y1,x2,y1
	invoke DrawLine,hDC,x1,y2,x2,y2
	invoke DrawLine,hDC,x1,y1,x1,y2
	invoke DrawLine,hDC,x2,y1,x2,y2
		
	ret

DrawRect endp



FileExist PROC pszFile:DWORD
		
		invoke CreateFile,pszFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
		.if eax == INVALID_HANDLE_VALUE
			xor eax,eax
		.else
			invoke CloseHandle,eax
			mov eax,1
		.endif
	ret

FileExist endp


CheckExtension PROC pFile:DWORD,pExt:DWORD
	LOCAL BuffExt[5]:BYTE
	
	invoke GetExtension,pFile,addr BuffExt
	lea eax,BuffExt
	xor ebx,ebx
	mov bl,byte ptr ds:[eax]
	.if bl ==0
		invoke SetExtension,pFile,pExt
	.endif
	
	ret

CheckExtension endp

ObtenerSubTextEdit PROC hEditCtrl:DWORD,Index:DWORD,NCaracteres:DWORD,pBuffer:DWORD
	
	LOCAL pDatos:DWORD
	LOCAL DatosSingelLine:DWORD
	LOCAL MaxLeng:DWORD
	
	mov DatosSingelLine,0
	invoke SendMessage,hEditCtrl,WM_GETTEXTLENGTH,0,0
	mov MaxLeng,eax
	invoke SendMessage,hEditCtrl,EM_GETHANDLE,0,0
	.if eax != 0
		; Estamos en un MultiLine
		
		mov eax,[eax]
		mov pDatos,eax
	.else
		; Es un sigle Line se tiene que tener TODA la string
		mov edx,MaxLeng
		inc edx
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT, edx
		mov DatosSingelLine,eax
		
		mov edx,MaxLeng
		inc edx
		invoke SendMessage,hEditCtrl,WM_GETTEXT,edx,DatosSingelLine
		
		mov eax, DatosSingelLine
		mov pDatos,eax
	.endif
	xor edx,edx
	mov dl,[eax+1]
	.if dl == 0
		; Unicode
		mov eax,Index
		shl eax,1
		add pDatos,eax
		mov edi,pBuffer
		mov esi,pDatos
		xor ecx,ecx
		
ObtenerSubTextEdit_UNI_otro:
		
		cmp ecx,NCaracteres
		je ObtenerSubTextEdit_UNI_END
			mov al,[esi]
			mov byte ptr ds:[edi],al
			inc edi
			add esi,2
			inc ecx
			jmp ObtenerSubTextEdit_UNI_otro

ObtenerSubTextEdit_UNI_END:
		mov byte ptr ds:[edi],0
				
	.else 
		; ASCII
		mov eax,Index
		add pDatos,eax
		mov edi,pBuffer
		mov esi,pDatos
		xor ecx,ecx
ObtenerSubTextEdit_ASC_otro:
		
		cmp ecx,NCaracteres
		je ObtenerSubTextEdit_ASC_END
			mov al,[esi]
			mov byte ptr ds:[edi],al
			inc edi
			inc esi
			inc ecx
			jmp ObtenerSubTextEdit_ASC_otro

ObtenerSubTextEdit_ASC_END:
		mov byte ptr ds:[edi],0
	.endif
	
	.if DatosSingelLine != 0
		invoke LocalFree, DatosSingelLine
	.endif
	
	ret

ObtenerSubTextEdit endp

AnadirImagen  PROC hImagen:DWORD,HPicture:DWORD

	invoke SendMessage,hImagen,STM_SETIMAGE,IMAGE_ICON,HPicture 	
	
	ret

AnadirImagen endp

AnadirImagenBMP proc hImagen:DWORD,HPicture:DWORD

	invoke SendMessage,hImagen,STM_SETIMAGE,IMAGE_BITMAP,HPicture
ret
AnadirImagenBMP endp
EditHexProc	proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	
	mov eax,uMsg
	.if eax==WM_CHAR
		mov eax,wParam
		.if al >= '0' && al <= '9' ; 0..9 => 30h..39h
				; Son números no se tocan

				invoke GetWindowLong,hWin,GWL_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
				mov edi,eax
				invoke CallWindowProc,edi,hWin,uMsg,wParam,lParam	
		.elseif al>='a' && al <= 'f'  ; a..f => 61h..66h
					; son de la a..f pasar a mayusculas antes de enviarlo
					
					and al,11011111b ;pasamos a mayuscula
					mov wParam,eax
					
					invoke GetWindowLong,hWin,GWL_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
					mov edi,eax
					invoke CallWindowProc,edi,hWin,uMsg,wParam,lParam
		.elseif al >='A' && al <= 'F' ; A..F => 41h..46h		
					; son de la A..F no hace falta tocar nada
					invoke GetWindowLong,hWin,GWL_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
					mov edi,eax
					invoke CallWindowProc,edi,hWin,uMsg,wParam,lParam
		.elseif al == 8 ; El botón de Borrar
			invoke GetWindowLong,hWin,GWL_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
			mov edi,eax
			invoke CallWindowProc,edi,hWin,uMsg,wParam,lParam
			 
		.else
			xor eax,eax
			ret
		.endif
	.else
		invoke GetWindowLong,hWin,GWL_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
		mov edi,eax
		invoke CallWindowProc,edi,hWin,uMsg,wParam,lParam	
	.endif

	ret
EditHexProc endp


SetEditHex	proc handle:HWND

	invoke GetWindowLong,handle,GWL_WNDPROC
	mov edi,eax
	invoke SetWindowLong,handle,GWL_USERDATA,edi
	invoke SetWindowLong,handle,GWL_WNDPROC,offset EditHexProc
	ret
SetEditHex endp


UnSetEditHex proc handle:HWND

	invoke GetWindowLong,handle,GWL_USERDATA
	mov edi,eax
	invoke SetWindowLong,handle,GWL_WNDPROC,edi
	ret
UnSetEditHex endp

AsciiHexToInt	PROC Dato:DWORD
	
	mov eax,Dato
	and eax,0FFh; nos quedamos con el Byte
	
	.if eax >= '0' && eax <= '9'
		sub eax,'0'
	.elseif eax >= 'a' && eax <='f'
		sub eax,'a'
		add eax,10
	.elseif eax >= 'A' && eax <='F'
		sub eax,'A'
		add eax,10
	.else 
		mov eax,-1
	.endif
	ret

AsciiHexToInt endp

IsMenuItemCheck proc HandleMenu:DWORD,IDItem:DWORD
	LOCAL MenuItemInf:MENUITEMINFO 
	
	invoke setmem,addr MenuItemInf,sizeof MENUITEMINFO,0
	mov MenuItemInf.cbSize,sizeof MENUITEMINFO 
	mov MenuItemInf.fMask,MIIM_STATE	
				
	invoke GetMenuItemInfo,HandleMenu,IDItem,FALSE,addr MenuItemInf
	
	mov eax,MenuItemInf.fState
	
	
	ret

IsMenuItemCheck endp
; El resultado de la operación se guardará en ST(0)
pow10	proc Exp:DWORD
	LOCAL Base_Pow:DWORD
	LOCAL AuxFloat:QWORD
	LOCAL AuxInteger:DWORD
	
	push ecx
	
	mov Base_Pow,1
	finit ; inicializamos el coprocesador
	fld1
	FSTP AuxFloat
	
	mov eax,Exp
	cmp eax,0
	jge pow10_SingoMayor	
		neg eax
		mov Exp,eax
		mov Base_Pow,-1

pow10_SingoMayor:
		
	mov ecx,Exp
pow10_OTRO:
	
	cmp ecx,0
	je pow10_FIN
		
			mov  AuxInteger,10
			
			fld AuxFloat
			fild AuxInteger
			.if Base_Pow == -1
				fdiv 
				
			.else
				fmul
			.endif
			fstp AuxFloat
			dec ecx
			jmp pow10_OTRO 
		 	 
pow10_FIN:		  
	fld AuxFloat
	
	pop ecx
	ret

pow10 endp

; Handle: Handle del control TreeView
; hPar:   Handle del nodo parde
; lpStr:  Puntero a String que se mostrará en el nodo
; nImg:   Index de la imagen para el nodo
;
; Devuelve el Handle Del nuevo Nodo o NULL si error
NodoArbloTV proc Handle:DWORD,hPar:DWORD,lpStr:DWORD,nImg:DWORD
	LOCAL	tvins:TV_INSERTSTRUCT

	mov		eax,hPar
    mov		tvins.hParent,eax
    ;Saveing hPar simplifies building path
    ;when user selects an item
    mov		tvins.item.lParam,eax
    mov		tvins.hInsertAfter,0
    mov		tvins.item.imask,TVIF_TEXT or TVIF_PARAM or TVIF_IMAGE or TVIF_SELECTEDIMAGE
	mov		eax,lpStr
	mov		tvins.item.pszText,eax
	mov		eax,nImg
    mov		tvins.item.iImage,eax
    mov		tvins.item.iSelectedImage,eax
    invoke SendMessage,Handle,TVM_INSERTITEM,0,addr tvins
    ret

NodoArbloTV endp
