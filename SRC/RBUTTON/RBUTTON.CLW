; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRButtonCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rbutton.h"
LastPage=0
CDK=Y

ClassCount=3
Class1=CRButtonCtrl
Class2=CRButtonPropPage

ResourceCount=2
Resource1=IDD_PROPPAGE_RBUTTON (English (U.K.))
Class3=CHintBox
Resource2=IDD_PROPPAGE_RBUTTON

[CLS:CRButtonCtrl]
Type=0
BaseClass=COleControl
HeaderFile=rbuttonc.h
ImplementationFile=Rbuttonc.cpp
LastObject=CRButtonCtrl
Filter=W
VirtualFilter=wWC

[CLS:CRButtonPropPage]
Type=0
BaseClass=COlePropertyPage
HeaderFile=rbuttonp.h
ImplementationFile=rbuttonp.cpp
Filter=D
VirtualFilter=idWC
LastObject=CRButtonPropPage

[DLG:IDD_PROPPAGE_RBUTTON]
Type=1
Class=CRButtonPropPage
ControlCount=14
Control1=IDC_MOVES_PARENT,button,1342242819
Control2=IDC_FONT_NUMBER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CLOSE,button,1342242819
Control5=IDC_TICK,button,1342242819
Control6=IDC_STATIC,button,1342177287
Control7=IDC_DROP_SHADOWS,button,1342242819
Control8=IDC_PRESSED_PICTURE_FILE_NUM,edit,1350631552
Control9=IDC_NORMAL_PICTURE_FILE_NUM,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_UPDATE_CAPTION,button,1342242819
Control13=IDC_PRESSED_PICTURE_FILE_NUM2,edit,1350631552
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_RBUTTON (English (U.K.))]
Type=1
ControlCount=12
Control1=IDC_MOVES_PARENT,button,1342242819
Control2=IDC_FONT_NUMBER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CLOSE,button,1342242819
Control5=IDC_TICK,button,1342242819
Control6=IDC_STATIC,button,1342177287
Control7=IDC_DROP_SHADOWS,button,1342242819
Control8=IDC_PRESSED_PICTURE_FILE_NUM,edit,1350631552
Control9=IDC_NORMAL_PICTURE_FILE_NUM,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_UPDATE_CAPTION,button,1342242819
Class=CRButtonPropPage

[CLS:CHintBox]
Type=0
HeaderFile=HintBox.h
ImplementationFile=HintBox.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC

