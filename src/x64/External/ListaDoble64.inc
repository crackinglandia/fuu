; $Id: ListaDoble64.inc 61 2010-07-12 17:16:52Z nahuelriva $

NODOLISTADOBLE64 STRUCT
    LpItem      QWORD ?
    LpNextNode  QWORD ?
    LpPrevNode	QWORD ?
NODOLISTADOBLE64 ENDS

funcproto LOCAL,CrearListaDoble,QWORD
funcproto LOCAL,AnadirItemListaDoble,QWORD,QWORD,QWORD
funcproto LOCAL,BorrarItemListaDoble,QWORD,QWORD
funcproto LOCAL,RecuperarItemListaDoble,QWORD,QWORD,QWORD
funcproto LOCAL,ActualizarItemListaDoble,QWORD,QWORD,QWORD
funcproto LOCAL,BorrarListaDoble,QWORD
funcproto LOCAL,SiguienteNodoListaDoble,QWORD,QWORD
funcproto LOCAL,AnteriorNodoListaDoble,QWORD,QWORD
funcproto LOCAL,PrimerNodoListaDoble,QWORD
funcproto LOCAL,UltimoNodoListaDoble,QWORD
funcproto LOCAL,BuscarItemListaDoble,QWORD,QWORD,QWORD,QWORD
funcproto LOCAL,NumeroItemListaDoble,QWORD
funcproto LOCAL,IsListaDobleVacia,QWORD
funcproto LOCAL,VaciarListaDoble,QWORD
funcproto LOCAL,ItemPosByIndexListaDoble,QWORD,QWORD

funcproto LOCAL,ListaAFicheroListaDoble,QWORD,QWORD,DWORD
funcproto LOCAL,LoadListaFormFileListaDoble,QWORD,QWORD
funcproto LOCAL,OrdenarListaDoble,QWORD,QWORD,QWORD

szErrorFicheroExiste		db "Error. The File exists",0
szErrorFicheroNotOPen		db "It's not possible to create the file",0
szErrorReservandoMemoria	db "Error allocating memory",0

.code


; Crearlista debuelve en RAX la dirección de la lista 
; Recibe el tamaño de la estructura Item
function CrearListaDoble,ItemSize:QWORD
	
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,sizeof NODOLISTADOBLE64
	@IF <<cmp rax,0>>,NOEQUAL?
		
		mov [rax].NODOLISTADOBLE64.LpNextNode,rax
		mov [rax].NODOLISTADOBLE64.LpPrevNode,rax
		mov rcx,ItemSize
		mov [rax].NODOLISTADOBLE64.LpItem,rcx

	@ENDIF
	return rax
exitf

; Devuelve en eax 1 OK, 0,false
function AnadirItemListaDoble,Lista:QWORD, Item:QWORD, Pos:QWORD
	begin_alloc
		alloc_var lpNewNode:QWORD
		alloc_var lpItem:QWORD
	end_alloc

	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,sizeof NODOLISTADOBLE64
	@IF <<cmp rax,0>>,NOEQUAL?
		
		mov lpNewNode,rax
		mov rax,Lista
		@IF <<cmp rax,0>>,NOEQUAL?
		
			mov rdi,[rax].NODOLISTADOBLE64.LpItem ;Tamaño de ITEM
			
			push rdi
			
			invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edi
			pop rdi
			
			@IF <<cmp rax,0>>,NOEQUAL?
				mov lpItem,rax
				mov rax,lpNewNode
				mov rbx,Pos
				@IF <<cmp rbx,0>>,NOEQUAL?
			    		
			    	push rax ; q
			    	push rbx ; p
			    	invoke memcpy,lpItem,Item,rdi  
					pop rbx
					pop rax
						
					mov rcx,lpItem
					mov [rax].NODOLISTADOBLE64.LpItem,rcx  ; copia del Item
					mov rcx,[ebx].NODOLISTADOBLE64.LpNextNode ; rcx => p->sig
	
					mov [rax].NODOLISTADOBLE64.LpNextNode,rcx ; q->s = p->sig
					mov [rbx].NODOLISTADOBLE64.LpNextNode,rax ; p->sig = q
						
					mov rdx,[rax].NODOLISTADOBLE64.LpNextNode
					mov rcx,[rdx].NODOLISTADOBLE64.LpPrevNode ; rcx = q->sig->ant
					mov [rax].NODOLISTADOBLE64.LpPrevNode,rcx ; q->ant = q->sig->ant
					mov [rdx].NODOLISTADOBLE64.LpPrevNode,rax ; q->sig->ant = q

					mov rax,1
				@ELSE
					xor rax,rax
				@ENDIF
			@ENDIF
		@ENDIF
	@ENDIF
	return rax
