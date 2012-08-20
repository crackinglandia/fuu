; $Id: PluginSample.asm guan $
comment ~
   Plugin Sample for x64 version 

   Copyright (C) 2010 ReversingLabs www.reversinglabs.com

 	This library is free software: you can redistribute it and/or
 	modify it under the terms of the GNU Lesser General Public
 	License as published by the Free Software Foundation, either
 	version 3 of the License, or any later version.
 
 	This library is distributed in the hope that it will be useful,
 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 	Lesser General Public License for more details.
 
 	You should have received a copy of the GNU Lesser General Public
 	License along with this library.  If not, see <http://www.gnu.org/licenses/>.



	---------------------------------------------
	Modified version by +NCR/CRC! [ReVeRsEr]
	---------------------------------------------

The objective of this plugins is to show the squeleton of a FUU's plugin 
This plugin is a small PE+ visor 

Currently, the unique way to work with TE in x64 is making the load dinamically. 
For that the SDK is divided in 2 files.
     - SDKx64.inc   Has the Struct and const for handle the TE. 
     - TitanEngine_x64.inc  has the defintion of the APIs and Loads the library. 
~



include PluginSample.inc

include ..\..\External\funciones64.inc
include ..\..\External\ListView.inc

; Has the code of the Dialog 
include MainDialog.inc

function DllEntry,hInstance:HINSTANCE, reason:DWORD, reserved1:DWORD 
    comment ~
	Function Name: DllEntry
	Function Description: The main function of the dll 
	Function Parameters:
		hInstance: HINSTANCE
		reason: DWORD
		reserved1: DWORD
	~
	
    mov eax,reason
    @IF <<cmp eax,DLL_PROCESS_ATTACH>>,EQUAL?
        push hInstance 
        pop hInst
      	
      	invoke LoadTitanEngine ; That is a provisional solution 
 	@ELSEIF <<cmp eax,DLL_PROCESS_DETACH>>,EQUAL?
 		invoke UnLoadTitanEngine ; That is a provisional solution 
 		
    @ENDIF
    return TRUE
     
exitf

function GetPluginName 
	comment ~
	Function Name: GetPluginName
	Function Description: Returns the plugin's name 
	Function Parameters: None
	~
	
	lea rax, PluginName
	return rax
exitf

function DoUnpack,lpCommunicationObject:QWORD, szFname:QWORD, lpOptoinsArray:QWORD ,lpReserved:QWORD, lpParam:QWORD
	comment ~
	Function Name: DoUnpack
	Function Description: That's the function that is called when Unpack button is pressed in the FUU GUI
	 
	Function Parameters:
		lpCommunicationObject: QWORD  it is a pointer to Comunication Object. 
		szFname: QWORD    it is a pointer to FilePath
		lpOptionsArray: QWORD
		lpReserved: QWORD
		lpParam: QWORD
	
	
	lpCommunicationObject is a pointer to COMUNICATIONPLUGIN STRUC which is described in PluginSample.inc
		
	~
		begin_alloc
		alloc_var Data:MAINSTRUCT
	end_alloc
	
	lea rax,Data
	mov rbx,lpCommunicationObject
	mov [rax].MAINSTRUCT.Object,rbx
	mov rbx,szFname
	mov [rax].MAINSTRUCT.lpFilePath,rbx
	
	GetMainHandle lpCommunicationObject ; Taken the GUI Handle 
	mov rbx,rax
	
	; Creating the Dialog 		
	invoke DialogBoxParam,hInst,IDD_DLGMAIN,rbx,addr DlgProc,addr Data	


exitf

end ;;DllEntry