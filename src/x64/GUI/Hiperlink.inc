; $Id: Hiperlink.inc 62 2010-07-12 17:18:44Z nahuelriva $
;
; Hyperlink stuffs from: http://members.a1.net/ranmasaotome/masm32/Hyperlink.zip
;
; It's adapted to 64 bits


; NCR hay algo raro con la API GetClientRect, no termina de devolver bien el Ancho, al menos en W7. 
; Esto afecta por ejemplo en la región en la que el ratón se supone que está encima del control, ya que también se usaba para 
; dibujar el subrayado pero eso lo he podido mejorar usando otra API. 

funcproto LOCAL,InitHyperLinkClass
funcproto LOCAL, _Hyperlink,HWND,UINT,WPARAM,LPARAM

.const 

HLM_SETTYPE			equ		WM_USER+200 ; lParam = HLINK_URL/HLINK_EMAIL wndxtra 0
HLM_SETHOTCOLOR		equ		WM_USER+201 ; lParam = Hot color wndxtra 4
HLM_SETTEXTCOLOR	equ		WM_USER+202 ; lParam = Normal text color wndxtra 8
HLM_ISHOT			equ		WM_USER+206 ; Sent to parent wParam = ID, lParam = hControl
HLM_SETSUBJECT		equ		WM_USER+203 ; lParam = Email subject line wndxtra 24
HLM_SETBODY			equ		WM_USER+204 ; lParam = Email body wndxtra 28
HLM_SETUNDERLINE	equ		WM_USER+205 ; lParam = Underline link TRUE/FALSE wndxtra 32

HLINK_URL			equ		0
HLINK_EMAIL			equ		1

.code

function InitHyperLinkClass 
	begin_alloc
		alloc_var hlc_wcx:WNDCLASSEX
	end_alloc
	jmp @F
		UDC_HyperClass	db		"UDC_HyperLink",0
	@@:

	mov hlc_wcx.WNDCLASSEX.cbSize,SIZEOF WNDCLASSEX
	mov hlc_wcx.WNDCLASSEX.style, CS_HREDRAW or CS_VREDRAW
	mov rax,hInstance
	mov hlc_wcx.WNDCLASSEX.hInstance,rax
	lea rax,UDC_HyperClass
	mov hlc_wcx.WNDCLASSEX.lpszClassName,rax 
	mov hlc_wcx.WNDCLASSEX.cbClsExtra,0
	mov hlc_wcx.WNDCLASSEX.cbWndExtra,72 ; Memoria extra necesaria para alojar variables
	lea rax,_Hyperlink
	mov hlc_wcx.WNDCLASSEX.lpfnWndProc,rax 
	mov hlc_wcx.WNDCLASSEX.hIcon,NULL
	mov hlc_wcx.WNDCLASSEX.hIconSm,NULL
	invoke GetStockObject,NULL_BRUSH
	mov hlc_wcx.WNDCLASSEX.hbrBackground,rax
	mov hlc_wcx.WNDCLASSEX.lpszMenuName,NULL

	invoke LoadCursor,NULL,IDC_HAND
	mov hlc_wcx.WNDCLASSEX.hCursor,rax

	invoke RegisterClassEx,addr hlc_wcx

exitf


