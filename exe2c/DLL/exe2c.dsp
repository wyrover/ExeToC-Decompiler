# Microsoft Developer Studio Project File - Name="exe2c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=exe2c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "exe2c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "exe2c.mak" CFG="exe2c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "exe2c - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "exe2c - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "exe2c - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../../BIN/exe2c.dll"

!ELSEIF  "$(CFG)" == "exe2c - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../../BIN/exe2c.dll" /implib:"../../BIN/exe2c.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "exe2c - Win32 Release"
# Name "exe2c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DLL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\exe2c.def
# End Source File
# Begin Source File

SOURCE=.\exe2c_DLL.cpp
# End Source File
# Begin Source File

SOURCE=.\exe2c_DLL.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "LibScanner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SRC\CLibScanner.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CLibScanner.H
# End Source File
# Begin Source File

SOURCE=..\LibScanner.H
# End Source File
# End Group
# Begin Source File

SOURCE=..\SRC\00000.h
# End Source File
# Begin Source File

SOURCE=..\SRC\analysis.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CApiManage.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CApiManage.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CCbuf.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCbuf.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CClassManage.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CClassManage.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CCodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCodeList.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CEnumMng.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CEnumMng.h
# End Source File
# Begin Source File

SOURCE=..\SRC\Cexe2c.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\Cexe2c.H
# End Source File
# Begin Source File

SOURCE=..\SRC\CExprManage.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CExprManage.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFunc.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CFunc_CreateInstrList.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFuncOptim.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFuncPrt.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFuncStep1.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFuncType.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFuncType.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CISC.H
# End Source File
# Begin Source File

SOURCE=..\SRC\CMyString.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMyString.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CNameID.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNameID.h
# End Source File
# Begin Source File

SOURCE=..\SRC\ComplexInstr.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\ComplexInstr.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CStrategy.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CXmlList.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CXmlList.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CXmlPrt.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CXmlPrt.h
# End Source File
# Begin Source File

SOURCE=..\SRC\dasm.h
# End Source File
# Begin Source File

SOURCE=..\SRC\DataType.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DataType.h
# End Source File
# Begin Source File

SOURCE=..\SRC\Deasm_Init.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\Disasm.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DLL32DEF.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DLL32DEF.h
# End Source File
# Begin Source File

SOURCE=..\SRC\enum.h
# End Source File
# Begin Source File

SOURCE=..\SRC\exe2c.cpp
# End Source File
# Begin Source File

SOURCE=.\exe2c_DLL.rc
# End Source File
# Begin Source File

SOURCE=..\SRC\EXPR.h
# End Source File
# Begin Source File

SOURCE=..\SRC\FileLoad.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\FileLoad.h
# End Source File
# Begin Source File

SOURCE=..\SRC\hpp.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\hpp.h
# End Source File
# Begin Source File

SOURCE=..\SRC\INSTR.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\INSTR.h
# End Source File
# Begin Source File

SOURCE=..\SRC\main.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\mylist.h
# End Source File
# Begin Source File

SOURCE=..\SRC\optim.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\PEload.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\proto.h
# End Source File
# Begin Source File

SOURCE=..\SRC\PUB.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\standard.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\standard.h
# End Source File
# Begin Source File

SOURCE=..\SRC\strparse.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\strparse.h
# End Source File
# Begin Source File

SOURCE=..\SRC\SVarType.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SVarType.h
# End Source File
# Begin Source File

SOURCE=..\SRC\XmlType.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\XMLTYPE.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\SRC\CFuncStep1.h
# End Source File
# Begin Source File

SOURCE=..\SRC\CStrategy.h
# End Source File
# Begin Source File

SOURCE=..\exe2c.H
# End Source File
# Begin Source File

SOURCE=..\..\I_KSUNKNOWN\KsFrame.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\SRC\me.txt
# End Source File
# End Target
# End Project
