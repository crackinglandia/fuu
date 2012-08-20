NODOLISTADOBLE STRUCT
    LpItem      DWORD ?
    LpNextNode  DWORD ?
    LpPrevNode	DWORD ?
NODOLISTADOBLE ENDS

CrearListaDoble 				PROTO :DWORD
AnadirItemListaDoble	 		PROTO :DWORD,:DWORD,:DWORD
BorrarItemListaDoble	 		PROTO :DWORD,:DWORD
RecuperarItemListaDoble			PROTO :DWORD,:DWORD,:DWORD
BorrarListaDoble	 			PROTO :DWORD
SiguienteNodoListaDoble 		PROTO :DWORD,:DWORD
AnteriorNodoListaDoble	 		PROTO :DWORD,:DWORD
PrimerNodoListaDoble	 		PROTO :DWORD
UltimoNodoListaDoble	 		PROTO :DWORD
BuscarItemListaDoble	 		PROTO :DWORD,:DWORD,:DWORD,:DWORD
NumeroItemListaDoble	 		PROTO :DWORD
ActualizarItemListaDoble	 	PROTO :DWORD,:DWORD,:DWORD
IsListaDobleVacia				PROTO :DWORD
VaciarListaDoble 				PROTO :DWORD
ItemPosByIndexListaDoble 		proto :DWORD,:DWORD

ListaAFicheroListaDoble 		PROto :DWORD,:DWORD,:DWORD
LoadListaFormFileListaDoble 	PROto :DWORD,:DWORD

OrdenarListaDoble 				proto :DWORD,:DWORD,:DWORD

.data

szErrorFicheroExiste		db "Error. The File exists",0
szErrorFicheroNotOPen		db "It's not possible to create the file",0
szErrorReservandoMemoria	db "Error allocating memory",0

.code


;Crearlista debuelve en EAX la dirección de la lista 
; Recibe el tamaño de la estructura Item
CrearListaDoble PROC ItemSize:DWORD
	
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,sizeof NODOLISTADOBLE
	.if eax != 0
		assume eax: ptr NODOLISTADOBLE
        	mov [eax].LpNextNode,eax
        	mov [eax].LpPrevNode,eax
        	mov ecx,ItemSize
        	mov [eax].LpItem,ecx ; el elemento 0 tiene el tamaño de la estructura Item
        assume eax:NOTHING
	.endif

	ret

CrearListaDoble endp
; Debuelve en eax 1 OK, 0,false
AnadirItemListaDoble PROC Lista:DWORD, Item:DWORD, Pos:DWORD
	LOCAL lpNewNode:DWORD
	LOCAL lpItem:DWORD

	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,sizeof NODOLISTADOBLE
	.if eax != 0
		mov lpNewNode,eax
		mov eax,Lista
		.if eax !=0
			assume eax: ptr NODOLISTADOBLE
				mov edx,[eax].LpItem ;Tamaño de ITEM
			assume eax:NOTHING
			push edx
			invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
			pop edx
			.if eax != 0
				mov lpItem,eax
				mov eax,lpNewNode
				mov ebx,Pos
				.if ebx !=0
					assume eax: ptr NODOLISTADOBLE ; q
					assume ebx: ptr NODOLISTADOBLE ; p
			    		push eax
			    		push ebx
			    		invoke memcpy,lpItem,Item,edx  
						pop ebx
						pop eax
						
						mov ecx,lpItem
						mov [eax].LpItem,ecx  ; copia del Item

						mov ecx,[ebx].LpNextNode ; ecx => p->sig
						mov [eax].LpNextNode,ecx ; q->s = p->sig
						mov [ebx].LpNextNode,eax ; p->sig = q
						
						mov edx,[eax].LpNextNode
						assume edx: ptr NODOLISTADOBLE
							mov ecx,[edx].LpPrevNode ; ecx = q->sig->ant
							mov [eax].LpPrevNode,ecx ; q->ant = q->sig->ant
							mov [edx].LpPrevNode,eax ; q->sig->ant = q
						assume edx:NOTHING
        			assume ebx:NOTHING
        			assume eax:NOTHING

					mov eax,1
				.else
					invoke LocalFree,lpItem
					invoke LocalFree,lpNewNode
					mov eax,0
				.endif
			.else
				invoke LocalFree,lpNewNode
				xor eax,eax
				
			.endif
		.else
			invoke LocalFree,lpNewNode
			xor eax,eax
		.endif
	.endif

	ret