exitf

;Borra un item de la lista
function BorrarItemListaDoble,Lista:QWORD,Pos:QWORD
	mov rsi,Pos
	@IF <<cmp rsi,0>>,NOEQUAL?
		
		invoke UltimoNodoListaDoble,Lista
		@IF <<cmp rax,rsi>>,NOEQUAL?
			mov rbx,Pos
			
			mov rsi,[rbx].NODOLISTADOBLE64.LpNextNode ;rsi = p->sig
			mov rax,[rsi].NODOLISTADOBLE64.LpNextNode ;rax = p->sig->sig
			mov [rbx].NODOLISTADOBLE64.LpNextNode,rax ; p->sig = p->sig->sig
			mov [rax].NODOLISTADOBLE64.LpPrevNode,rbx ;p->sig->ant = p
			
			mov rax,[rsi].NODOLISTADOBLE64.LpItem
; Se tiene que borrar antes la memoria reserbada al item.
			
			invoke LocalFree,rax
			
; Borramos la memoria reservada al tipo nodo 
			invoke LocalFree,rsi
			mov rax,1
		@ELSE
			xor rax,rax
		@ENDIF
	@ELSE
		xor rax,rax	
	@ENDIF
	return rax
exitf

; Devuelve en ITEM el Item leido de la lista
function RecuperarItemListaDoble,Lista:QWORD,Pos:QWORD,Item:QWORD
; Se tiene que acceder por puntero al elemento
	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		mov rax, Pos
		@IF <<cmp rax,0>>,EQUAL?
			xor rax,rax
		@ELSE
			invoke UltimoNodoListaDoble,Lista
			mov rsi,Pos
			@IF <<cmp rax,rsi>>,NOEQUAL?
				
				mov rax,Lista
				mov rsi,[rax].NODOLISTADOBLE64.LpItem ;tamaño de la estructura item
				mov rbx,Pos
				mov rcx,[rbx].NODOLISTADOBLE64.LpNextNode
				mov rax,[rcx].NODOLISTADOBLE64.LpItem
				
				invoke memcpy,Item,rax,rsi
				
				mov rax,1
			@ELSE
				xor rax,rax
			@ENDIF		
		@ENDIF
	@ELSE
		xor rax,rax
	@ENDIF
	
	return rax
exitf

function ActualizarItemListaDoble,Lista:QWORD,Pos:QWORD,Item:QWORD
	
; Se tiene que acceder por puntero al elemento
	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		invoke UltimoNodoListaDoble,Lista
		mov rsi,Pos
		@IF <<cmp rax,rsi>>,NOEQUAL?
	
			mov rax, Lista
			mov rsi,[rax].NODOLISTADOBLE64.LpItem ;tamaño de la estructura item
			
			mov rbx,Pos
			
			mov rcx,[rbx].NODOLISTADOBLE64.LpNextNode
			mov rax,[rcx].NODOLISTADOBLE64.LpItem

			invoke memcpy,rax,Item,rsi
			mov rax,1 		
		@ELSE
			xor rax,rax		
		@ENDIF
	@ENDIF
	
	return rax
exitf

; Borra la lista completa
function BorrarListaDoble,Lista:QWORD
	
Borrar_Lista_otra:
	mov rbx,Lista
	
	mov rax,[rbx].NODOLISTADOBLE64.LpNextNode
	
	cmp rax,rbx ;la condición de fin es cuando p->sig= p
	je Borrar_Lista_FIN
		invoke BorrarItemListaDoble,Lista,rbx ; con esto se borra el 1º NODO con datos y se reajustan los enlacex 
	jmp Borrar_Lista_otra	
			
	
Borrar_Lista_FIN:	
	invoke LocalFree,rbx ;Borramos el nodo cabecera
exitf

