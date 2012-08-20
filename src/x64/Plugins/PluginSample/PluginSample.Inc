include Alt_IF_en.mac
include x64calling.inc

include windows.inc 
include kernel32.inc 
include user32.inc
include comdlg32.inc
include shell32.inc


;**********  TE SDK ***************
include SDKx64.inc
include TitanEngine_x64.inc
;**********************************

includelib kernel32.lib 
includelib user32.lib
includelib ComDlg32.Lib
includelib Shell32.Lib


funcproto LOCAL,DllEntry,HINSTANCE,DWORD,DWORD
funcproto LOCAL,GetPluginName 
funcproto LOCAL,DoUnpack,QWORD,QWORD,QWORD,QWORD,QWORD

;*******  Struct to send the File Path and ComunicationObject to Dialog WinProc *********
MAINSTRUCT STRUC
	Object		dq ?
	lpFilePath	dq ?
MAINSTRUCT ends
;******************************************************************************************

COMUNICATIONPLUGIN STRUC
	LogString		dq ?
	ClearLog		dq ?
	LogToFile		dq ?
	GetMainHandle	dq ?
COMUNICATIONPLUGIN ends

;************************************************************
;    Macros for a easy using of the Log Method
;
;   NOTE:  The following macros have not suport the addr macro 
; to send the pointer of a buffer
;************************************************************
ClearLog MACRO Object:req
	push rbx
	mov rbx,Object
	mov rbx, [rbx].COMUNICATIONPLUGIN.ClearLog
	@AjustePila
	sub rsp,8*4 
	call rbx
   	add rsp,8*4
	@ReAjustePila
	pop rbx
ENDM


LogString MACRO Object:req,lpString:req    
	push rbx
	mov rbx,Object
	mov rbx, [rbx].COMUNICATIONPLUGIN.LogString
	@AjustePila
	sub rsp,8*4 
	;arg 1
	mov rcx,lpString
	call rbx
   	add rsp,8*4
	@ReAjustePila
	pop rbx
ENDM

LogToFile MACRO Object:req,lpFile:req,OverWritten:req  

	push rbx
	mov rbx,Object
	mov rbx, [rbx].COMUNICATIONPLUGIN.LogToFile
	@AjustePila
	sub rsp,8*4 
	;arg 1
	mov rcx,lpFile
	; arg 2
	mov rdx,OverWritten
	call rbx
 	add rsp,8*4
	@ReAjustePila
	pop rbx
ENDM

GetMainHandle MACRO Object:req

	push rbx
	mov rbx,Object
	mov rbx, [rbx].COMUNICATIONPLUGIN.GetMainHandle
	@AjustePila
	sub rsp,8*4 
	call rbx
 	add rsp,8*4
	@ReAjustePila
	pop rbx

ENDM
;********************************************************

.const



.data
hInst		dq 0 ; The hInstance of the dll

PluginName	db "Plugin PE Visor",0 ; The plugin Name
