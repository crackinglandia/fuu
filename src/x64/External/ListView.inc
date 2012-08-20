funcproto local,AnadirColumnaLW,QWORD,QWORD,DWORD
funcproto local,GetColumCountLW,QWORD
funcproto LOCAL,GetItemCountLW,QWORD
funcproto LOCAL,BorrarItemsLW,QWORD
funcproto LOCAL,AnadirTextLW,QWORD,QWORD,DWORD,DWORD
funcproto LOCAL,ModificarTextLW,QWORD,QWORD,DWORD,DWORD,DWORD
funcproto LOCAL,InsertarTextoLW,QWORD,QWORD,DWORD,DWORD

.code

function AnadirColumnaLW,Handle:QWORD,NameCol:QWORD,WidthCol:DWORD
	begin_alloc
		alloc_var Columna_Aux:LV_COLUMN
		alloc_var Index:DWORD
	end_alloc
	
	invoke GetColumCountLW,Handle
	mov Index,eax
	
	mov Columna_Aux.LV_COLUMN.imask,LVCF_TEXT or LVCF_FMT or LVCF_WIDTH
	mov eax,WidthCol
	mov Columna_Aux.LV_COLUMN.lx,eax
	mov Columna_Aux.LV_COLUMN.fmt,LVCFMT_LEFT
	mov eax,Index		
	mov Columna_Aux.LV_COLUMN.iSubItem,eax
	
	mov rax,NameCol
	mov Columna_Aux.LV_COLUMN.pszText,rax 
	invoke lstrlen,NameCol
	mov Columna_Aux.LV_COLUMN.cchTextMax,eax
	
	invoke SendMessage,Handle,LVM_INSERTCOLUMN,Index,addr Columna_Aux
	
	xor rax,rax
	mov eax,Index
	return rax 
	
exitf

function GetColumCountLW,Handle:QWORD  
	begin_alloc
		         
		alloc_var Columna_Aux:LV_COLUMN
		alloc_var Index:DWORD    
	end_alloc
	xor rax,rax
	mov Index,eax

	mov Columna_Aux.LV_COLUMN.imask,LVCF_WIDTH	 ;Necesitamos fijar algo en la máscara para preguntar
												 ;Sino en función de la basura funciona o no
												 ;en este caso pedimos el ancho. 
GetColumCountLW_Otra:
	
	invoke SendMessage,Handle,LVM_GETCOLUMN,Index,addr Columna_Aux 
	@IF <<cmp rax,0>>,NOEQUAL?
		mov eax,Index
		inc eax
		mov Index,eax
		jmp GetColumCountLW_Otra
	@ENDIF
	xor rax,rax
	mov eax,Index
	return rax
exitf	

function AnadirTextLW,Handle:QWORD,NameItem:QWORD,NCol:DWORD,IndexImage:DWORD
	begin_alloc
		alloc_var Item_Aux:LV_ITEM
		alloc_var Index:DWORD
	end_alloc

	invoke setmem,addr Item_Aux,sizeof LV_ITEM,0 
	invoke GetItemCountLW,Handle
	dec rax
	
	cmp rax,0
	jge	AnadirTextLW_IndexOK
		xor rax,rax
AnadirTextLW_IndexOK:
	mov ebx,NCol
	@IF <<cmp ebx,0>>,EQUAL?
		inc rax
	@ENDIF	
	mov Index,eax
	
	mov eax,IndexImage
	mov Item_Aux.LV_ITEM.iImage,eax
	mov Item_Aux.LV_ITEM.imask,LVIF_TEXT or LVIF_IMAGE
		
	mov eax,Index
	mov Item_Aux.LV_ITEM.iItem,eax
	mov eax,NCol
	mov Item_Aux.LV_ITEM.iSubItem,eax
	mov rax,NameItem
	mov Item_Aux.LV_ITEM.pszText,rax
	invoke lstrlen,rax
	inc eax
	mov Item_Aux.LV_ITEM.cchTextMax,eax
	
	mov Item_Aux.LV_ITEM.LParam,0

	mov eax,NCol	
	@IF <<cmp eax,0>>,EQUAL?
		invoke SendMessage,Handle,LVM_INSERTITEM,0,addr Item_Aux
	@ELSE
		invoke SendMessage,Handle,LVM_SETITEM,0,addr Item_Aux
	@ENDIF
exitf

function InsertarTextoLW,Handle:QWORD,NameItem:QWORD,Pos:DWORD,NCol:DWORD
	begin_alloc
	 	alloc_var Item_Aux:LV_ITEM
	end_alloc
	
	invoke setmem,addr Item_Aux,sizeof LV_ITEM,0 
	mov eax,Pos
	cmp eax,0
	jge InsertarTextoLW_IndexOK
		return 0
		
InsertarTextoLW_IndexOK:
	mov ebx,NCol
	@IF <<cmp ebx,0>>,EQUAL?
		inc eax
	@ENDIF	
		
	mov Item_Aux.LV_ITEM.imask,LVIF_TEXT
	mov eax,Pos
	mov Item_Aux.LV_ITEM.iItem,eax
	mov eax,NCol
	mov Item_Aux.LV_ITEM.iSubItem,eax
	mov rax,NameItem
	mov Item_Aux.LV_ITEM.pszText,rax
	invoke lstrlen,rax
	inc eax
	mov Item_Aux.LV_ITEM.cchTextMax,eax
	mov Item_Aux.LV_ITEM.iImage,0
	mov Item_Aux.LV_ITEM.LParam,0

	mov eax,NCol	
	@IF <<cmp eax,0>>,EQUAL?
		invoke SendMessage,Handle,LVM_INSERTITEM,0,addr Item_Aux
	@ELSE
		invoke SendMessage,Handle,LVM_SETITEM,0,addr Item_Aux
	@ENDIF

exitf


function ModificarTextLW,Handle:QWORD,lpText:QWORD,NItem:DWORD,NCol:DWORD,IndexImage:DWORD

	begin_alloc
		alloc_var Item_Aux:LV_ITEM
	end_alloc
	
	mov eax,IndexImage
	@IF <<cmp eax,-1>>,EQUAL?
		mov Item_Aux.LV_ITEM.imask,LVIF_TEXT
		mov Item_Aux.LV_ITEM.iImage,0
	@ELSE
		mov Item_Aux.LV_ITEM.imask,LVIF_TEXT or LVIF_IMAGE	
		mov Item_Aux.LV_ITEM.iImage,eax
	@ENDIF
	
	mov eax,NItem
	mov Item_Aux.LV_ITEM.iItem,eax
	mov eax,NCol
	mov Item_Aux.LV_ITEM.iSubItem,eax
	mov rax,lpText
	mov Item_Aux.LV_ITEM.pszText,rax
	invoke lstrlen,rax
	inc eax
	mov Item_Aux.LV_ITEM.cchTextMax,eax
	
	mov Item_Aux.LV_ITEM.LParam,0
	invoke SendMessage,Handle,LVM_SETITEM,0,addr Item_Aux

exitf

function GetItemCountLW,Handle:QWORD
	invoke SendMessage,Handle,LVM_GETITEMCOUNT,0,0
exitf

function BorrarItemsLW,Handle:QWORD
	invoke SendMessage,Handle,LVM_DELETEALLITEMS,0,0
exitf