AnadirItemListaDoble endp
;Borra un item de la lista
BorrarItemListaDoble PROC Lista:DWORD, Pos:DWORD
	
	.if Lista != NULL
		invoke UltimoNodoListaDoble,Lista
		.if ((eax != Pos) && (Pos != 0))
			mov ebx,Pos
			assume ebx: ptr NODOLISTADOBLE
				mov ecx,[ebx].LpNextNode ;ecx = p->sig
				assume ecx: ptr NODOLISTADOBLE
					mov eax,[ecx].LpNextNode ; eax = p->sig->sig
					mov [ebx].LpNextNode,eax ; p->sig = p->sig->sig
					assume eax: ptr NODOLISTADOBLE
						mov [eax].LpPrevNode,ebx ;p->sig->ant = p
					assume eax:NOTHING
						
					mov eax,[ecx].LpItem
				assume ecx:NOTHING
			assume ebx:NOTHING
; Se tiene que borrar antes la memoria reserbada al item.
			push ecx
			invoke LocalFree,eax
			pop ecx
; Borramos la memoria reservada al tipo nodo 
			invoke LocalFree,ecx
			mov eax,1
		.else
			xor eax,eax	
		.endif
	.endif
ret
BorrarItemListaDoble endp

; Debuelve en ITEM el Item leido de la lista
RecuperarItemListaDoble PROC Lista:DWORD,Pos:DWORD, Item:DWORD
; Se tiene que acceder por puntero al elemento
	mov eax,Lista
	.if  eax != 0
		mov eax, Pos
		.if eax == 0
			xor eax,eax
		.else
			invoke UltimoNodoListaDoble,Lista
			.if eax != Pos
				mov eax, Lista
				.if eax != 0 
					assume eax: ptr NODOLISTADOBLE
						mov edx,[eax].LpItem ;tamaño de la estructura item
					assume eax:NOTHING
			
					mov ebx,Pos
					assume ebx: ptr NODOLISTADOBLE
						mov ecx,[ebx].LpNextNode
						assume ecx: ptr NODOLISTADOBLE
							mov eax,[ecx].LpItem
							invoke memcpy,Item,eax,edx
							mov eax,1 		
						assume ecx:NOTHING
					assume ebx:NOTHING
				.endif
			.else
				xor eax,eax
			.endif		
		.endif
	.else
		xor eax,eax
	.endif
	
	ret
RecuperarItemListaDoble endp

ActualizarItemListaDoble PROC Lista:DWORD,Pos:DWORD,Item:DWORD
	
	.if Lista != NULL
; Se tiene que acceder por puntero al elemento
		invoke UltimoNodoListaDoble,Lista
		.if eax != Pos
			mov eax, Lista
			.if eax != 0 
				assume eax: ptr NODOLISTADOBLE
					mov edx,[eax].LpItem ;tamaño de la estructura item
				assume eax:NOTHING
			
				mov ebx,Pos
				assume ebx: ptr NODOLISTADOBLE
					mov ecx,[ebx].LpNextNode
					assume ecx: ptr NODOLISTADOBLE
						mov eax,[ecx].LpItem
						invoke memcpy,eax,Item,edx
						mov eax,1 		
					assume ecx:NOTHING
				assume ebx:NOTHING
			.endif
	
		.else
			xor eax,eax		
		.endif
	.endif
	ret

ActualizarItemListaDoble endp

; Borra la lista completa
BorrarListaDoble PROC Lista:DWORD
	LOCAL PosIni:DWORD
	.if Lista != NULL	
		invoke PrimerNodoListaDoble,Lista
		mov PosIni,eax

Borrar_Lista_otra:	
		invoke UltimoNodoListaDoble,Lista
	
		.if  eax != PosIni
			invoke BorrarItemListaDoble,Lista,PosIni
			jmp Borrar_Lista_otra
		.else
	
			invoke LocalFree,Lista
		.endif
	.endif
	ret
BorrarListaDoble endp
; En eax la dirección de siguiente
SiguienteNodoListaDoble PROC Lista:DWORD, Pos:DWORD
	
	.if Lista != NULL
		invoke UltimoNodoListaDoble,Lista
		.if eax != Pos
			push ebx
	
			mov ebx,Pos
			assume ebx: ptr NODOLISTADOBLE 
				mov eax,[ebx].LpNextNode
			assume ebx:NOTHING
			pop ebx
		
		.else
			xor eax,eax
		.endif
	.else
		xor eax,eax
	.endif	
	ret

SiguienteNodoListaDoble endp
; En eax la direccion del anterior
AnteriorNodoListaDoble PROC Lista:DWORD, Pos:DWORD
	
	push ebx
	.if Lista != NULL
		mov ebx,Pos ; ebx has to take the value of Pos not Lista
		.if Lista != ebx   ; Changed Pos for Lista due to the change of ebx value.
		
Anterior_otro:
			assume ebx: ptr NODOLISTADOBLE 
				mov eax,[ebx].LpPrevNode
			assume ebx:NOTHING
		
		.else
			xor eax,eax
		.endif
	.else
		xor eax,eax
	.endif
	pop ebx
	ret

AnteriorNodoListaDoble endp
; En eax la dirección del 1º elemento de la lista
PrimerNodoListaDoble PROC Lista: DWORD
	
	mov eax,Lista
	ret

PrimerNodoListaDoble endp
; En eax la dirección del ultimo elemento de la lista
UltimoNodoListaDoble PROC Lista:DWORD
	push ebx
	.if Lista !=  NULL
		mov ebx,Lista
Ultimo_lista_next:
		assume ebx: ptr NODOLISTADOBLE 
			mov eax,[ebx].LpPrevNode
		assume ebx:NOTHING

	.endif
	pop ebx
	ret

UltimoNodoListaDoble endp
; Búsqueda de un ITEM
; ITEM: puntero a una estructura ITEM que se quiere buscar en la lista
; PosInit: Posicion incial de busqueda en la lista NULL => empezar por el 1º Elemento
; Fun: Dirección a una funcion callback para la comparación si es NULL se comprueba el bloque completo de memoria
;      Si existe la funcion devolvera 1 en eax si se ha encontrado
;      Estrucutura de la funcion:
;            PROC lpItem:DWORD,lpItemTmp:DWORD,ItemSize:DWORD
 
; La funcion Busqueda de ITEM devolvera NULL si no encuentra el ITEM, o la posicion en la lista del ITEM

BuscarItemListaDoble PROC Lista:DWORD, Item:DWORD, PosInit:DWORD, Fun:DWORD
	LOCAL PosLista:DWORD
	LOCAL FunCall:DWORD
	LOCAL lpItemTmp:DWORD ; Reservar memoria para este ITEM
	LOCAL ItemSize:DWORD
	
	mov eax,Lista
	.if eax !=0 

		invoke IsListaDobleVacia,Lista
		.if eax == 0 
			invoke UltimoNodoListaDoble,Lista
			.if eax != PosInit
				mov eax,Lista
				assume eax: ptr NODOLISTADOBLE
					mov eax,[eax].LpItem
					mov ItemSize,eax
				assume eax:NOTHING
				invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,ItemSize
				mov lpItemTmp,eax
					
				mov eax,PosInit
				.if eax == 0
					invoke PrimerNodoListaDoble,Lista
				.endif
				mov PosLista,eax		
	
				mov eax,Fun
				.if eax == 0
					mov FunCall,0 
				.else
					mov FunCall,1
				.endif	
		
		
BuscarItemLista_otro:
				invoke RecuperarItemListaDoble,Lista,PosLista,lpItemTmp
				.if eax != 0
					.if FunCall == 1
