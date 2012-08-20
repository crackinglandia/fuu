; $Id: installer.nsi 68 2010-07-13 16:08:16Z nahuelriva $

;FUU v0.1.1 Installer
;Written by +NCR/CRC! [ReVeRsEr]

  !include "MUI2.nsh"

  Name "FUU v0.1.1 Beta"
  OutFile "FUUv0.1.1b.exe"

  CRCCheck on
  XPStyle  on
  
  ;Default installation folder
  InstallDir "$PROGRAMFILES\FUU v0.1.1b"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\FUU" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

  !define MUI_ABORTWARNING

  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "Software\FUU" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\FUU\LICENSE"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

  !insertmacro MUI_LANGUAGE "English" ;first language is the default language
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_LANGUAGE "German"
  !insertmacro MUI_LANGUAGE "Spanish"
  !insertmacro MUI_LANGUAGE "SpanishInternational"
  !insertmacro MUI_LANGUAGE "SimpChinese"
  !insertmacro MUI_LANGUAGE "TradChinese"
  !insertmacro MUI_LANGUAGE "Japanese"
  !insertmacro MUI_LANGUAGE "Korean"
  !insertmacro MUI_LANGUAGE "Italian"
  !insertmacro MUI_LANGUAGE "Dutch"
  !insertmacro MUI_LANGUAGE "Danish"
  !insertmacro MUI_LANGUAGE "Swedish"
  !insertmacro MUI_LANGUAGE "Norwegian"
  !insertmacro MUI_LANGUAGE "NorwegianNynorsk"
  !insertmacro MUI_LANGUAGE "Finnish"
  !insertmacro MUI_LANGUAGE "Greek"
  !insertmacro MUI_LANGUAGE "Russian"
  !insertmacro MUI_LANGUAGE "Portuguese"
  !insertmacro MUI_LANGUAGE "PortugueseBR"
  !insertmacro MUI_LANGUAGE "Polish"
  !insertmacro MUI_LANGUAGE "Ukrainian"
  !insertmacro MUI_LANGUAGE "Czech"
  !insertmacro MUI_LANGUAGE "Slovak"
  !insertmacro MUI_LANGUAGE "Croatian"
  !insertmacro MUI_LANGUAGE "Bulgarian"
  !insertmacro MUI_LANGUAGE "Hungarian"
  !insertmacro MUI_LANGUAGE "Thai"
  !insertmacro MUI_LANGUAGE "Romanian"
  !insertmacro MUI_LANGUAGE "Latvian"
  !insertmacro MUI_LANGUAGE "Macedonian"
  !insertmacro MUI_LANGUAGE "Estonian"
  !insertmacro MUI_LANGUAGE "Turkish"
  !insertmacro MUI_LANGUAGE "Lithuanian"
  !insertmacro MUI_LANGUAGE "Slovenian"
  !insertmacro MUI_LANGUAGE "Serbian"
  !insertmacro MUI_LANGUAGE "SerbianLatin"
  !insertmacro MUI_LANGUAGE "Arabic"
  !insertmacro MUI_LANGUAGE "Farsi"
  !insertmacro MUI_LANGUAGE "Hebrew"
  !insertmacro MUI_LANGUAGE "Indonesian"
  !insertmacro MUI_LANGUAGE "Mongolian"
  !insertmacro MUI_LANGUAGE "Luxembourgish"
  !insertmacro MUI_LANGUAGE "Albanian"
  !insertmacro MUI_LANGUAGE "Breton"
  !insertmacro MUI_LANGUAGE "Belarusian"
  !insertmacro MUI_LANGUAGE "Icelandic"
  !insertmacro MUI_LANGUAGE "Malay"
  !insertmacro MUI_LANGUAGE "Bosnian"
  !insertmacro MUI_LANGUAGE "Kurdish"
  !insertmacro MUI_LANGUAGE "Irish"
  !insertmacro MUI_LANGUAGE "Uzbek"
  !insertmacro MUI_LANGUAGE "Galician"
  !insertmacro MUI_LANGUAGE "Afrikaans"
  !insertmacro MUI_LANGUAGE "Catalan"
  !insertmacro MUI_LANGUAGE "Esperanto"
  
  !insertmacro MUI_RESERVEFILE_LANGDLL

Section "FUU v0.1.1b" MainFUUFiles

  SetOutPath "$INSTDIR\bin"
  
  CreateDirectory "$SMPROGRAMS\FUU v0.1.1b"
  CreateShortCut "$SMPROGRAMS\FUU v0.1.1b\FUU v0.1.1b.lnk" \
				 "$INSTDIR\bin\fuu.exe"
  
  CreateShortCut "$SMPROGRAMS\FUU v0.1.1b\Uninstall FUUv0.1.1b.lnk" \
				 "$INSTDIR\uninstall.exe"

  CreateShortCut "$SMPROGRAMS\FUU v0.1.1b\Readme.lnk" \
				 "$INSTDIR\readme.txt"

  CreateShortCut "$SMPROGRAMS\FUU v0.1.1b\Changelog.lnk" \
				 "$INSTDIR\changelog.txt"

  CreateShortCut "$SMPROGRAMS\FUU v0.1.1b\LICENSE.lnk" \
				 "$INSTDIR\LICENSE"
				 
  File fuu.exe
  
  ;Store installation folder
  WriteRegStr HKCU "Software\FUU" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  SetOutPath "$INSTDIR"
  
  File changelog.txt
  File readme.txt
  File LICENSE
  
  Exec "explorer $SMPROGRAMS\FUU v0.1.1b\"
SectionEnd

Section "Plugins" Plugins
	SetOutPath "$INSTDIR\bin\Plugins\x86"
	
	CreateDirectory "$INSTDIR\bin\Plugins\x86"
	
	File upx_unpacker.dll
	File UnPackman.dll
	File UnnPack.dll
	File UnDePack.dll
	File TitanEngine.dll
	File fsg_unpacker.dll
	File BeRoExeUnpacker.dll
	File aspack_unpacker.dll
	
	SetOutPath "$INSTDIR\bin\Plugins"
	
	File LICENSE
	
SectionEnd

Section "Tools" Tools
	SetOutPath "$INSTDIR\bin\Tools"
	
	CreateDirectory "$INSTDIR\bin\Tools"
	
	File ZDRx.dll
	File kanal.dll
	File ImpREC.dll
	File GenOEP.dll
	File Detect_Signatures.dll
	
	SetOutPath "$INSTDIR\bin\Tools\Signaturesdb"
	
	File signatures.txt
	
SectionEnd

Section "Sample Plugin" Samples
	SetOutPath "$INSTDIR\docs\SamplePlugin"
	
	CreateDirectory "$INSTDIR\docs\SamplePlugin"
	
	File TitaniumHooks_x86.dll
	File TitanEngine_x86.lib
	File TitanEngine.dll
	File SDK.INC
	File SamplePlugin.rap
	File SamplePlugin.Inc
	File SamplePlugin.dll
	File SamplePlugin.Def
	File SamplePlugin.Asm
	
SectionEnd

Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${MainFUUFiles} "Main Files for FUU"
	!insertmacro MUI_DESCRIPTION_TEXT ${Plugins} "FUU Unpacker Plugins"
	!insertmacro MUI_DESCRIPTION_TEXT ${Tools} "Extra tools for FUU"
	!insertmacro MUI_DESCRIPTION_TEXT ${Samples} "Sample Plugin for FUU"
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

Section "Uninstall"

  RMDir /r "$SMPROGRAMS\FUU v0.1.1b"
  RMDir /r "$INSTDIR"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\FUU"

SectionEnd

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd