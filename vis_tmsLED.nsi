; The name of the installer
Name "tmsLED Plug-in"

; The file to write
OutFile "vis_tmsled101.exe"
XPStyle on
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Japanese.nlf"

; License page
LicenseText "vis_tmsLED is Freeware"
LicenseData vis_tmsLED.txt

; The default installation directory
InstallDir $PROGRAMFILES\Winamp
; detect winamp path from uninstall string if available
InstallDirRegKey HKLM \
                 "Software\Microsoft\Windows\CurrentVersion\Uninstall\Winamp" \
                 "UninstallString"

; The text to prompt the user to enter a directory
DirText "Please select your Winamp path below (you will be able to proceed when Winamp is detected):"
;DirShow hide

; automatically close the installer when done.
AutoCloseWindow true
; hide the "show details" box
ShowInstDetails nevershow

Function .onVerifyInstDir
  IfFileExists $INSTDIR\Winamp.exe Good
    Abort
  Good:
FunctionEnd

Function QueryWinampVisPath ; sets $1 with vis path
  StrCpy $1 $INSTDIR\Plugins
  ; use DSPDir instead of VISDir to get DSP plugins directory
  ReadINIStr $9 $INSTDIR\winamp.ini Winamp VisDir 
  StrCmp $9 "" End
  IfFileExists $9 0 End
    StrCpy $1 $9 ; update dir
  End: 
FunctionEnd


; The stuff to install
Section "ThisNameIsIgnoredSoWhyBother?"
  Call QueryWinampVisPath
  SetOutPath $1

  ; File to extract
  File "vis_tmsLED.dll"
  File "vis_tmsLED_skin.zip"
  File "vis_tmsLED.txt"

  ; prompt user, and if they select no, skip the following 3 instructions.
  MessageBox MB_YESNO|MB_ICONQUESTION \
             "The plug-in was installed. Would you like to run Winamp now with tmsLED as the default plug-in?" \
             IDNO NoWinamp
;  MessageBox MB_YESNO|MB_ICONQUESTION \
;             "tmsLEDをインストールしました。tmsLEDをWinampのデフォルトプラグインに選択しますか？" \
;             IDNO NoWinamp
    WriteINIStr "$INSTDIR\Winamp.ini" "Winamp" "visplugin_name" "vis_tmsLED.dll"
    WriteINIStr "$INSTDIR\Winamp.ini" "Winamp" "visplugin_num" "0"
    Exec '"$INSTDIR\Winamp.exe"'
  NoWinamp:
SectionEnd

; eof