function _Hyperlink,hlc_hWin:HWND,hlc_uMsg:UINT,hlc_wParam:WPARAM,hlc_lParam:LPARAM
	begin_alloc 
		alloc_var hlc_tme:TRACKMOUSEEVENT
		alloc_var hlc_ps:PAINTSTRUCT
		alloc_var hlc_hdc:QWORD
		alloc_var hlc_strlen:DWORD
		alloc_var hlc_prc:RECT
		alloc_var hlc_color:QWORD
		alloc_var hlc_pt:POINT
		alloc_var hlc_pSubject:QWORD
		alloc_var hlc_Tamano:TSIZE 
		alloc_var hlc_text{2048}:BYTE  
	end_alloc

	xor rax,rax
	mov eax,hlc_uMsg
	@IF <<cmp  eax,WM_SETTEXT>>,EQUAL?
		; Get the border size
		invoke GetWindowRect,hlc_hWin,addr hlc_prc
		xor rax,rax
		mov eax,hlc_prc.RECT.right
		sub eax,hlc_prc.RECT.left
		push rax
		mov eax,hlc_prc.RECT.bottom
		sub eax,hlc_prc.RECT.top
		push rax
		invoke GetClientRect,hlc_hWin,addr hlc_prc
		pop rax
		sub eax,hlc_prc.RECT.bottom
		pop rcx
		push rax
		sub ecx,hlc_prc.RECT.right
		push rcx

		invoke GetDC,hlc_hWin
		mov hlc_hdc,rax

		invoke GetWindowLongPtr,hlc_hWin,40
		@IF <<cmp rax,0>>,NOEQUAL?
			invoke GetStockObject,SYSTEM_FONT
		@ENDIF
		invoke SelectObject,hlc_hdc,rax
		invoke lstrlen,hlc_lParam
		mov hlc_strlen,eax
		invoke DrawText,hlc_hdc,hlc_lParam,hlc_strlen,addr hlc_prc,DT_CALCRECT
		pop rcx
		add ecx,hlc_prc.RECT.right
		sub ecx,hlc_prc.RECT.left

		pop rax
		add eax,hlc_prc.RECT.bottom
		sub eax,hlc_prc.RECT.top
		invoke SetWindowPos,hlc_hWin,HWND_TOP,0,0,ecx,eax,SWP_NOMOVE or SWP_NOZORDER
		invoke ReleaseDC,hlc_hWin,hlc_hdc

	@ELSEIF <<cmp eax, WM_CREATE>>,EQUAL?
		invoke GlobalAlloc,GMEM_FIXED,4192
		invoke SetWindowLongPtr,hlc_hWin,24,rax

	@ELSEIF <<cmp eax, HLM_SETTYPE>>,EQUAL?
		invoke SetWindowLongPtr,hlc_hWin,0,hlc_lParam
		return rax;

	@ELSEIF <<cmp eax,HLM_SETUNDERLINE>>,EQUAL?
		invoke SetWindowLongPtr,hlc_hWin,64,hlc_lParam  ;Esto parece que no va
		return rax;

	@ELSEIF <<cmp eax,HLM_SETHOTCOLOR>>,EQUAL?
		invoke SetWindowLongPtr,hlc_hWin,8,hlc_lParam

		; set the current color if necessary
		invoke GetCursorPos,addr hlc_pt
		invoke GetParent,hlc_hWin
		push rax
		mov rcx,rax
		invoke ScreenToClient,rcx,addr hlc_pt
		pop rcx
		invoke ChildWindowFromPoint,rcx,hlc_pt.POINT.x,hlc_pt.POINT.y
		@IF <<cmp rax,hlc_hWin>>,EQUAL?
			invoke SetWindowLongPtr,hlc_hWin,32,hlc_lParam
			mov hlc_tme.TRACKMOUSEEVENT.cbSize,SIZEOF TRACKMOUSEEVENT
			mov hlc_tme.TRACKMOUSEEVENT.dwFlags,TME_LEAVE
			mov rax,hlc_hWin
			mov hlc_tme.TRACKMOUSEEVENT.hwndTrack,rax
			mov hlc_tme.TRACKMOUSEEVENT.dwHoverTime,HOVER_DEFAULT
			invoke TrackMouseEvent,addr hlc_tme
		@ENDIF
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		invoke UpdateWindow,hlc_hWin
		return rax

	@ELSEIF <<cmp eax, HLM_SETTEXTCOLOR>>,EQUAL?
		invoke SetWindowLongPtr,hlc_hWin,16,hlc_lParam

		; set the current color if necessary
		invoke GetCursorPos,addr hlc_pt
		invoke GetParent,hlc_hWin
		push rax
		mov rcx,rax
		invoke ScreenToClient,rcx,addr hlc_pt
		pop rcx
		invoke ChildWindowFromPoint,rcx,hlc_pt.POINT.x,hlc_pt.POINT.y
		@IF <<cmp rax,hlc_hWin>>,EQUAL?
			invoke SetWindowLongPtr,hlc_hWin,32,hlc_lParam
		@ENDIF
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		invoke UpdateWindow,hlc_hWin
		return rax

	@ELSEIF <<cmp eax, HLM_SETSUBJECT>>,EQUAL?
		invoke lstrlen,hlc_lParam
		inc eax
		mov hlc_strlen,eax
		invoke GetWindowLongPtr,hlc_hWin,48
		mov hlc_pSubject,rax
		@IF <<cmp eax,0>>,NOEQUAL?
			invoke GlobalFree,rax
		@ENDIF
		invoke GlobalAlloc,GMEM_FIXED,hlc_strlen
		mov hlc_pSubject,rax
		mov eax,hlc_strlen
		@IF <<cmp eax,1024>>,ABOVE?||EQUAL?
			mov rax,hlc_lParam
			add rax,1023
			mov BYTE PTR [rax],0
		@ENDIF
		invoke lstrcpy,hlc_pSubject,hlc_lParam
		invoke SetWindowLongPtr,hlc_hWin,48,hlc_pSubject
		return rax

	@ELSEIF <<cmp eax, HLM_SETBODY>>,EQUAL?
		invoke lstrlen,hlc_lParam
		inc eax
		mov hlc_strlen,eax
		invoke GetWindowLongPtr,hlc_hWin,56
		mov hlc_pSubject,rax
		@IF <<cmp rax,0>>,NOEQUAL?
			invoke GlobalFree,rax
		@ENDIF
		invoke GlobalAlloc,GMEM_FIXED,hlc_strlen
		mov hlc_pSubject,rax
		mov eax,hlc_strlen
		@IF <<cmp eax,1024>>,ABOVE?||EQUAL?
			mov rax,hlc_lParam
			add rax,1023
			mov BYTE PTR [rax],0
		@ENDIF
		invoke lstrcpy,hlc_pSubject,hlc_lParam
		invoke SetWindowLongPtr,hlc_hWin,56,hlc_pSubject
		return rax

	@ELSEIF <<cmp eax,WM_SETFONT>>,EQUAL?
		; The def window proc does not do fonts so it has to be done manually
		invoke SetWindowLongPtr,hlc_hWin,40,hlc_wParam
		invoke GetWindowText,hlc_hWin,addr hlc_text,256
		invoke SetWindowText,hlc_hWin,addr hlc_text
		mov rax,hlc_lParam
		@IF <<cmp rax,0>>,NOEQUAL?
			invoke InvalidateRect,hlc_hWin,NULL,TRUE
			invoke UpdateWindow,hlc_hWin
		@ENDIF
		return rax

	@ELSEIF <<cmp eax, WM_LBUTTONDOWN>>,EQUAL?
		invoke GetWindowLongPtr,hlc_hWin,24
		mov hlc_pSubject,rax

		invoke GetWindowLongPtr,hlc_hWin,0
		
		@IF << cmp rax,HLINK_URL>>,EQUAL?
			lea rax,hlc_text
			invoke GetWindowText,hlc_hWin,hlc_pSubject,256


		@ELSEIF <<cmp rax,HLINK_EMAIL>>,EQUAL?
			jmp @F
				hlc_szMailTo 	db		"mailto:",0
				hlc_szSubject	db		"?subject=",0
				hlc_szBody		db		"&body=",0
				hlc_szOpen		db		"open",0
			@@:
			invoke lstrcpy,hlc_pSubject,addr hlc_szMailTo
			mov rax,hlc_pSubject
			add rax,7
			invoke GetWindowText,hlc_hWin,rax,240
			invoke GetWindowLongPtr,hlc_hWin,48
			@IF <<cmp rax,0>>,NOEQUAL?
				push rax
				invoke lstrcat,hlc_pSubject,addr hlc_szSubject
				pop rax
				invoke lstrcat,hlc_pSubject,rax
				invoke GetWindowLongPtr,hlc_hWin,56
				@IF <<cmp rax,0>>,NOEQUAL?
					push rax
					invoke lstrcat,hlc_pSubject,addr hlc_szBody
					pop rax
					invoke lstrcat,hlc_pSubject,rax
				@ENDIF
			@ENDIF
	
		@ENDIF
		invoke ShellExecute, hlc_hWin, addr hlc_szOpen,hlc_pSubject, 0, 0, SW_SHOWNORMAL

	@ELSEIF <<cmp eax,WM_MOUSEMOVE>>,EQUAL?
		; The first mouse move message changes the color
		invoke GetWindowLongPtr,hlc_hWin,8
		push rax
		invoke SetWindowLongPtr,hlc_hWin,32,rax
		pop rcx
		@IF <<cmp rax,rcx>>,NOEQUAL?
		
			invoke GetDlgCtrlID,hlc_hWin
			push rax
			invoke GetParent,hlc_hWin
			pop rcx
			invoke SendMessage,rax,HLM_ISHOT,rcx,hlc_hWin
			mov hlc_tme.TRACKMOUSEEVENT.cbSize,SIZEOF TRACKMOUSEEVENT
			mov hlc_tme.TRACKMOUSEEVENT.dwFlags,TME_LEAVE
			mov rax,hlc_hWin
			mov hlc_tme.TRACKMOUSEEVENT.hwndTrack,rax
			mov hlc_tme.TRACKMOUSEEVENT.dwHoverTime,HOVER_DEFAULT
			invoke TrackMouseEvent,addr hlc_tme
			invoke InvalidateRect,hlc_hWin,NULL,TRUE
		@ENDIF

	@ELSEIF <<cmp eax,WM_MOUSELEAVE>>,EQUAL?
		invoke GetWindowLongPtr,hlc_hWin,16
		invoke SetWindowLongPtr,hlc_hWin,32,rax
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		return rax

	@ELSEIF <<cmp eax, WM_PAINT>>,EQUAL?
		invoke GetWindowText,hlc_hWin,addr hlc_text,256
		mov hlc_strlen,eax
		invoke GetWindowLongPtr,hlc_hWin,32 
		mov hlc_color,rax
		invoke BeginPaint,hlc_hWin,addr hlc_ps
			mov hlc_hdc,rax
			invoke GetWindowLongPtr,hlc_hWin,40 
			invoke SelectObject,hlc_hdc,rax
			invoke SetTextColor,hlc_hdc,hlc_color
			invoke SetBkMode,hlc_hdc,TRANSPARENT
			invoke TextOut,hlc_hdc,0,0,addr hlc_text,hlc_strlen
			invoke GetWindowLongPtr,hlc_hWin,64 ; Underline
			@IF <<cmp rax,0>>,NOEQUAL?
			
				; a line is drawn
				invoke CreatePen,PS_SOLID,1,hlc_color
				invoke SelectObject,hlc_hdc,rax
				push rax
				
				invoke GetTextExtentPoint32,hlc_hdc,addr hlc_text,hlc_strlen,addr hlc_Tamano
			
				invoke MoveToEx,hlc_hdc,0,hlc_Tamano.TSIZE.Alto,NULL
				
				invoke LineTo,hlc_hdc,hlc_Tamano.TSIZE.Ancho,hlc_Tamano.TSIZE.Alto
				pop rax
				invoke SelectObject,hlc_hdc,rax
				invoke DeleteObject,rax
			@ENDIF
		invoke EndPaint,hlc_hWin,addr hlc_ps
		return rax

	@ELSEIF <<cmp eax, WM_DESTROY>>,EQUAL?
		invoke GetWindowLongPtr,hlc_hWin,24
		@IF <<cmp rax,0>>,NOEQUAL?
			invoke GlobalFree,rax
		@ENDIF
		invoke GetWindowLongPtr,hlc_hWin,48
		@IF <<cmp rax,0>>,NOEQUAL?
			invoke GlobalFree,rax
		@ENDIF
		invoke GetWindowLongPtr,hlc_hWin,56
		@IF << cmp rax,0>>,NOEQUAL?
			invoke GlobalFree,rax
		@ENDIF

	@ENDIF

	invoke DefWindowProc,hlc_hWin,hlc_uMsg,hlc_wParam,hlc_lParam
exitf