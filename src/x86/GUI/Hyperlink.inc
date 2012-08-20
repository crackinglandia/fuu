; $Id: Hyperlink.inc 34 2010-07-11 22:30:28Z nahuelriva $

_Hyperlink 			proto :DWORD,:DWORD,:DWORD,:DWORD
InitHyperLinkClass 	proto

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

.data

.code

_Hyperlink proc hlc_hWin:DWORD,hlc_uMsg:DWORD,hlc_wParam:DWORD,hlc_lParam:DWORD
	comment ~
	Function Name: _Hyperlink
	Function Description: Receive and process all WM for the hyperlink stuffs
	Function Parameters: 
		hlc_hWin: DWORD
		hlc_uMsg: DWORD
		hlc_wParam: DWORD
		hlc_lParam: DWORD
	~

	LOCAL hlc_tme				:TRACKMOUSEEVENT
	LOCAL hlc_ps				:PAINTSTRUCT
	LOCAL hlc_hdc				:DWORD
	LOCAL hlc_strlen			:DWORD
	LOCAL hlc_prc				:RECT
	LOCAL hlc_color				:DWORD
	LOCAL hlc_pt				:POINT
	LOCAL hlc_text[2048]		:BYTE
	LOCAL hlc_pSubject			:DWORD

	.if hlc_uMsg == WM_SETTEXT
		; Get the border size
		invoke GetWindowRect,hlc_hWin,ADDR hlc_prc
		mov eax,hlc_prc.right
		sub eax,hlc_prc.left
		push eax
		mov eax,hlc_prc.bottom
		sub eax,hlc_prc.top
		push eax
		invoke GetClientRect,hlc_hWin,ADDR hlc_prc
		pop eax
		sub eax,hlc_prc.bottom
		pop ecx
		push eax
		sub ecx,hlc_prc.right
		push ecx

		invoke GetDC,hlc_hWin
		mov hlc_hdc,eax

		invoke GetWindowLong,hlc_hWin,20
		.if !eax
			invoke GetStockObject,SYSTEM_FONT
		.endif
		invoke SelectObject,hlc_hdc,eax
		invoke lstrlen,hlc_lParam
		mov hlc_strlen,eax
		invoke DrawText,hlc_hdc,hlc_lParam,hlc_strlen,ADDR hlc_prc,DT_CALCRECT
		pop ecx
		add ecx,hlc_prc.right
		sub ecx,hlc_prc.left

		pop eax
		add eax,hlc_prc.bottom
		sub eax,hlc_prc.top
		invoke SetWindowPos,hlc_hWin,HWND_TOP,0,0,ecx,eax,SWP_NOMOVE or SWP_NOZORDER
		invoke ReleaseDC,hlc_hWin,hlc_hdc

	.elseif hlc_uMsg == WM_CREATE
		invoke GlobalAlloc,GMEM_FIXED,4192
		invoke SetWindowLong,hlc_hWin,12,eax

	.elseif hlc_uMsg == HLM_SETTYPE
		invoke SetWindowLong,hlc_hWin,0,hlc_lParam
		ret

	.elseif hlc_uMsg == HLM_SETUNDERLINE
		invoke SetWindowLong,hlc_hWin,32,hlc_lParam
		ret

	.elseif hlc_uMsg == HLM_SETHOTCOLOR
		invoke SetWindowLong,hlc_hWin,4,hlc_lParam

		; set the current color if necessary
		invoke GetCursorPos,ADDR hlc_pt
		invoke GetParent,hlc_hWin
		push eax
		mov ecx,eax
		invoke ScreenToClient,ecx,ADDR hlc_pt
		pop ecx
		invoke ChildWindowFromPoint,ecx,hlc_pt.x,hlc_pt.y
		.if eax == hlc_hWin
			invoke SetWindowLong,hlc_hWin,16,hlc_lParam
			mov hlc_tme.cbSize,SIZEOF TRACKMOUSEEVENT
			mov hlc_tme.dwFlags,TME_LEAVE
			mov eax,hlc_hWin
			mov hlc_tme.hwndTrack,eax
			mov hlc_tme.dwHoverTime,HOVER_DEFAULT
			invoke _TrackMouseEvent,ADDR hlc_tme
		.endif
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		invoke UpdateWindow,hlc_hWin
		ret

	.elseif hlc_uMsg == HLM_SETTEXTCOLOR
		invoke SetWindowLong,hlc_hWin,8,hlc_lParam

		; set the current color if necessary
		invoke GetCursorPos,ADDR hlc_pt
		invoke GetParent,hlc_hWin
		push eax
		mov ecx,eax
		invoke ScreenToClient,ecx,ADDR hlc_pt
		pop ecx
		invoke ChildWindowFromPoint,ecx,hlc_pt.x,hlc_pt.y
		.if eax != hlc_hWin
			invoke SetWindowLong,hlc_hWin,16,hlc_lParam
		.endif
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		invoke UpdateWindow,hlc_hWin
		ret

	.elseif hlc_uMsg == HLM_SETSUBJECT
		invoke lstrlen,hlc_lParam
		inc eax
		mov hlc_strlen,eax
		invoke GetWindowLong,hlc_hWin,24
		mov hlc_pSubject,eax
		.if eax
			invoke GlobalFree,eax
		.endif
		invoke GlobalAlloc,GMEM_FIXED,hlc_strlen
		mov hlc_pSubject,eax
		.if hlc_strlen >= 1024
			mov eax,hlc_lParam
			add eax,1023
			mov BYTE PTR [eax],0
		.endif
		invoke lstrcpy,hlc_pSubject,hlc_lParam
		invoke SetWindowLong,hlc_hWin,24,hlc_pSubject
		ret

	.elseif hlc_uMsg == HLM_SETBODY
		invoke lstrlen,hlc_lParam
		inc eax
		mov hlc_strlen,eax
		invoke GetWindowLong,hlc_hWin,28
		mov hlc_pSubject,eax
		.if eax
			invoke GlobalFree,eax
		.endif
		invoke GlobalAlloc,GMEM_FIXED,hlc_strlen
		mov hlc_pSubject,eax
		.if hlc_strlen >= 1024
			mov eax,hlc_lParam
			add eax,1023
			mov BYTE PTR [eax],0
		.endif
		invoke lstrcpy,hlc_pSubject,hlc_lParam
		invoke SetWindowLong,hlc_hWin,28,hlc_pSubject
		ret

	.elseif hlc_uMsg == WM_SETFONT
		; The def window proc does not do fonts so it has to be done manually
		invoke SetWindowLong,hlc_hWin,20,hlc_wParam
		invoke GetWindowText,hlc_hWin,ADDR hlc_text,256
		invoke SetWindowText,hlc_hWin,ADDR hlc_text
		.if hlc_lParam
			invoke InvalidateRect,hlc_hWin,NULL,TRUE
			invoke UpdateWindow,hlc_hWin
		.endif
		ret

	.elseif hlc_uMsg == WM_LBUTTONDOWN
		invoke GetWindowLong,hlc_hWin,12
		mov hlc_pSubject,eax

		invoke GetWindowLong,hlc_hWin,0
		.if eax == HLINK_URL
			lea eax,hlc_text
			invoke GetWindowText,hlc_hWin,hlc_pSubject,256
			
		.elseif eax == HLINK_EMAIL
			jmp @F
				hlc_szMailTo 	db		"mailto:",0
				hlc_szSubject	db		"?subject=",0
				hlc_szBody		db		"&body=",0
				hlc_szOpen		db		"open",0
			@@:
			invoke lstrcpy,hlc_pSubject,OFFSET hlc_szMailTo
			mov eax,hlc_pSubject
			add eax,7
			invoke GetWindowText,hlc_hWin,eax,240
			invoke GetWindowLong,hlc_hWin,24
			.if eax
				push eax
				invoke lstrcat,hlc_pSubject,OFFSET hlc_szSubject
				pop eax
				invoke lstrcat,hlc_pSubject,eax
				invoke GetWindowLong,hlc_hWin,28
				.if eax
					push eax
					invoke lstrcat,hlc_pSubject,OFFSET hlc_szBody
					pop eax
					invoke lstrcat,hlc_pSubject,eax
				.endif
			.endif
	
		.endif
		invoke ShellExecute, hlc_hWin, OFFSET hlc_szOpen,hlc_pSubject, 0, 0, SW_SHOWNORMAL

	.elseif hlc_uMsg == WM_MOUSEMOVE
		; The first mouse move message changes the color
		invoke GetWindowLong,hlc_hWin,4
		push eax
		invoke SetWindowLong,hlc_hWin,16,eax
		pop ecx
		.if eax != ecx
			invoke GetDlgCtrlID,hlc_hWin
			push eax
			invoke GetParent,hlc_hWin
			pop ecx
			invoke SendMessage,eax,HLM_ISHOT,ecx,hlc_hWin
			mov hlc_tme.cbSize,SIZEOF TRACKMOUSEEVENT
			mov hlc_tme.dwFlags,TME_LEAVE
			mov eax,hlc_hWin
			mov hlc_tme.hwndTrack,eax
			mov hlc_tme.dwHoverTime,HOVER_DEFAULT
			invoke _TrackMouseEvent,ADDR hlc_tme
			invoke InvalidateRect,hlc_hWin,NULL,TRUE
		.ENDIF

	.elseif hlc_uMsg == WM_MOUSELEAVE
		invoke GetWindowLong,hlc_hWin,8
		invoke SetWindowLong,hlc_hWin,16,eax
		invoke InvalidateRect,hlc_hWin,NULL,TRUE
		ret

	.elseif hlc_uMsg == WM_PAINT
		invoke GetWindowText,hlc_hWin,ADDR hlc_text,256
		mov hlc_strlen,eax
		invoke GetWindowLong,hlc_hWin,16
		mov hlc_color,eax
		invoke BeginPaint,hlc_hWin,ADDR hlc_ps
			mov hlc_hdc,eax
			invoke GetWindowLong,hlc_hWin,20
			invoke SelectObject,hlc_hdc,eax
			invoke SetTextColor,hlc_hdc,hlc_color
			invoke SetBkMode,hlc_hdc,TRANSPARENT
			invoke TextOut,hlc_hdc,0,0,ADDR hlc_text,hlc_strlen
			invoke GetWindowLong,hlc_hWin,32 ; Underline
			.if eax
				; a line is drawn
				invoke CreatePen,PS_SOLID,1,hlc_color
				invoke SelectObject,hlc_hdc,eax
				push eax
				invoke GetClientRect,hlc_hWin,ADDR hlc_prc
				dec hlc_prc.bottom
				invoke MoveToEx,hlc_hdc,0,hlc_prc.bottom,NULL
				invoke LineTo,hlc_hdc,hlc_prc.right,hlc_prc.bottom
				pop eax
				invoke SelectObject,hlc_hdc,eax
				invoke DeleteObject,eax
			.endif
		invoke EndPaint,hlc_hWin,ADDR hlc_ps
		ret


	.elseif hlc_uMsg == WM_DESTROY
		invoke GetWindowLong,hlc_hWin,12
		.if eax
			invoke GlobalFree,eax
		.endif
		invoke GetWindowLong,hlc_hWin,24
		.if eax
			invoke GlobalFree,eax
		.endif
		invoke GetWindowLong,hlc_hWin,28
		.if eax
			invoke GlobalFree,eax
		.endif

	.endif

	invoke DefWindowProc,hlc_hWin,hlc_uMsg,hlc_wParam,hlc_lParam
	ret
	
