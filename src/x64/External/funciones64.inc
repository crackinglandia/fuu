; $Id: funciones64.inc 61 2010-07-12 17:16:52Z nahuelriva $

IFNDEF __Funciones64__
__Funciones64__	equ 1


funcproto LOCAL,setmem,QWORD,QWORD,BYTE
funcproto LOCAL,memcpy,QWORD,QWORD,QWORD
funcproto LOCAL,memcpm,QWORD,QWORD,QWORD
	
funcproto LOCAL,CadenaToInt,QWORD
funcproto LOCAL,HexToInt,QWORD	
	
funcproto LOCAL,AbrirFicheroDlg,QWORD,QWORD,QWORD,DWORD,QWORD
funcproto local,GuardarFicheroDlg,QWORD,QWORD,QWORD,DWORD,QWORD
funcproto LOCAL,DirectorioDLG,QWORD,QWORD,QWORD

funcproto LOCAL,CrearFicheroEnBlanco,QWORD,DWORD,QWORD

funcproto LOCAL,SetEditHex,HWND
funcproto LOCAL,UnSetEditHex,HWND
funcproto LOCAL,EditHexProc,HWND,UINT,WPARAM,LPARAM


funcproto LOCAL,SetEditReadOnly,HWND
funcproto LOCAL,UnSetEditReadOnly,HWND
funcproto LOCAL,EditReadOnlyProc,HWND,UINT,WPARAM,LPARAM


funcproto LOCAL,FormateoBuffer,QWORD,DWORD,BYTE
funcproto LOCAL,AnadirImagen, QWORD,QWORD
funcproto LOCAL,AnadirImagenBMP,QWORD,QWORD

; Funciones para la decodificación del TimeDateStamp
funcproto LOCAL,TimeToTimeDateStamp,QWORD
funcproto LOCAL,TimeDataDescription,DWORD,QWORD
funcproto LOCAL,EsAnnoBisiesto,QWORD	
funcproto LOCAL,dias_mes,QWORD,QWORD

.data
szBufferAux db MAX_PATH dup(0)

.code

; SetMem
function setmem,Address:QWORD,Len:QWORD,Char:BYTE

	pushfq
	
	mov rcx, Len
	mov rdi, Address
	
setmem_BorraMemoria:
	
	mov al,Char
	mov byte ptr [rdi],al
	inc rdi
	
	loop setmem_BorraMemoria
	popfq

exitf	
	

;memcpy
function memcpy,Des:QWORD,Src:QWORD, Len:QWORD
	
    cld		; set direction flag forward
    mov rsi, Src	; put address into the source index
    mov rdi, Des	; put address into the destination index

    mov rcx, Len	; put the number of bytes to copy in ecx
  ; --------------------------------------------------
  ; repeat copying bytes from RSI to RDI until RCX = 0
  ; --------------------------------------------------
    rep movsb		
exitf


; Función de comparación 
; RAX = 1 Todo igual 
; RAX = 0 No igual
function memcpm,Bytes1:QWORD,Bytes2:QWORD,BlockSize:QWORD
 
    cld		; set direction flag forward
    mov rsi, Bytes1	
    mov rdi, Bytes2	

    mov rcx, BlockSize	
  
    repe cmpsb
    
    @IF <<cmp rcx,0>>,NOEQUAL?
    	return 0
    @ELSE
    	return 1
    @ENDIF		

exitf


; Función que recibe una cadena y la transforma en su valor numérico correspondiente
; Se tomará como terminador de cadena cualquier carracter distinto de los numéricos (0-9)
function CadenaToInt,Scr:QWORD
		
		mov rdi,Scr
		xor rax,rax
CadenaToInt_otro:
		xor rbx,rbx
		mov bl,byte ptr [rdi]
		sub bl,30h
		cmp bl,0
		jl CadenaToInt_FIN
		cmp bl,9
		jg CadenaToInt_FIN
		imul rax,10	
		add rax,rbx
		inc rdi
		jmp CadenaToInt_otro
		
CadenaToInt_FIN:
	
		return rax	
exitf


; Función que recibe una cadena hexagesimal y la transforma en su valor numérico correspondiente
; Se tomará como terminador de cadena cualquier carracter distinto de los numéricos (0..9, a..f,A..F)
function HexToInt,Scr:QWORD

		mov rdi,Scr
		xor rax,rax

HexToInt_otro:
		xor rbx,rbx
		mov bl,byte ptr [rdi]
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
		imul rax,10h	
		add rax,rbx
		inc rdi
		jmp HexToInt_otro
		
HexToInt_FIN:	

		return rax
exitf

;Dialogo AbrirFichero
; Si se cancela o cierras rax = 0
function AbrirFicheroDlg,lpFichero:QWORD,lpTitulo :QWORD,lpFiltro:QWORD,nFiltro:DWORD,hWinOwn:QWORD
	begin_alloc
		alloc_var ofn_Fun:OPENFILENAME
	end_alloc
	
		
	invoke setmem,addr ofn_Fun, sizeof OPENFILENAME,0
			 	   
    ; inicializando la estructura del openDialogo
    mov ofn_Fun.OPENFILENAME.lStructSize,        sizeof OPENFILENAME
    mov rax,hWinOwn
    mov ofn_Fun.OPENFILENAME.hWndOwner,rax
    mov rax,hInstance
    mov ofn_Fun.OPENFILENAME.hInstance,rax
    mov rax, lpFiltro
    mov ofn_Fun.OPENFILENAME.lpstrFilter,rax
    mov eax,nFiltro
    mov ofn_Fun.OPENFILENAME.nFilterIndex,eax
            
    mov rax, lpFichero
    mov ofn_Fun.OPENFILENAME.lpstrFile, rax
   
   ; Verificamos si el fichero existe
    invoke CreateFile,lpFichero,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
    @IF <<cmp eax,-1>>,EQUAL?
    	;Fichero no existe
    	mov rax, lpFichero
    	mov byte ptr [rax],0  ; Para evitar problemas si el fichero indica no existe borramos el buffer	
    @ELSE
 		;Fichero existe
    	invoke CloseHandle,rax
    @ENDIF
 
    mov ofn_Fun.OPENFILENAME.nMaxFile, 260 
    mov rax,lpTitulo
    mov ofn_Fun.OPENFILENAME.lpstrTitle,rax
    mov ofn_Fun.OPENFILENAME.Flags,   OFN_EXPLORER or OFN_FILEMUSTEXIST or  OFN_LONGNAMES
    lea rax,ofn_Fun
    invoke GetOpenFileName,rax 
exitf


;Dialogo GuardarFichero
function GuardarFicheroDlg,lpFichero:QWORD,lpTitulo:QWORD,lpFiltro:QWORD,nFiltro:DWORD,hWinOwn:QWORD
	begin_alloc
		alloc_var ofn_Fun:OPENFILENAME
	end_alloc

	invoke setmem,addr ofn_Fun, sizeof OPENFILENAME,0
    
    ; inicializando la estructura del openDialogo
    mov ofn_Fun.OPENFILENAME.lStructSize,        sizeof OPENFILENAME
    mov rax,hWinOwn
    mov ofn_Fun.OPENFILENAME.hWndOwner, rax
    mov rax,hInstance
    mov ofn_Fun.OPENFILENAME.hInstance,rax
    mov rax, lpFiltro
    mov ofn_Fun.OPENFILENAME.lpstrFilter,rax
    mov eax,nFiltro
    mov ofn_Fun.OPENFILENAME.nFilterIndex,eax
            
    mov rax, lpFichero
    mov ofn_Fun.OPENFILENAME.lpstrFile, rax    
  
    ; Verificamos si el fichero existe
    invoke CreateFile,lpFichero,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
    @IF <<cmp eax,-1>>,EQUAL?
    	;Fichero no existe
    	mov rax, lpFichero
    	mov byte ptr [rax],0	; Para evitar problemas si el fichero indica no existe borramos el buffer
    @ELSE
 		;Fichero existe
    	invoke CloseHandle,rax
    @ENDIF
  
 	mov ofn_Fun.OPENFILENAME.nMaxFile, 260 
    mov rax,lpTitulo
    mov ofn_Fun.OPENFILENAME.lpstrTitle,rax
    mov ofn_Fun.OPENFILENAME.Flags,   OFN_EXPLORER or OFN_LONGNAMES or OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST
   invoke GetSaveFileName,addr ofn_Fun
exitf

;Dialogo de elección de directorio
function DirectorioDLG,hWinOwn:QWORD,lpTitulo:QWORD,lpDir:QWORD
	begin_alloc
		alloc_var PListaItems:QWORD
		alloc_var Dir:BROWSEINFO
	end_alloc

    mov rax,hWinOwn
    mov Dir.BROWSEINFO.hwndOwner,rax
    mov rax,lpTitulo
    mov Dir.BROWSEINFO.lpszTitle,rax
	mov rax,lpDir
    mov Dir.BROWSEINFO.pszDisplayName,rax
    mov Dir.BROWSEINFO.pidlRoot,0
    mov Dir.BROWSEINFO.ulFlags,BIF_RETURNONLYFSDIRS
    mov Dir.BROWSEINFO.lpfn,0
    invoke SHBrowseForFolder,addr Dir	
    mov PListaItems, rax
 	@IF <<cmp rax,0>>,NOEQUAL?
			invoke setmem,lpDir,MAX_PATH,0
        	invoke SHGetPathFromIDList,PListaItems,lpDir
 	@ENDIF
exitf

; Función que crea un fichero del tamaño indicado por SizeFile
; Si Machar = 1 en caso de encontrarse un fichero con el mismo nombre se lo carga
; eax = 0 Error
; eax = 1 OK
function CrearFicheroEnBlanco,LpNombre:QWORD,SizeFile:DWORD,Machacar:QWORD 
	begin_alloc
		alloc_var HFile:QWORD
	end_alloc
	
		
	mov rax, Machacar
	
	@IF <<cmp rax,1>>,EQUAL?
		invoke CreateFile,LpNombre,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL
	@ELSE
		invoke CreateFile,LpNombre,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE,NULL	
	@ENDIF
	
	@IF <<cmp rax,INVALID_HANDLE_VALUE>>,EQUAL?
		return FALSE
	@ENDIF
	
	mov HFile,rax
	
	invoke SetFilePointer,HFile, SizeFile,NULL,FILE_BEGIN
	@IF <<cmp eax,-1>>,EQUAL?
		invoke CloseHandle,HFile
		return FALSE
	@ENDIF

	invoke SetEndOfFile,HFile
	@IF <<cmp eax,0>>,EQUAL?
		invoke CloseHandle,HFile
		return FALSE
	@ENDIF
	
	invoke CloseHandle,HFile
	return TRUE	
exitf


function EditHexProc,hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	
	mov eax,uMsg
	@IF <<cmp eax,WM_CHAR>>,EQUAL?
		mov rax,wParam
		@IF <<cmp al,'0'>>,ABOVE?||EQUAL? ; 0..9 => 30h..39h
			@IF <<cmp al,'9'>>,BELOW?||EQUAL? 
				; Son números no se tocan

				invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
				mov rdi,rax
				invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam	
			@ELSEIF <<cmp al,'a'>>,ABOVE?||EQUAL? ; a..f => 61h..66h
				@IF <<cmp al,'f'>>,BELOW?||EQUAL?
					; son de la a..f pasar a mayusculas antes de enviarlo
					
					and al,11011111b ;pasamos a mayuscula
					mov wParam,rax
					
					invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
					mov rdi,rax
					invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam
					
				@ELSE
					return FALSE
				@ENDIF
			@ELSEIF <<cmp al,'A'>>,ABOVE?||EQUAL? ; A..F => 41h..46hh
				@IF <<cmp al,'F'>>,BELOW?||EQUAL?
					; son de la A..F no hace falta tocar nada
					invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
					mov rdi,rax
					invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam
				@ELSE
					return FALSE
				@ENDIF
			@ELSE
				return FALSE	
			@ENDIF
		@ELSEIF <<cmp al,8>>,EQUAL?
			 ; El botón de Borrar
			invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
			mov rdi,rax
			invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam
			 
		@ELSE
			return FALSE
		@ENDIF
	@ELSE
		invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
		mov rdi,rax
		invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam	
	@ENDIF