;Comprobación del usuario			
						push ItemSize
						push lpItemTmp
						push Item
						call Fun
					.else
;Comprobación del bloque completo de la estructura ITEM
		 				invoke memcpm,Item, lpItemTmp,ItemSize
					.endif

					.if eax == 0 ; Busca otro
						invoke SiguienteNodoListaDoble,Lista,PosLista
						.if eax != 0
							mov PosLista,eax
							jmp BuscarItemLista_otro
						.endif 
					.else
						invoke LocalFree,lpItemTmp
						mov eax,PosLista 
					.endif
				 .else
					invoke LocalFree,lpItemTmp
				 	xor eax,eax
				 .endif
			.else
				xor eax,eax
			.endif
		.else
			xor eax,eax
		.endif
	.else
		xor eax,eax
	.endif
	
	ret
BuscarItemListaDoble endp

NumeroItemListaDoble PROC Lista:DWORD 
	
	LOCAL PosF:DWORD
	LOCAL PosP:DWORD
	LOCAL contItem:DWORD
	
	mov contItem,0
	.if Lista != NULL
		
	
		invoke PrimerNodoListaDoble,Lista
		mov PosP,eax
		invoke UltimoNodoListaDoble,Lista
		mov PosF,eax

NumeroItemLista_otro:
	
		mov eax,PosP
		.if eax != PosF
			invoke SiguienteNodoListaDoble,Lista,PosP
			inc contItem
			mov PosP,eax
			jmp NumeroItemLista_otro
		.endif
	.endif
	
	mov eax,contItem
	ret

NumeroItemListaDoble endp


IsListaDobleVacia PROC Lista:DWORD

	.if Lista != NULL
		mov esi,Lista
		.if esi !=NULL
			assume esi: ptr NODOLISTADOBLE
				mov eax,[esi].LpNextNode
				mov ebx,[esi].LpPrevNode
			assume esi:NOTHING
	
			.if eax == esi
				mov eax,1
			.else 
				xor eax,eax
			.endif
		.else
			xor eax,eax
		.endif	
	.endif
ret
IsListaDobleVacia endp

;****************************************************
; Retorna la posició del Item indicado por Index, 
; o NULL si no se encontró
;****************************************************
ItemPosByIndexListaDoble proc Lista:DWORD,Index:DWORD
	LOCAL Pos:DWORD
	LOCAL PosUlt:DWORD
	
	mov esi,Lista
	.if esi != NULL
		invoke PrimerNodoListaDoble,Lista
		mov Pos,eax
		invoke UltimoNodoListaDoble,Lista
		mov PosUlt,eax
		
		xor ecx,ecx
ItemPosByIndexListaDoble_otro:
		
		cmp ecx,Index
		je ItemPosByIndexListaDoble_FIN
		mov ebx,Pos
		cmp ebx,PosUlt
		je ItemPosByIndexListaDoble_Err
			push ecx
			
			invoke SiguienteNodoListaDoble,Lista,Pos
			mov Pos,eax
			pop ecx
			inc ecx
			jmp ItemPosByIndexListaDoble_otro
ItemPosByIndexListaDoble_FIN:
		mov eax,Pos
		
	.else
ItemPosByIndexListaDoble_Err:
		xor eax,eax		
	.endif
	ret

ItemPosByIndexListaDoble endp

VaciarListaDoble PROC Lista:DWORD
	LOCAL Pos:DWORD
	LOCAL PosUlt:DWORD
	
	.if Lista != NULL
		invoke PrimerNodoListaDoble,Lista
		mov Pos,eax
	
VaciarListaDoble_otro:	

		invoke UltimoNodoListaDoble,Lista

		cmp eax,Pos
		je VaciarListaDoble_FIN
		
			invoke BorrarItemListaDoble,Lista,Pos
			jmp VaciarListaDoble_otro

VaciarListaDoble_FIN:
	.endif
	
	ret

VaciarListaDoble endp