; En rax la dirección de siguiente
function SiguienteNodoListaDoble,Lista:QWORD,Pos:QWORD
	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		invoke UltimoNodoListaDoble,Lista
		mov rsi,Pos
		@IF <<cmp rax,rsi>>,NOEQUAL?
		
			mov rbx,Pos
			mov rax,[rbx].NODOLISTADOBLE64.LpNextNode
		@ELSE
			xor rax,rax
		@ENDIF
	@ENDIF
	return rax
exitf

; En rax la direccion del anterior
function AnteriorNodoListaDoble,Lista:QWORD,Pos:QWORD
	
	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		mov rbx,Pos
		@IF <<cmp rbx,rax>>,NOEQUAL?
  			mov rax,[rbx].NODOLISTADOBLE64.LpPrevNode
		@ELSE
			xor rax,rax
		@ENDIF
	@ENDIF
	return rax
exitf

; En eax la dirección del 1º elemento de la lista
function PrimerNodoListaDoble,Lista:QWORD
	mov rax,Lista
	return rax
exitf

; En eax la dirección del ultimo elemento de la lista
function UltimoNodoListaDoble,Lista:QWORD
	mov rbx,Lista
	mov rax,[rbx].NODOLISTADOBLE64.LpPrevNode
	return rax
exitf

; Búsqueda de un ITEM
; ITEM: puntero a una estructura ITEM que se quiere buscar en la lista
; PosInit: Posicion incial de busqueda en la lista NULL => empezar por el 1º Elemento
; Fun: Dirección a una funcion callback para la comparación si es NULL se comprueba el bloque completo de memoria
;      Si existe la funcion devolvera 1 en eax si se ha encontrado
;      Estrucutura de la funcion:
;            PROC lpItem:DWORD,lpItemTmp:DWORD,ItemSize:DWORD
 
; La funcion Busqueda de ITEM devolvera NULL si no encuentra el ITEM, o la posicion en la lista del ITEM

function BuscarItemListaDoble,Lista:QWORD,Item:QWORD,PosInit:QWORD,Fun:QWORD

	begin_alloc 
		alloc_var PosLista:QWORD
		alloc_var FunCall:QWORD
		alloc_var lpItemTmp:QWORD ; Reservar memoria para este ITEM
		alloc_var ItemSize:QWORD 
	end_alloc
	
	mov Rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL? 

		invoke IsListaDobleVacia,Lista
		@IF <<cmp rax,0>>,EQUAL? 
			invoke UltimoNodoListaDoble,Lista
			mov rsi,PosInit
			@IF <<cmp rax,rsi>>,NOEQUAL?
			
				mov rax,Lista
				mov rax,[rax].NODOLISTADOBLE64.LpItem
				mov ItemSize,rax
				
				invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,ItemSize
				mov lpItemTmp,rax
					
				mov rax,PosInit
				@IF <<cmp rax,0>>,EQUAL?
					invoke PrimerNodoListaDoble,Lista
				@ENDIF
				mov PosLista,rax		
	
				mov rax,Fun
				@IF <<cmp rax,0>>,EQUAL?
					xor rax,rax
					mov FunCall,rax 
				@ELSE
					mov rax,1
					mov FunCall,rax
				@ENDIF
		
		
BuscarItemLista_otro:
				invoke RecuperarItemListaDoble,Lista,PosLista,lpItemTmp
				@IF <<cmp rax,0>>,NOEQUAL?
				
					mov rax,FunCall
					@IF <<cmp rax,1>>,EQUAL?
;Comprobación del usuario			
						@AjustePila
			     		; reservamos la memoria en la pila 
     					sub rsp,8*4  ; Con esta suma la pila sigue alineada
     	
			     		;arg 1
			     		mov rcx,Item
			     		;arg 2
			     		mov rdx,lpItemTmp
						;arg 3
						mov r8, ItemSize
			  		   	
			  		   	; llamada a la función
    			 		mov rax,Fun
     					call rax
     					
		    	 		; liberamos la memoria
     					add rsp,8*4
						; Reajustamos la pila 
     					@ReAjustePila
					
					@ELSE