exitf


function SetEditHex,handle:HWND

	invoke GetWindowLongPtr,handle,GWLP_WNDPROC
	mov rdi,rax
	invoke SetWindowLongPtr,handle,GWLP_USERDATA,rdi
	invoke SetWindowLongPtr,handle,GWLP_WNDPROC,offset EditHexProc

exitf

function UnSetEditHex,handle:HWND

	invoke GetWindowLongPtr,handle,GWLP_USERDATA
	mov rdi,rax
	invoke SetWindowLongPtr,handle,GWLP_WNDPROC,rdi
	
exitf

function EditReadOnlyProc,hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	
	mov eax,uMsg
	@IF <<cmp eax,WM_CHAR>>,EQUAL?
		return FALSE	
	@ELSEIF <<cmp eax,WM_PASTE>>,EQUAL?
		return FALSE
	@ELSEIF <<cmp eax,WM_CUT>>,EQUAL?
		return FALSE
	@ELSEIF <<cmp eax,WM_KEYDOWN>>,EQUAL?
		mov rax,wParam
		@IF <<cmp rax,VK_DELETE>>,EQUAL?
			
			return FALSE
		@ELSE
			invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
			mov rdi,rax
			invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam	
		@ENDIF
		
	@ELSE
		invoke GetWindowLongPtr,hWin,GWLP_USERDATA ; En USER DATA tenemos el antiguo offset a la ventana gestora del mensajes
		mov rdi,rax
		invoke CallWindowProc,rdi,hWin,uMsg,wParam,lParam	
	@ENDIF


exitf


function SetEditReadOnly,handle:HWND

	invoke GetWindowLongPtr,handle,GWLP_WNDPROC
	mov rdi,rax
	invoke SetWindowLongPtr,handle,GWLP_USERDATA,rdi
	invoke SetWindowLongPtr,handle,GWLP_WNDPROC,offset EditReadOnlyProc

exitf

function UnSetEditReadOnly,handle:HWND

	invoke GetWindowLongPtr,handle,GWLP_USERDATA
	mov rdi,rax
	invoke SetWindowLongPtr,handle,GWLP_WNDPROC,rdi
	
exitf


function FormateoBuffer,lpBuff:QWORD,NChar:DWORD,Char:BYTE
	begin_alloc
		alloc_var pBuff:QWORD
		alloc_var Len:DWORD
	end_alloc
	mov eax,NChar
	inc eax   ; para soportar el terminador de cadena
	mov Len,eax 
	
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,Len
	mov pBuff,rax
	
	invoke lstrlen,lpBuff
	@IF <<cmp rax,NChar>>,BELOW?
	
	
		mov rbx,rax
		xor rax,rax
		mov eax,NChar
		sub rax,rbx
		
		@IF <<cmp rax,0>>,NOEQUAL?
			; Formateamos el buffer
			mov rsi,pBuff
			mov byte ptr [rsi],0 ; vacio
				
FormateoBuffer_otro:
			cmp rax,0
			je FormateoBuffer_FIN
				mov bl,Char
				mov byte ptr [rsi],bl
				inc rsi
				dec rax
				jmp FormateoBuffer_otro

FormateoBuffer_FIN:
			mov byte ptr [rsi],0 ; fin de cadena
				
			invoke lstrcat,pBuff,lpBuff
			invoke lstrcpyn,lpBuff,pBuff,Len
		@ENDIF
	@ELSE
		mov rsi,lpBuff
		add rsi,NChar
		mov byte ptr [rsi],0 ; El buffer es más grande que el soportado, así que lo truncamos
	@ENDIF
	invoke LocalFree,pBuff	
exitf


function AnadirImagen, hImagen:QWORD,HPicture:QWORD

	invoke SendMessage,hImagen,STM_SETIMAGE,IMAGE_ICON,HPicture 	
	
exitf	


function AnadirImagenBMP, hImagen:QWORD,HPicture:QWORD

	invoke SendMessage,hImagen,STM_SETIMAGE,IMAGE_BITMAP,HPicture
exitf


;************ TimeDateStamp a System Time

; Siendo lpTimepoAux un puntero a SYSTEMTIME
; y Fecha los segundos a sumar al día cero   1/1/1970 
function TimeDataDescription,Fecha:DWORD,lpTimepoAux:QWORD
	begin_alloc
		alloc_var DiasAux:DWORD
	end_alloc
	
	; Establecemos el Tiempo 0
	invoke setmem, lpTimepoAux,sizeof SYSTEMTIME,0 
	
	
	mov rsi,lpTimepoAux
	mov [rsi].SYSTEMTIME.wYear,1970
	mov [rsi].SYSTEMTIME.wMonth,1
	mov [rsi].SYSTEMTIME.wDay,1
	
	
	; La idea es sumar los segundos (variable Fecha) e ir reajustando
	
	xor rax,rax
	mov ax,word ptr [rsi].SYSTEMTIME.wSecond
	add eax,Fecha
	
	mov rbx,60 ; segundos
	
	xor rdx,rdx
	idiv rbx
	
	; en edx los segundos
	mov [rsi].SYSTEMTIME.wSecond,dx
	
	xor rbx,rbx
	mov bx,[rsi].SYSTEMTIME.wMinute
	add rax,rbx  
	
	mov rbx,60 ; Minutos
	
	xor rdx,rdx
	idiv rbx
	
	; en edx los Minutos
	mov [rsi].SYSTEMTIME.wMinute,dx
	 
	xor rbx,rbx
	mov bx,[rsi].SYSTEMTIME.wHour
	add rax,rbx  
	 
	mov rbx,24 ; Horas
	
	xor rdx,rdx
	idiv rbx
	
	; en edx las Horas
	mov [rsi].SYSTEMTIME.wHour,dx
	 
	;*******   Esto es la parte complicada  días, meses y años, ver como hacer con los Años Bisiestos 
	
	mov DiasAux,eax
	
	; hacemos una aproximación sin considerar años bisiestos 
	
	xor rdx,rdx
	xor rbx,rbx
	mov ebx,365
	idiv ebx
	
	; en edx los días del Año, en EAX el número de años transcurrido
	
	@IF <<cmp rax,2>>,ABOVE?||EQUAL?
	
		push rax
		push rdx
		sub eax,2 ; el primer año bisiesto a tener en cuenta fue en el 1972 
		
		
		xor rdx,rdx
		mov rbx,4
		idiv ebx
		
		pop rdx  ; los días
		sub edx,eax
		pop rax ; el número de años 
		@IF <<cmp edx,0>>,LESS?
			; le quitamos un año 
			dec rax
			; pasamos los dias a positivo sumando 366 o 365 según el año sea bisiesto o no  
			push rax
			add rax,1970
			push rdx
			invoke EsAnnoBisiesto,rax
			pop rdx
			@IF <<cmp rax,TRUE>>,EQUAL?
				add edx,366
			@ELSE
				add edx,365
			@ENDIF
			pop rax
		@ENDIF
	@ENDIF
	
	mov rsi,lpTimepoAux
	add [rsi].SYSTEMTIME.wYear,ax
	
	; los días en rdx
	
	; se realizará un algoritmo de resta de días en función del més/año
	;inc rdx ;se parte incialmente del 1 del mes de enero
	
TimeDataDescription_otra:
	
	push rdx
	mov rsi,lpTimepoAux
	xor rbx,rbx
	xor rcx,rcx
	mov bx,[rsi].SYSTEMTIME.wMonth
	mov cx,[rsi].SYSTEMTIME.wYear
	invoke dias_mes,rbx ,rcx 
	pop rdx
	@IF <<cmp rax,NULL>>,NOEQUAL?
		mov rsi,lpTimepoAux
		@IF <<cmp rdx,rax>>,ABOVE?||EQUAL?
			sub rdx,rax
			
			mov ax,[rsi].SYSTEMTIME.wMonth
			inc rax
			mov [rsi].SYSTEMTIME.wMonth,ax
		
			jmp TimeDataDescription_otra
		@ENDIF

		mov [rsi].SYSTEMTIME.wDay,dx	
	@ENDIF
	
exitf