ListaAFicheroListaDoble PROC Lista:DWORD,lpFile:DWORD,SobreEscribir:DWORD
	LOCAL HFile:DWORD
	LOCAL Pos:DWORD
	LOCAL PosUlt:DWORD
	LOCAL Tam:DWORD
	LOCAL lpItem:DWORD
	LOCAL WrittenByte:DWORD
	
	.if lpFile != NULL && Lista != NULL
		
		.if SobreEscribir != NULL
			invoke CreateFile,lpFile,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL	
			.if eax ==  INVALID_HANDLE_VALUE
				invoke MessageBox,NULL,addr szErrorFicheroNotOPen,NULL,MB_OK or MB_ICONERROR
				
				xor eax,eax
				ret
			.endif
		.else
			invoke CreateFile,lpFile,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE,NULL
			.if eax ==  INVALID_HANDLE_VALUE
				invoke MessageBox,NULL,addr szErrorFicheroExiste,NULL,MB_OK or MB_ICONERROR
				
				xor eax,eax
				ret
			.endif
		.endif
		
		mov HFile,eax
		
		; Tomamos el tamaño del elemento
		mov esi,Lista
		assume esi: ptr NODOLISTADOBLE
			mov eax,[esi].LpItem
			mov Tam,eax
		assume esi:NOTHING
		
		invoke LocalAlloc,LMEM_ZEROINIT or LMEM_FIXED, Tam
		mov lpItem,eax
		.if eax == 0
			invoke MessageBox,NULL,addr szErrorReservandoMemoria,NULL,MB_OK or MB_ICONERROR
			invoke CloseHandle,HFile
			xor eax,eax
			ret
		.endif
		invoke PrimerNodoListaDoble,Lista
		mov Pos,eax
		invoke UltimoNodoListaDoble,Lista
		mov PosUlt,eax
		
ListaAFicheroListaDoble_otro:
		mov eax,Pos
		cmp eax,PosUlt
		je ListaAFicheroListaDoble_FIN
		
			invoke RecuperarItemListaDoble,Lista,Pos,lpItem
			
			invoke WriteFile,HFile,lpItem,Tam,addr WrittenByte,NULL
		
			invoke SiguienteNodoListaDoble,Lista,Pos
			mov Pos,eax
			jmp ListaAFicheroListaDoble_otro
ListaAFicheroListaDoble_FIN:

		invoke CloseHandle,HFile
		invoke LocalFree,lpItem
		mov eax,TRUE
	.else
		mov eax,FALSE
	.endif
	ret

ListaAFicheroListaDoble endp

LoadListaFormFileListaDoble PROC Lista:DWORD,lpFile:DWORD
	
	LOCAL HFile:DWORD
	LOCAL LocalBuff:DWORD
	LOCAL Pos:DWORD
	LOCAL BytesRead:DWORD
	LOCAL ItemSize:DWORD
	
	.if Lista == 0
		
		xor eax,eax
		ret
	.else
		; obtenemos el tamaño del ITEM
		mov eax,Lista
		assume eax: ptr NODOLISTADOBLE
			mov edx, [eax].LpItem
		assume eax:NOTHING
		mov ItemSize,edx
	.endif
	;1º Abrimos el Fichero 
	invoke CreateFile,lpFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL
	.if eax == INVALID_HANDLE_VALUE
		xor eax,eax
		ret
	.endif
	mov HFile,eax		
	
	
	;3º Pedimos memoria para el buffer auxiliar
	invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,ItemSize
	mov LocalBuff,eax
	.if eax == 0
		invoke CloseHandle,HFile
		xor eax,eax

		ret
	.endif
	;3 Guardamos el recurso en la lista
LoadListaFile_otroItem:
	invoke UltimoNodoListaDoble,Lista
	mov Pos,eax

	invoke ReadFile,HFile,LocalBuff,ItemSize,addr BytesRead,NULL
	.if BytesRead > 0
		invoke AnadirItemListaDoble,Lista,LocalBuff,Pos
		jmp LoadListaFile_otroItem
	.endif
	invoke CloseHandle,HFile
	;4 Borramos el buffer
	invoke LocalFree,LocalBuff
	mov eax,1
