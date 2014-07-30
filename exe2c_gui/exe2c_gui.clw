; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sample.h"
LastPage=0

ClassCount=20
Class1=CButtonBar
Class2=CCrystalEditView
Class3=CCrystalTextBuffer
Class4=CCrystalTextView
Class5=CChange
Class6=CChildFrame
Class7=CChildView
Class8=CCoolTabCtrl
Class9=CMainFrame
Class10=CSampleApp
Class11=CAboutDlg
Class12=CSampleDoc
Class13=CSampleDocA
Class14=CSampleView
Class15=CCoolBar
Class16=CSizingControlBar
Class17=CSCBMiniDockFrameWnd
Class18=CViewFunDlg

ResourceCount=11
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_VIEW2_TMP
Resource3=IDD_DIALOG2
Resource4=IDD_COMMAND
Resource5=IDR_SAMPLETYPE (English (U.S.))
Resource6=IDD_DIALOGBAR1
Resource7=IDD_DIALOG4
Class19=CMyLog
Resource8=IDD_DIALOGBAR2
Class20=CLog
Resource9=IDD_DIALOGBAR3 (English (U.S.))
Resource10=IDD_DIALOG1
Resource11=IDR_MAINFRAME (English (U.S.))

[CLS:CButtonBar]
Type=0
BaseClass=CDialogBar
HeaderFile=ButtonBar.h
ImplementationFile=ButtonBar.cpp

[CLS:CCrystalEditView]
Type=0
BaseClass=CCrystalTextView
HeaderFile=CCrystalEditView.h
ImplementationFile=CCrystalEditView.cpp

[CLS:CCrystalTextBuffer]
Type=0
BaseClass=CCmdTarget
HeaderFile=CCrystalTextBuffer.h
ImplementationFile=CCrystalTextBuffer.cpp

[CLS:CCrystalTextView]
Type=0
BaseClass=CView
HeaderFile=CCrystalTextView.h
ImplementationFile=CCrystalTextView.cpp

[CLS:CChange]
Type=0
BaseClass=CDialog
HeaderFile=Change.h
ImplementationFile=Change.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CCoolTabCtrl]
Type=0
BaseClass=CWnd
HeaderFile=CoolTabCtrl.h
ImplementationFile=CoolTabCtrl.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=IDD_VIEW_COMMAND

[CLS:CSampleApp]
Type=0
BaseClass=CWinApp
HeaderFile=Sample.h
ImplementationFile=Sample.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Sample.cpp
ImplementationFile=Sample.cpp
LastObject=CAboutDlg

[CLS:CSampleDoc]
Type=0
BaseClass=CDocument
HeaderFile=SampleDoc.h
ImplementationFile=SampleDoc.cpp

[CLS:CSampleDocA]
Type=0
BaseClass=CDocument
HeaderFile=SampleDocA.h
ImplementationFile=SampleDocA.cpp

[CLS:CSampleView]
Type=0
BaseClass=CCrystalEditView
HeaderFile=SampleView.h
ImplementationFile=SampleView.cpp

[CLS:CCoolBar]
Type=0
BaseClass=baseCCoolBar
HeaderFile=scbarg.h
ImplementationFile=scbarg.cpp
LastObject=ID_APP_ABOUT
Filter=N

[CLS:CSizingControlBar]
Type=0
BaseClass=baseCSizingControlBar
HeaderFile=sizecbar.h
ImplementationFile=sizecbar.cpp

[CLS:CSCBMiniDockFrameWnd]
Type=0
BaseClass=baseCSCBMiniDockFrameWnd
HeaderFile=sizecbar.h
ImplementationFile=sizecbar.cpp

[CLS:CViewFunDlg]
Type=0
BaseClass=CDialog
HeaderFile=ViewFunDlg.h
ImplementationFile=ViewFunDlg.cpp

