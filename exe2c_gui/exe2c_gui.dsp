# Microsoft Developer Studio Project File - Name="exe2c_gui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=exe2c_gui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "exe2c_gui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "exe2c_gui.mak" CFG="exe2c_gui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "exe2c_gui - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "exe2c_gui - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "exe2c_gui - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../BIN/exe2c_gui.exe"

!ELSEIF  "$(CFG)" == "exe2c_gui - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../BIN/exe2c_gui.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "exe2c_gui - Win32 Release"
# Name "exe2c_gui - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ButtonBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Change.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CMyString.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\cplusplus.cpp
# End Source File
# Begin Source File

SOURCE=.\CRorEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\CRorTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CRorTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CRorTextView2.cpp
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CXmlList.cpp
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CXmlPrt.cpp
# End Source File
# Begin Source File

SOURCE=.\exe2c_gui.cpp
# End Source File
# Begin Source File

SOURCE=.\exe2c_gui.rc
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ViewFunDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\XmlType.cpp
# End Source File
# Begin Source File

SOURCE=..\BIN\exe2c.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ButtonBar.h
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\Change.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CMyString.h
# End Source File
# Begin Source File

SOURCE=.\CommandDlg.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CRorEditView.h
# End Source File
# Begin Source File

SOURCE=.\CRorEditView.inl
# End Source File
# Begin Source File

SOURCE=.\CRorTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CRorTextBuffer.inl
# End Source File
# Begin Source File

SOURCE=.\CRorTextView.h
# End Source File
# Begin Source File

SOURCE=.\CRorTextView.inl
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CXmlList.h
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\CXmlPrt.h
# End Source File
# Begin Source File

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=..\exe2c\exe2c.H
# End Source File
# Begin Source File

SOURCE=.\exe2c_gui.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyLog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\SampleView.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ViewFunDlg.h
# End Source File
# Begin Source File

SOURCE=..\exe2c\SRC\XMLTYPE.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sample.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sample.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SampleDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