;Comprobación del bloque completo de la estructura ITEM
		 				invoke memcpm,Item, lpItemTmp,ItemSize
					@ENDIF

					@IF <<cmp rax,0>>,EQUAL? ; Busca otro
						invoke SiguienteNodoListaDoble,Lista,PosLista
						@IF <<cmp rax,0>>,NOEQUAL?
							mov PosLista,rax
							jmp BuscarItemLista_otro
						@ENDIF 
					@ELSE
						mov rax,PosLista 
					@ENDIF
				@ELSE
				 	xor rax,rax
				@ENDIF
			@ELSE
				xor rax,rax
			@ENDIF
		@ELSE
			xor rax,rax
		@ENDIF
	@ENDIF
	return rax
exitf

function NumeroItemListaDoble,Lista:QWORD 
	begin_alloc
		alloc_var PosP:QWORD
		alloc_var PosF:QWORD
		alloc_var contItem:QWORD
	end_alloc
	
	xor rax,rax	
	mov contItem,rax ;0
	
	invoke PrimerNodoListaDoble,Lista  ; Si Lista es NULL la función devuelve 0
	mov PosP,rax
	invoke UltimoNodoListaDoble,Lista  ; Si Lista es NULL la función devuelve 0
	mov PosF,rax

NumeroItemLista_otro:
	mov rax,PosP
	mov rbx,PosF
	cmp rax,rbx                       ; SI lista es NULL rax == rbx = 0 => salta y devuelve 0
	je  NumeroItemLista_FIN
	
		invoke SiguienteNodoListaDoble,Lista,PosP
		mov rsi,contItem
		inc rsi
		mov contItem,rsi
		mov PosP,rax
		jmp NumeroItemLista_otro

NumeroItemLista_FIN:	
	mov rax,contItem
	return rax
exitf


function IsListaDobleVacia,Lista:QWORD

	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		
		mov rbx,[rax].NODOLISTADOBLE64.LpNextNode
		mov rsi,[rax].NODOLISTADOBLE64.LpPrevNode
		@IF <<cmp rbx,rsi>>,EQUAL?
			mov rax,1
		@ELSE
			xor rax,rax
		@ENDIF
	@ENDIF
	return rax	
exitf

function VaciarListaDoble,Lista:QWORD
	begin_alloc
		alloc_var Pos:QWORD
		alloc_var PosUlt:QWORD 
	end_alloc
	
	mov rax,Lista
	@IF <<cmp rax,0>>,NOEQUAL?
		invoke PrimerNodoListaDoble,Lista
		mov Pos,rax
	
VaciarListaDoble_otro:	

		invoke UltimoNodoListaDoble,Lista

		cmp rax,Pos
		je VaciarListaDoble_FIN
		
			invoke BorrarItemListaDoble,Lista,Pos
			jmp VaciarListaDoble_otro

VaciarListaDoble_FIN:
	@ENDIF
	
exitf

;****************************************************
; Retorna la posició del Item indicado por Index, 
; o NULL si no se encontró
;****************************************************
function ItemPosByIndexListaDoble,Lista:QWORD,Index:QWORD
	begin_alloc
		alloc_var Pos:QWORD
		alloc_var PosUlt:QWORD
		 
	end_alloc
	
	mov rsi,Lista
	@IF <<cmp rsi,0>>,NOEQUAL?

		invoke PrimerNodoListaDoble,Lista
		mov Pos,rax
		invoke UltimoNodoListaDoble,Lista
		mov PosUlt,rax
		
		xor rcx,rcx
ItemPosByIndexListaDoble_otro:
		
		cmp rcx,Index
		je ItemPosByIndexListaDoble_FIN
		mov rbx,Pos
		cmp rbx,PosUlt
		je ItemPosByIndexListaDoble_Err
			push rcx
			
			invoke SiguienteNodoListaDoble,Lista,Pos
			mov Pos,rax
			pop rcx
			inc rcx
			jmp ItemPosByIndexListaDoble_otro
ItemPosByIndexListaDoble_FIN:
		mov rax,Pos
		
	@ELSE
ItemPosByIndexListaDoble_Err:
		xor rax,rax		
	@ENDIF
	
	return rax
exitf

