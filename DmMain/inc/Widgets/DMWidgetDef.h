//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMWidgetDef.h 
// File Des: ���ÿؼ��ļ򵥶���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-9	1.0			
//--------------------------------------------------------
#pragma once

namespace DM
{
// ----------------------------------------------------
// ���ô��ڶ���
#define      DUINAME_Label     "label"                       // DUI Label
#define      DUINAME_Group      "group"                        // DUI Group
#define      DUINAME_CheckBox   "checkbox"                     // DUI CheckBox
#define      DUINAME_Link       "link"                         // DUI Link
#define      DUINAME_ComboxBox  "combobox"                     // DUI Combobox
#define      DUINAME_Button     "button"                       // DUI Button
#define      DUINAME_HotKey     "hotkey"                       // DUI HotKey
#define      DUINAME_IPEdit	    "ipedit"						// DUI IPEdit
#define      DUINAME_IPAddress  "ipaddress"                    // DUI IPAddress
#define      DUINAME_RadioButton "radiobutton"					// DUI RadioButton
#define      DUINAME_SliderCtrl "sliderctrl"					// DUI SliderCtrl
#define      DUINAME_ProcessCtrl "processctrl"					// DUI ProcessCtrl
#define      DUINAME_TabCtrl    "tabctrl"                      // DUI TabCtrl
#define      DUINAME_TabPage    "tabpage"                      // DUI TabPage
#define      DUINAME_TabAnimate "tabanimate"                   // DUI TabAnimate
#define      DUINAME_ActiveX    "activex"                      // DUI ActiveX
#define      DUINAME_Flash      "flash"                        // DUI Flash
#define      DUINAME_IE         "ie"                           // DUI IE
#define      DUINAME_ScrollBar  "scrollbar"                    // DUI ScrollBar
#define      DUINAME_Panel	    "panel"                        // DUI Panel
#define      DUINAME_ScrollView	"scrollview"                   // DUI ScrollView
#define      DUINAME_RichEdit	"richedit"                     // DUI RichEdit
#define      DUINAME_Edit	    "edit"                         // DUI Edit
#define      DUINAME_ListCtrl	"listctrl"                     // DUI ListCtrl
#define      DUINAME_ListBox	"listbox"                      // DUI ListBox
#define      DUINAME_ListBoxEx	"listboxex"                    // DUI ListBoxEx
#define      DUINAME_TreeCtrl	"treectrl"                     // DUI TreeCtrl
#define      DUINAME_TreeCtrlEx	"treectrlex"                   // DUI TreeCtrlEx
#define      DUINAME_HeaderCtrl	"headerctrl"                   // DUI HeaderCtrl
#define      DUINAME_ListCtrlEx	"listctrlex"                   // DUI ListCtrlEx
#define      DUINAME_Gif     	"gif"                          // DUI Gif
#define      DUINAME_ScrollBase "scrollbase"                   // DUI ScrollBase
#define      DUINAME_ScrollWnd  "scrollwnd"                    // DUI ScrollWnd
#define      DUINAME_ScrollFL   "scrollfl"                     // DUI ScrollFL
#define      DUINAME_MonthCalCtrl "monthcalctrl"				// DUI MonthCalCtrl
#define      DUINAME_DateTimeCtrl "datetimectrl"				// DUI DateTimeCtrl
#define      DUINAME_RectTracker  "recttracker"				// DUI RectTracker


// ----------------------------------------------------
// scroll
// ״̬:������ͣ������������á���Active
#define    DMSBST_NORMAL                             0							///< ����״̬
#define    DMSBST_HOVER                              1							///< hover״̬
#define    DMSBST_PUSHDOWN                           2							///< ����״̬
#define    DMSBST_DISABLE                            3							///< ����״̬
#define    DMSBST_NOACTIVE							 4							///< �Ǽ���״̬

// ��������ʾ״̬
#define	   DMSB_NULL								 0
#define	   DMSB_HORZ								 1
#define	   DMSB_VERT								 2
#define	   DMSB_BOTH								(DMSB_HORZ|DMSB_VERT)

struct SBSTATEINFO
{
	SBSTATEINFO()
	{
		sbCode = -1;
		nState = 0;
		bVert  = false;
	}
	SBSTATEINFO(LONG obj)
	{
		memcpy(this,&obj,4);
	}
	bool operator !=(const SBSTATEINFO &obj)
	{
		return memcmp(this,&obj,sizeof(SBSTATEINFO))!=0;
	}
	LONG sbCode:16;
	LONG nState:8;
	bool bVert :8;
};

// �ؼ�:�ϼ�ͷ���¼�ͷ����ֱ����������ֱ���ۡ����ͷ���Ҽ�ͷ��ˮƽ��������ˮƽ���ۡ�С�߽�
#define    SB_CORNOR								10
#define    MAKESBSTATE(sbCode,nState,bVert)         MAKELONG((sbCode),MAKEWORD((nState),(bVert)))
#define	   TIMER_SBWAIT								1         // �������������Ķ�ʱ��
#define    TIMER_SBGO								2         // ���������Ķ�ʱ��
}// namespace DM