function EsAnnoBisiesto,Anno:QWORD
	
	
	mov rax,Anno
	xor rdx,rdx
	mov rbx,400
	idiv rbx
	
	@IF <<cmp rdx,0>>,EQUAL?
		return TRUE
	@ENDIF
	
	mov rax,Anno
	xor rdx,rdx
	mov rbx,4
	idiv rbx
	
	@IF <<cmp rdx,0>>,EQUAL?
		mov rax,Anno
		xor rdx,rdx
		mov rbx,100
		idiv rbx
		
		@IF <<cmp rdx,0>>,NOEQUAL?
			
			return TRUE
		@ENDIF
	@ENDIF
	
	return FALSE
	
exitf

function dias_mes,Mes:QWORD,Anno:QWORD


	mov rax,Mes
	@IF <<cmp rax,1>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,2>>,EQUAL?
		invoke EsAnnoBisiesto,Anno
		@IF <<cmp rax,TRUE>>,EQUAL?
			return 29
		@ELSE
			return 28
		@ENDIF
	
	@ELSEIF <<cmp rax,3>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,4>>,EQUAL?
		return 30
	@ELSEIF <<cmp rax,5>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,6>>,EQUAL?
		return 30
	@ELSEIF <<cmp rax,7>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,8>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,9>>,EQUAL?
		return 30
	@ELSEIF <<cmp rax,10>>,EQUAL?
		return 31
	@ELSEIF <<cmp rax,11>>,EQUAL?
		return 30
	@ELSEIF <<cmp rax,12>>,EQUAL?
		return 31
	@ELSE
		return NULL	
	@ENDIF
exitf


function TimeToTimeDateStamp,lpTime:QWORD
	
	mov rsi,lpTime
	xor rax,rax
	mov ax,[rsi].SYSTEMTIME.wYear
	
	push rax
	@IF << cmp ax, 1972>>,ABOVE?||EQUAL?
	
		; Cálculo de los días Bisiestos a sumar
		sub ax,1973
		xor rdx,rdx
		mov rbx,4
		idiv rbx
		mov rbx,rax
		
	@ELSE
		mov rbx,0
	
	@ENDIF
	pop rax
	sub rax,1970
	xor rdx,rdx
	mov rcx,365
	imul rax,rcx
	add rax,rbx  ; en rbx tenemos los días bisiestos
	
	; En rax tenemos los días correspondientes a años completos
	
	mov rsi,lpTime
	xor rbx,rbx
	xor rcx,rcx
	mov bx,[rsi].SYSTEMTIME.wDay
	
	add rax,rbx  ; Sumamos los días correspondientes al més en currso
	
	mov bx,[rsi].SYSTEMTIME.wMonth
	dec rbx
	mov cx,[rsi].SYSTEMTIME.wYear

TimeToTimeDateStamp_Dias_otra:	
	cmp rbx,0
	je TimeToTimeDateStamp_Dias_FIN
		push rcx ; año
		push rbx ; mes
		push rax ; cuenta
			
		invoke dias_mes,rbx ,rcx 
	
		pop rdx
		add rax,rdx
		
		pop rbx
		pop rcx
		dec rbx
		jmp TimeToTimeDateStamp_Dias_otra

TimeToTimeDateStamp_Dias_FIN:

	; Pasamos la cuenta de días a segundos
	xor rdx,rdx
	mov rbx, 86400 ;24 h * 3600 segundos
	imul rax,rbx 
	push rax
	; Sumamos el correspondiente a las Tiempo
	
	mov rsi,lpTime
	xor rbx,rbx
	xor rdx,rdx
	mov bx,[rsi].SYSTEMTIME.wHour
	mov rax,3600
	imul rax,rbx
	pop rdx
	add rax,rdx
	
	push rax
	
	mov rsi,lpTime
	xor rbx,rbx
	xor rdx,rdx
	mov bx,[rsi].SYSTEMTIME.wMinute
	mov rax,60
	imul rax,rbx
	pop rdx
	add rax,rdx
	
	xor rbx,rbx
	mov bx,[rsi].SYSTEMTIME.wSecond
	add rax,rbx
	
	return rax
	
exitf
ENDIF