function ListaAFicheroListaDoble, Lista:QWORD,lpFile:QWORD,SobreEscribir:DWORD
	begin_alloc
		alloc_var HFile:QWORD
		alloc_var Pos:QWORD
		alloc_var PosUlt:QWORD
		alloc_var Tam:DWORD
		alloc_var lpItem:QWORD
		alloc_var WrittenByte:DWORD
		
	end_alloc
	
	mov rax,lpFile
	@IF << cmp rax, 0>>,NOEQUAL?
		mov rax,Lista
		@IF <<cmp rax,0>>,NOEQUAL?
			mov eax,SobreEscribir
			@IF <<cmp eax,0>>,NOEQUAL?

				invoke CreateFile,lpFile,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL	
				@IF<<cmp rax, INVALID_HANDLE_VALUE>>,EQUAL?
					invoke MessageBox,NULL,addr szErrorFicheroNotOPen,NULL,MB_OK or MB_ICONERROR
				
					return NULL
				
				@ENDIF

			
			@ELSE
			
				invoke CreateFile,lpFile,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE,NULL
				@IF <<cmp rax,INVALID_HANDLE_VALUE>>,EQUAL?
					invoke MessageBox,NULL,addr szErrorFicheroExiste,NULL,MB_OK or MB_ICONERROR
				
					return NULL
				@ENDIF
			@ENDIF
			
			mov HFile,rax	
		
			; Tomamos el tamaño del elemento	
			mov rsi,Lista
			mov rax,[rsi].NODOLISTADOBLE64.LpItem
			mov Tam,eax
			
			invoke LocalAlloc,LMEM_ZEROINIT or LMEM_FIXED, Tam
		
			mov lpItem,rax
			@IF <<cmp rax,0>>,EQUAL?
				invoke MessageBox,NULL,addr szErrorReservandoMemoria,NULL,MB_OK or MB_ICONERROR
				invoke CloseHandle,HFile
				return NULL
			@ENDIF

			invoke PrimerNodoListaDoble,Lista
			mov Pos,rax
			invoke UltimoNodoListaDoble,Lista
			mov PosUlt,rax
			
ListaAFicheroListaDoble_otro:
			mov rax,Pos
			cmp rax,PosUlt
			je ListaAFicheroListaDoble_FIN
		
				invoke RecuperarItemListaDoble,Lista,Pos,lpItem
			
				invoke WriteFile,HFile,lpItem,Tam,addr WrittenByte,NULL
		
				invoke SiguienteNodoListaDoble,Lista,Pos
				mov Pos,rax
				jmp ListaAFicheroListaDoble_otro
ListaAFicheroListaDoble_FIN:

			invoke CloseHandle,HFile
			invoke LocalFree,lpItem
			return TRUE
		
		@ELSE
			return FALSE	
		@ENDIF
	@ELSE
		return FALSE
	@ENDIF
exitf

function LoadListaFormFileListaDoble,Lista:QWORD,lpFile:QWORD
	begin_alloc
		alloc_var HFile:QWORD
		alloc_var LocalBuff:QWORD
		alloc_var Pos:QWORD
		alloc_var BytesRead:DWORD
		alloc_var ItemSize:DWORD
	end_alloc

	mov rax,Lista
	@IF <<cmp rax,0>>,EQUAL?
		return NULL
	@ENDIF
	
	; obtenemos el tamaño del ITEM
	mov rax,Lista
	mov rdx, [rax].NODOLISTADOBLE64.LpItem
	mov ItemSize,edx

	;1º Abrimos el Fichero 
	invoke CreateFile,lpFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
	@IF <<cmp rax, INVALID_HANDLE_VALUE>>,EQUAL?
		return NULL
	@ENDIF
	mov HFile,rax		
	
	
	;3º Pedimos memoria para el buffer auxiliar
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,ItemSize
	mov LocalBuff,rax
	@IF <<cmp rax,0>>,EQUAL?
		invoke CloseHandle,HFile
		return NULL
	@ENDIF
	;3 Guardamos el recurso en la lista
LoadListaFile_otroItem:
	invoke UltimoNodoListaDoble,Lista
	mov Pos,rax

	invoke ReadFile,HFile,LocalBuff,ItemSize,addr BytesRead,NULL
	mov eax,BytesRead
	@IF <<cmp eax,0>>,ABOVE?
		invoke AnadirItemListaDoble,Lista,LocalBuff,Pos
		jmp LoadListaFile_otroItem
	@ENDIF
	invoke CloseHandle,HFile
	;4 Borramos el buffer
	invoke LocalFree,LocalBuff
	return TRUE