[DLG:IDD_DIALOGBAR1]
Type=1
Class=CButtonBar
ControlCount=3
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_BUTTON3,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CChange
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[DLG:IDD_DIALOG2]
Type=1
Class=CLog
ControlCount=1
Control1=IDC_EDIT3,edit,1353781444

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DIALOGBAR2]
Type=1
Class=CViewFunDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_SAMPLETYPE (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PAGE_SETUP
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_REDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_DELETE
Command17=ID_EDIT_SELECT_ALL
Command18=ID_EDIT_FIND
Command19=ID_EDIT_REPEAT
Command20=ID_EDIT_FIND_PREVIOUS
Command21=ID_EDIT_REPLACE
Command22=ID_READ_ONLY
Command23=ID_EDIT_CLEAR_BOOKMARKS
Command24=ID_EDIT_TOGGLE_BOOKMARK0
Command25=ID_EDIT_TOGGLE_BOOKMARK1
Command26=ID_EDIT_TOGGLE_BOOKMARK2
Command27=ID_EDIT_TOGGLE_BOOKMARK3
Command28=ID_EDIT_TOGGLE_BOOKMARK4
Command29=ID_EDIT_TOGGLE_BOOKMARK5
Command30=ID_EDIT_TOGGLE_BOOKMARK6
Command31=ID_EDIT_TOGGLE_BOOKMARK7
Command32=ID_EDIT_TOGGLE_BOOKMARK8
Command33=ID_EDIT_TOGGLE_BOOKMARK9
Command34=ID_EDIT_GO_BOOKMARK0
Command35=ID_EDIT_GO_BOOKMARK1
Command36=ID_EDIT_GO_BOOKMARK2
Command37=ID_EDIT_GO_BOOKMARK3
Command38=ID_EDIT_GO_BOOKMARK4
Command39=ID_EDIT_GO_BOOKMARK5
Command40=ID_EDIT_GO_BOOKMARK6
Command41=ID_EDIT_GO_BOOKMARK7
Command42=ID_EDIT_GO_BOOKMARK8
Command43=ID_EDIT_GO_BOOKMARK9
Command44=ID_EDIT_TOGGLE_BOOKMARK
Command45=ID_EDIT_GOTO_NEXT_BOOKMARK
Command46=ID_EDIT_GOTO_PREV_BOOKMARK
Command47=ID_EDIT_CLEAR_ALL_BOOKMARKS
Command48=ID_EDIT_DISABLEBSATSOL
Command49=ID_EDIT_DISABLEDRAGANDDROP
Command50=ID_VIEW_TOOLBAR
Command51=ID_VIEW_STATUS_BAR
Command52=ID_VIEW_FORM1
Command53=ID_VIEW_FORM2
Command54=ID_LOG2
Command55=IDD_VIEW_FUN
Command56=IDD_VIEW_COMMAND
Command57=ID_WINDOW_NEW
Command58=ID_WINDOW_CASCADE
Command59=ID_WINDOW_TILE_HORZ
Command60=ID_WINDOW_ARRANGE
Command61=ID_APP_ABOUT
CommandCount=61

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PAGE_SETUP
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_REDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_DELETE
Command17=ID_EDIT_SELECT_ALL
Command18=ID_EDIT_FIND
Command19=ID_EDIT_REPEAT
Command20=ID_EDIT_FIND_PREVIOUS
Command21=ID_EDIT_REPLACE
Command22=ID_READ_ONLY
Command23=ID_EDIT_CLEAR_BOOKMARKS
Command24=ID_EDIT_TOGGLE_BOOKMARK0
Command25=ID_EDIT_TOGGLE_BOOKMARK1
Command26=ID_EDIT_TOGGLE_BOOKMARK2
Command27=ID_EDIT_TOGGLE_BOOKMARK3
Command28=ID_EDIT_TOGGLE_BOOKMARK4
Command29=ID_EDIT_TOGGLE_BOOKMARK5
Command30=ID_EDIT_TOGGLE_BOOKMARK6
Command31=ID_EDIT_TOGGLE_BOOKMARK7
Command32=ID_EDIT_TOGGLE_BOOKMARK8
Command33=ID_EDIT_TOGGLE_BOOKMARK9
Command34=ID_EDIT_GO_BOOKMARK0
Command35=ID_EDIT_GO_BOOKMARK1
Command36=ID_EDIT_GO_BOOKMARK2
Command37=ID_EDIT_GO_BOOKMARK3
Command38=ID_EDIT_GO_BOOKMARK4
Command39=ID_EDIT_GO_BOOKMARK5
Command40=ID_EDIT_GO_BOOKMARK6
Command41=ID_EDIT_GO_BOOKMARK7
Command42=ID_EDIT_GO_BOOKMARK8
Command43=ID_EDIT_GO_BOOKMARK9
Command44=ID_EDIT_TOGGLE_BOOKMARK
Command45=ID_EDIT_GOTO_NEXT_BOOKMARK
Command46=ID_EDIT_GOTO_PREV_BOOKMARK
Command47=ID_EDIT_CLEAR_ALL_BOOKMARKS
Command48=ID_EDIT_DISABLEBSATSOL
Command49=ID_EDIT_DISABLEDRAGANDDROP
Command50=ID_VIEW_TOOLBAR
Command51=ID_VIEW_STATUS_BAR
Command52=ID_VIEW_FORM1
Command53=ID_VIEW_FORM2
Command54=ID_WINDOW_NEW
Command55=ID_WINDOW_CASCADE
Command56=ID_WINDOW_TILE_HORZ
Command57=ID_WINDOW_ARRANGE
Command58=ID_APP_ABOUT
CommandCount=58

[MNU:IDR_VIEW2_TMP]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PAGE_SETUP
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_REDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_DELETE
Command17=ID_EDIT_SELECT_ALL
Command18=ID_EDIT_FIND
Command19=ID_EDIT_REPEAT
Command20=ID_EDIT_FIND_PREVIOUS
Command21=ID_EDIT_REPLACE
Command22=ID_READ_ONLY
Command23=ID_EDIT_CLEAR_BOOKMARKS
Command24=ID_EDIT_TOGGLE_BOOKMARK0
Command25=ID_EDIT_TOGGLE_BOOKMARK1
Command26=ID_EDIT_TOGGLE_BOOKMARK2
Command27=ID_EDIT_TOGGLE_BOOKMARK3
Command28=ID_EDIT_TOGGLE_BOOKMARK4
Command29=ID_EDIT_TOGGLE_BOOKMARK5
Command30=ID_EDIT_TOGGLE_BOOKMARK6
Command31=ID_EDIT_TOGGLE_BOOKMARK7
Command32=ID_EDIT_TOGGLE_BOOKMARK8
Command33=ID_EDIT_TOGGLE_BOOKMARK9
Command34=ID_EDIT_GO_BOOKMARK0
Command35=ID_EDIT_GO_BOOKMARK1
Command36=ID_EDIT_GO_BOOKMARK2
Command37=ID_EDIT_GO_BOOKMARK3
Command38=ID_EDIT_GO_BOOKMARK4
Command39=ID_EDIT_GO_BOOKMARK5
Command40=ID_EDIT_GO_BOOKMARK6
Command41=ID_EDIT_GO_BOOKMARK7
Command42=ID_EDIT_GO_BOOKMARK8
Command43=ID_EDIT_GO_BOOKMARK9
Command44=ID_EDIT_TOGGLE_BOOKMARK
Command45=ID_EDIT_GOTO_NEXT_BOOKMARK
Command46=ID_EDIT_GOTO_PREV_BOOKMARK
Command47=ID_EDIT_CLEAR_ALL_BOOKMARKS
Command48=ID_EDIT_DISABLEBSATSOL
Command49=ID_EDIT_DISABLEDRAGANDDROP
Command50=ID_VIEW_TOOLBAR
Command51=ID_VIEW_STATUS_BAR
Command52=ID_VIEW_FORM1
Command53=ID_VIEW_FORM2
Command54=ID_WINDOW_NEW
Command55=ID_WINDOW_CASCADE
Command56=ID_WINDOW_TILE_HORZ
Command57=ID_WINDOW_ARRANGE
Command58=ID_APP_ABOUT
CommandCount=58

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_OPTIM
Command2=ID_APP_EXIT
CommandCount=2

[CLS:CMyLog]
Type=0
HeaderFile=MyLog.h
ImplementationFile=MyLog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyLog
VirtualFilter=dWC

[DLG:IDD_DIALOG4]
Type=1
Class=CLog
ControlCount=1
Control1=IDC_EDIT1,edit,1353781444

[CLS:CLog]
Type=0
HeaderFile=Log.h
ImplementationFile=Log.cpp
BaseClass=CDialog
Filter=D
LastObject=CLog
VirtualFilter=dWC

[DLG:IDD_COMMAND]
Type=1
Class=?
ControlCount=1
Control1=IDC_COMMAND,edit,1350631552

[DLG:IDD_DIALOGBAR3 (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT1,edit,1353783492