_Hyperlink endp

InitHyperLinkClass proc
	comment ~
	Function Name: InitHyperLinkClass
	Function Description: Creates the Hyperlink class
	Function Parameters: None
	~

	LOCAL hlc_wcx:WNDCLASSEX

	jmp @F
		UDC_HyperClass	db		"UDC_HyperLink",0
	@@:

	mov hlc_wcx.cbSize,SIZEOF WNDCLASSEX
	mov hlc_wcx.style, CS_HREDRAW or CS_VREDRAW
	mov eax,hInstance
	mov hlc_wcx.hInstance,eax
	mov hlc_wcx.lpszClassName,OFFSET UDC_HyperClass
	mov hlc_wcx.cbClsExtra,0
	mov hlc_wcx.cbWndExtra,36
	mov hlc_wcx.lpfnWndProc,OFFSET _Hyperlink
	mov hlc_wcx.hIcon,NULL
	mov hlc_wcx.hIconSm,NULL
	invoke GetStockObject,NULL_BRUSH
	mov hlc_wcx.hbrBackground,eax
	mov hlc_wcx.lpszMenuName,NULL

	invoke LoadCursor,NULL,IDC_HAND
	mov hlc_wcx.hCursor,eax

	invoke RegisterClassEx,ADDR hlc_wcx

	ret

InitHyperLinkClass endp