exitf

;**********************************************************************
;    DirOrd: Indica el orden de ordenación 0 menor a mayor
;                                          1 mayor a menor
;   Fun: Puntero a función CALLBACK que tiene el siguente prototipo
;                 PROC lpItme1:QWORD, lpItem2:QWORD
;
;        Debe de retornar:   0: Igual
;                            1: Item1 > Item2
;                           -1: Item1 < Item2
;**********************************************************************                                          
function OrdenarListaDoble,Lista:QWORD,DirOrd:QWORD,Fun:QWORD
	begin_alloc
		alloc_var Pos1:QWORD
		alloc_var Pos2:QWORD
		alloc_var PosAux:QWORD
		alloc_var PosUlt:QWORD
		alloc_var PosPri:QWORD
		alloc_var pItem1:QWORD
		alloc_var pItem2:QWORD
		    
	end_alloc

	mov rax,Lista
	@IF <<cmp rax,0>>,EQUAL?
		return NULL
	@ENDIF
	
	mov rax,Fun
	@IF <<cmp rax,0>>,EQUAL?
		return NULL
	@ENDIF
	
	
	invoke UltimoNodoListaDoble,Lista
	mov PosUlt,rax
	
	invoke PrimerNodoListaDoble,Lista
	mov PosPri,rax
	
	cmp rax,PosUlt   ;Comprobación de Lista Vacia
	je OrdenarLista_FIN

		; Pedimos memoria para los Items
		mov rax,Lista
		mov rdx,[rax].NODOLISTADOBLE64.LpItem ; tamaño del ITEM
		
			
		push rdx
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
		mov pItem1,rax
			
		pop rdx
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
		mov pItem2,rax

		
		invoke SiguienteNodoListaDoble,Lista,PosPri
		mov Pos1,rax

OrdenarLista_siguiente:		
		cmp rax,PosUlt
		je OrdenarLista_FIN
			
			mov rax,Pos1
			mov Pos2,rax

			
OrdenarLista_SigueCambiando:
			invoke AnteriorNodoListaDoble,Lista,Pos2
			mov PosAux,rax
		
 
			invoke RecuperarItemListaDoble,Lista,Pos2,pItem1 
			invoke RecuperarItemListaDoble,Lista,PosAux,pItem2
			;***************
			
			@AjustePila
			sub rsp,8*4  
     	
			;arg 1
			mov rcx,pItem1
			;arg 2
			mov rdx,pItem2
			
			mov rax,Fun
			call rax
			add rsp,8*4
			@ReAjustePila
			
			
			; junto con el valor de EAX y DirOrd se comprueba si se cambia o no 
			cmp rax,0
			je OrdenarLista_Otro_dato
				
			mov rbx,DirOrd
			cmp rbx,0
			je 	OrdenarLista_Des			

				; Comprobamos si ascendente
				cmp rax,1
				jne OrdenarLista_Otro_dato
				jmp OrdenarLista_Cambia
				
OrdenarLista_Des:
			
			cmp rax,-1
			jne OrdenarLista_Otro_dato 

OrdenarLista_Cambia:
			;-------------------- Cambio en los datos
			
			mov rax,Pos2
			mov rbx,PosAux

				mov rax,[rax].NODOLISTADOBLE64.LpNextNode
				mov rbx,[rbx].NODOLISTADOBLE64.LpNextNode

				mov rsi,[rax].NODOLISTADOBLE64.LpItem
				mov rdi,[rbx].NODOLISTADOBLE64.LpItem
				mov [rax].NODOLISTADOBLE64.LpItem,rdi
				mov [rbx].NODOLISTADOBLE64.LpItem,rsi
			
			;-------------------- Seguimos comprobando  
			mov rax,PosAux
			cmp rax,PosPri
			je OrdenarLista_Otro_dato ; Fin de la comprobación
			
			mov Pos2,rax
			jmp OrdenarLista_SigueCambiando
		
OrdenarLista_Otro_dato:
			
		invoke SiguienteNodoListaDoble,Lista,Pos1
		mov Pos1,rax
		jmp OrdenarLista_siguiente
	
OrdenarLista_FIN:
	
exitf