ret
LoadListaFormFileListaDoble endp

;**********************************************************************
;    DirOrd: Indica el orden de ordenación 0 menor a mayor
;                                          1 mayor a menor
;   Fun: Puntero a función CALLBACK que tiene el siguente prototipo
;                 PROC lpItme1:DWORD, lpItem2:DWORD
;
;        Debe de retornar:   0: Igual
;                            1: Item1 > Item2
;                           -1: Item1 < Item2
;**********************************************************************                                          
OrdenarListaDoble proc Lista:DWORD,DirOrd:DWORD,Fun:DWORD
	LOCAL  Pos1:DWORD
	LOCAL  Pos2:DWORD
	LOCAL  PosAux:DWORD
	LOCAL  PosUlt:DWORD
	LOCAL  PosPri:DWORD
	LOCAL  pItem1:DWORD
	LOCAL  pItem2:DWORD

	.if Lista == 0 || Fun == 0
		xor eax,eax
		ret
	.endif
	
	invoke UltimoNodoListaDoble,Lista
	mov PosUlt,eax
	
	invoke PrimerNodoListaDoble,Lista
	mov PosPri,eax
	
	cmp eax,PosUlt   ;Comprobación de Lista Vacia
	je OrdenarLista_FIN

		; Pedimos memoria para los Items
		mov eax,Lista
		assume eax: ptr NODOLISTADOBLE
			mov edx,[eax].LpItem ; tamaño del ITEM
		assume eax:NOTHING
			
		push edx
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
		mov pItem1,eax
			
		pop edx
		invoke LocalAlloc,LMEM_FIXED or LMEM_ZEROINIT,edx
		mov pItem2,eax

		
		invoke SiguienteNodoListaDoble,Lista,PosPri
		mov Pos1,eax

OrdenarLista_siguiente:		
		cmp eax,PosUlt
		je OrdenarLista_FIN
			
			mov eax,Pos1
			mov Pos2,eax

			
OrdenarLista_SigueCambiando:
			invoke AnteriorNodoListaDoble,Lista,Pos2
			mov PosAux,eax
		
 
			invoke RecuperarItemListaDoble,Lista,Pos2,pItem1 
			invoke RecuperarItemListaDoble,Lista,PosAux,pItem2
			
			
			push pItem2
			push pItem1
			call Fun
			
			; junto con el valor de EAX y DirOrd se comprueba si se cambia o no 
			cmp eax,0
			je OrdenarLista_Otro_dato
				
			mov ebx,DirOrd
			cmp ebx,0
			je 	OrdenarLista_Des			

				; Comprobamos si ascendente
				cmp eax,1
				jne OrdenarLista_Otro_dato
				jmp OrdenarLista_Cambia
				
OrdenarLista_Des:
			
			cmp eax,-1
			jne OrdenarLista_Otro_dato 

OrdenarLista_Cambia:
			;-------------------- Cambio en los datos
			
			mov eax,Pos2
			mov ebx,PosAux
			assume eax: ptr NODOLISTADOBLE 
			assume ebx: ptr NODOLISTADOBLE

				mov eax,[eax].LpNextNode
				mov ebx,[ebx].LpNextNode

				mov esi,[eax].LpItem
				mov edi,[ebx].LpItem
				mov [eax].LpItem,edi
				mov [ebx].LpItem,esi

   			assume ebx:NOTHING
   			assume eax:NOTHING			
			
			;-------------------- Seguimos comprobando  
			mov eax,PosAux
			cmp eax,PosPri
			je OrdenarLista_Otro_dato ; Fin de la comprobación
			
			mov Pos2,eax
			jmp OrdenarLista_SigueCambiando
		
OrdenarLista_Otro_dato:
			
		invoke SiguienteNodoListaDoble,Lista,Pos1
		mov Pos1,eax
		jmp OrdenarLista_siguiente
	
OrdenarLista_FIN:
	
	
	
	
	ret

OrdenarListaDoble endp
