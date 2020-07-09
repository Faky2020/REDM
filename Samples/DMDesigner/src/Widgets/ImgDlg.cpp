﻿#include "DMDesignerAfx.h"
#include "ImgDlg.h"

BEGIN_MSG_MAP(ImgDlg)   
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize) 
	MSG_WM_DROPFILES(OnDropFiles)
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP() 
BEGIN_EVENT_MAP(ImgDlg)
	EVENT_NAME_HANDLER("ds_img_bmult",DMEVT_CHECKCHANGING,OnCheckChange)
	EVENT_NAME_HANDLER("ds_img_bvert",DMEVT_CHECKCHANGING,OnCheckChange)
	EVENT_NAME_HANDLER("ds_img_name",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER("ds_img_dir",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER("ds_img_filename",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER("ds_img_fileafx",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_COMMAND("ds_img_save",OnSaveBtn)
	EVENT_NAME_COMMAND("ds_img_clean",OnClearBtn)
	EVENT_NAME_COMMAND("ds_img_opendir",OnOpenDir)
END_EVENT_MAP()
ImgDlg*  ImgDlg::ms_pthis = NULL;
ImgDlg::ImgDlg(bool bEditMode)
{
	m_bEditMode = bEditMode;
	ms_pthis	= this;
	m_pTitle = m_pImgPath = NULL;
	m_pSave = m_pClean = NULL;
	m_pImgEditor = NULL;
	m_pImgName = m_pImgDir = m_pImgFileName = m_pImgFileAfx = NULL;
	m_pXml = NULL;
}
 
BOOL ImgDlg::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	DragAcceptFiles(TRUE);

	//1.更新标题
	m_pTitle = FindChildByNameT<DUIStatic>("ds_title");
	m_strTitle = m_bEditMode?L"[编辑IMG]":L"[新加IMG]";
	m_pTitle->DV_SetWindowText(m_strTitle);

	// 2.初始化控件变量
	m_pImgPath = FindChildByNameT<DUIStatic>("ds_img_path");
	ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
	ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>("ds_projtree");
	m_pImgEditor = FindChildByNameT<DUImgEditor>("ds_img_editor");DMASSERT(m_pImgEditor);
	m_pbMultImg  = FindChildByNameT<DUICheckBox>("ds_img_bmult");DMASSERT(m_pbMultImg);
	m_pbVert     = FindChildByNameT<DUICheckBox>("ds_img_bvert");DMASSERT(m_pbVert);
	m_pSave      = FindChildByNameT<DUIButton>("ds_img_save");DMASSERT(m_pSave);
	m_pClean     = FindChildByNameT<DUIButton>("ds_img_clean");DMASSERT(m_pClean);
	m_pImgName	 = FindChildByNameT<DUIEdit>("ds_img_name");DMASSERT(m_pImgName);
	m_pImgDir	 = FindChildByNameT<DUIEdit>("ds_img_dir");DMASSERT(m_pImgDir);
	m_pImgFileName = FindChildByNameT<DUIEdit>("ds_img_filename");DMASSERT(m_pImgFileName);
	m_pImgFileAfx  = FindChildByNameT<DUIEdit>("ds_img_fileafx");DMASSERT(m_pImgFileAfx);
	m_pXml = FindChildByNameT<DUIRichEdit>("ds_img_xml");DMASSERT(m_pXml);
	m_pImgName->SetEventMask(ENM_CHANGE|m_pImgName->GetEventMask());
	m_pImgDir->SetEventMask(ENM_CHANGE|m_pImgDir->GetEventMask());
	m_pImgFileName->SetEventMask(ENM_CHANGE|m_pImgFileName->GetEventMask());
	m_pImgFileAfx->SetEventMask(ENM_CHANGE|m_pImgFileAfx->GetEventMask());

	// 3.得到主题包的node
	HDMTREEITEM hTheme = NULL;
	if (m_bEditMode)
	{
		HDMTREEITEM h_p = pProjTree->GetParentItem(pXml->m_hProjSel);
		hTheme = pProjTree->GetParentItem(h_p);
	}
	else
	{
		hTheme = pProjTree->GetParentItem(pXml->m_hProjSel);
	}

	DMXmlNodePtr pThemeNode = (DMXmlNodePtr)pProjTree->GetItemData(hTheme);
	m_strDirName = DMA2W(pThemeNode->Attribute(XML_PATH));
	m_strDirName = m_strDirName.Left(m_strDirName.ReverseFind(L'\\')+1);
	m_strDir = pXml->m_strResDir + m_strDirName;
	m_pImgPath->DV_SetWindowText(m_strDirName);

	//3.更新img结点
	DMXmlNode XmlBase = m_ImgDoc.Base();
	m_ImgNode = XmlBase.InsertChildNode(XML_FILE);

	if (m_bEditMode)
	{
		DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		if (pNode)
		{
			// title
			m_pImgName->SetTextA(pNode->Attribute(XML_NAME));
			CStringW strPath = pXml->m_strResDir + DMA2W(pNode->Attribute(XML_PATH));
			m_pTitle->DV_SetWindowText(m_strTitle+strPath);

			// 增加图片
			m_pImgEditor->AddImg(strPath);

			// 图片名+后缀
			CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
			CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
			strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
			m_pImgFileAfx->SetAttribute("text",DMW2A(strFileAfx));m_pImgFileAfx->DM_EnableWindow(false);
			m_pImgFileName->SetAttribute("text",DMW2A(strFileName));m_pImgFileName->DM_EnableWindow(false);
			m_pbMultImg->DM_SetVisible(false,true);

			// 设置目录
			strPath = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
			strPath = strPath.Left(strPath.ReverseFind(L'\\')+1);
			m_pImgDir->SetWindowText(strPath);
			DUIButton* pOpenDir = FindChildByNameT<DUIButton>("ds_img_opendir");
			if (pOpenDir)
			{
				pOpenDir->DM_SetVisible(false,true);
			}

			// img路径
			m_pImgPath->SetAttribute("text",pNode->Attribute(XML_PATH));
		}
	}
	UpdateXml();
	return TRUE;
}   

void ImgDlg::OnSize(UINT nType, CSize size)
{
	if (!IsIconic()) 
	{ 
		CRect rcWnd;
		::GetWindowRect(m_hWnd, &rcWnd);
		::OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);  
		HRGN hWndRgn = ::CreateRoundRectRgn(0, 0, rcWnd.right, rcWnd.bottom,4,4);
		SetWindowRgn(hWndRgn, TRUE);
		::DeleteObject(hWndRgn); 
		if (m_pImgEditor)
		{
			m_pImgEditor->UpdateScrollRangeSize();
		}
	}             
	SetMsgHandled(FALSE);
} 

void ImgDlg::OnDropFiles(HDROP hDropInfo)
{
	do 
	{
		if (m_bEditMode)
		{
			break;
		}
		
		int nDropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
		if (1!=nDropCount)
		{
			break;
		} 

		wchar_t szPath[MAX_PATH] = {0};
		DragQueryFile(hDropInfo, 0, szPath,MAX_PATH);
		if (IsDirectoryExist(szPath))
		{
			DM_MessageBox(L"不支持文件夹",MB_OK,L"MSG",m_hWnd);
			break;
		}
   
		// 更新到右边的显示区
		if (!m_pbMultImg->DM_IsChecked())// 单图模式
		{
			m_pImgEditor->Clear();
			m_pImgEditor->AddImg(szPath);
		}
		else
		{
			m_pImgEditor->AddImg(szPath);
		}

		// 更新到显示区
		CStringW strPath = szPath;
		CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
		CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
		strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
		m_pImgFileAfx->SetAttribute("text",DMW2A(strFileAfx));
		m_pImgFileName->SetAttribute("text", DMW2A(strFileName));
		m_pImgName->SetAttribute("text", DMW2A(strFileName));
		CStringW strTitle;
		strTitle += L"[新加IMG]";
		strTitle += strPath;
		m_pTitle->SetAttribute("text", DMW2A(strTitle));

		// 如果文件路径就在本主题包内，则设置文件夹路径为它原始路径
		bool bMatch = false;
		if (strPath.GetLength()>m_strDir.GetLength())
		{
			CStringW strLeft = strPath.Left(m_strDir.GetLength());
			if (0 == strLeft.CompareNoCase(m_strDir))
			{
				bMatch = true;
			}
		}

		if (bMatch)// 判断原始文件是否就在主题包里，如果在，就设置保持位置不变，当然你也可以自己去改变
		{
			CStringW strDir = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
			strDir = strDir.Left(strDir.ReverseFind(L'\\'));
			m_pImgDir->SetWindowText(strDir);
		}
	} while (false);
}

DMCode ImgDlg::OnCheckChange(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		DMEventCheckChangingCmdArgs* pEvent = (DMEventCheckChangingCmdArgs*)pEvt;
		if (pEvent->m_pSender == m_pbMultImg)
		{
			if (pEvent->m_bChecking)
			{
				m_pbVert->DM_SetVisible(true,true);
				m_pSave->DM_SetVisible(true,true);
				m_pClean->DM_SetVisible(true,true);
			}
			else
			{
				m_pbVert->DM_SetVisible(false,true);
				m_pSave->DM_SetVisible(false,true);
				m_pClean->DM_SetVisible(false,true);
				m_pImgEditor->Clear();
			}
		}
		if (pEvent->m_pSender == m_pbVert)
		{
			m_pImgEditor->SetVert(pEvent->m_bChecking);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::OnEditChange(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		DMEventRENotifyArgs *pEvent = (DMEventRENotifyArgs*)(pEvt);
		if (EN_CHANGE != pEvent->m_iNotify)
		{
			break;
		}

		// 更新下面的显示path
		if (pEvent->m_pSender == m_pImgName
			||pEvent->m_pSender == m_pImgDir
			||pEvent->m_pSender == m_pImgFileName
			||pEvent->m_pSender == m_pImgFileAfx
			)
		{
			CStringW strPath = m_strDirName;
			strPath += m_pImgDir->GetWindowText();
			if (strPath.Right(1)!=L"\\")
			{
				strPath += L"\\";
			}
	
			strPath += m_pImgFileName->GetWindowText();
			strPath += m_pImgFileAfx->GetWindowText();
			m_pImgPath->SetAttribute("text", DMW2A(strPath));

			UpdateXml();
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::OnSaveBtn()
{
	wchar_t szFileTitle[_MAX_FNAME] = {0};  
	wchar_t szFileName[_MAX_PATH]   = {0};
	OPENFILENAMEW ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile	= szFileName;
	ofn.nMaxFile	= _MAX_PATH;
	ofn.lpstrDefExt = L"png";
	ofn.lpstrFileTitle = (LPTSTR)szFileTitle;
	ofn.nMaxFileTitle  = _MAX_FNAME;
	ofn.Flags		   = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.lpstrFilter = L"img files(*.png)\0*.png\0img files(*.jpeg)\0*.jpeg\0img files(*.jpg)\0*.jpg\0img files(*.bmp)\0*.bmp\0\0";
	ofn.hwndOwner = m_hWnd;
	if (0 != ::GetSaveFileNameW(&ofn))
	{
		m_pImgEditor->Save(szFileName);
	}
	
	return DM_ECODE_OK;
}

DMCode ImgDlg::OnClearBtn()
{
	m_pImgEditor->Clear();
	m_pImgName->SetAttribute("text","");
	m_pImgFileName->SetAttribute("text","");
	m_pImgFileAfx->SetAttribute("text","");
	return DM_ECODE_OK;
}

DMCode ImgDlg::OnOpenDir()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		wchar_t path[MAX_PATH] = {0};
		BROWSEINFOW bi = {0};
		//hgy note: BIF_NEWDIALOGSTYLE会影响BFFM_SETSTATUSTEXT无法显示
		bi.ulFlags	 = BIF_STATUSTEXT| BIF_RETURNONLYFSDIRS|BIF_VALIDATE/*|BIF_NEWDIALOGSTYLE*/;
		bi.lpszTitle = L"仅能在当前主题包子目录下选择";
		bi.hwndOwner = m_hWnd;//设置拥有窗口
		bi.lpfn = ImgDlg::BrowseCallbackProc;//指定回调函数地址
		ITEMIDLIST *pIDL = SHBrowseForFolderW(&bi);
		if (pIDL!=NULL)
		{
			if (SHGetPathFromIDListW(pIDL,path) == TRUE) //变量path中存储了经过用户选择后的目录的完整路径.
			{
				CStringW strPath = path;
				strPath = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
				m_pImgDir->SetWindowText(strPath);
			}
			// free memory used   
			IMalloc * imalloc = 0;   
			if (SUCCEEDED(SHGetMalloc( &imalloc)))   
			{   
				imalloc->Free (pIDL);   
				imalloc->Release();   
			}   
		} 

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::UpdateXml()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		CStringW strImgName = m_pImgName->GetWindowText();
		m_ImgNode.SetAttribute(XML_NAME,strImgName);

		CStringW strImgPath = m_pImgPath->m_pDUIXmlInfo->m_strText;
		m_ImgNode.SetAttribute(XML_PATH, strImgPath);

		CStringA strXml;
		m_ImgNode.GetXmlContent(strXml);
		m_pXml->SetTextA(strXml);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

int CALLBACK ImgDlg::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	CStringW strDir = ms_pthis->m_strDir;
	switch (uMsg)
	{
	case BFFM_INITIALIZED:    //初始化消息
		{
			strDir += ms_pthis->m_pImgDir->GetWindowText();
			::SendMessageW(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)(LPWSTR)(LPCWSTR)strDir);  
		}
		break;

	case BFFM_SELCHANGED: //选择路径变化
		{
			wchar_t szPath[MAX_PATH];   
			SHGetPathFromIDListW((LPCITEMIDLIST)lParam,szPath);   
			CStringW strPath = szPath;
			if (strPath.GetLength()<strDir.GetLength())
			{
				strPath = strDir;
			}
			else 
			{
				CStringW strLeft = strPath.Left(strDir.GetLength());
				if (0 != strLeft.CompareNoCase(strDir))
				{
					strPath = strDir;
				}
			}
			::SendMessageW(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)(LPWSTR)(LPCWSTR)strPath); 
			::SendMessageW(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)(LPWSTR)(LPCWSTR)strPath);  
		}
		break;
	default:
		break;
	}

	return 0;
}

DMCode ImgDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
	ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>("ds_projtree");
	do 
	{
		// 1.判断name是否为空，判断本主题包是否已含有此name,注意，并没有判断此文件有没有被其他name占用
		CStringA strImgName = m_pImgName->GetTextA();
		if (strImgName.IsEmpty())
		{
			DM_MessageBox(L"未设置name!",MB_OK, L"MSG",m_hWnd);
			m_pImgName->DV_SetFocusWnd();
			break;
		}

		if (m_bEditMode)// 编辑模式
		{
			DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
			bool bFind = false;
			HDMTREEITEM hParentItem = pProjTree->GetParentItem(pXml->m_hProjSel);
			//2. 判断name是否已存在
			if (hParentItem)
			{
				HDMTREEITEM hChildItem = pProjTree->GetChildItem(hParentItem);
				while (hChildItem)
				{
					if (hChildItem != pXml->m_hProjSel)
					{// 跳过编辑自身
						DMXmlNodePtr pChildNode = (DMXmlNodePtr)pProjTree->GetItemData(hChildItem);
						if (0 == strImgName.CompareNoCase(pChildNode->Attribute(XML_NAME)))
						{
							bFind = true;
							break;
						}
					}
					hChildItem = pProjTree->GetNextSiblingItem(hChildItem);
				}
			}
			if (bFind)
			{
				DM_MessageBox(L"name已存在,请重新设置!",MB_OK,L"MSG",m_hWnd);
				m_pImgName->DV_SetFocusWnd();
				break;
			}
			
			//3.判断名字是否和以前相同，如不同，则设置新名字到pNode中，并设置为未保存状态
			CStringA strOldName = pNode->Attribute(XML_NAME);
			if (0 != strOldName.CompareNoCase(strImgName))
			{
				pNode->SetAttribute(XML_NAME,strImgName);
				pXml->SetDocUnSave(pNode);
			}
			
			iErr = DM_ECODE_OK;
			EndDialog(IDOK);
			break;// 中间跳出，后续为新建模式
		}
		
		DMXmlNodePtr pTypeNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		CStringA strType = pTypeNode->GetName();
		HDMTREEITEM hTheme = pProjTree->GetParentItem(pXml->m_hProjSel);
		DMXmlNodePtr pThemeNode = (DMXmlNodePtr)pProjTree->GetItemData(hTheme);
		CStringA strThemeName = pThemeNode->Attribute(XML_NAME);
		DMAutoResetT<bool> AutoNoLoop(&pXml->m_pRes->m_bThemeLoop,false);// 不遍历其他主题包查找
		if (DMSUCCEEDED(pXml->m_pRes->IsItemExists(strType,strImgName,strThemeName)))
		{
			DM_MessageBox(L"本主题包已存在此name!",MB_OK, L"MSG",m_hWnd);
			m_pImgName->DV_SetFocusWnd();
			break;
		}
		//2.判断目录文件名是否为空，判断是否没有拖入文件
		CStringW strImgFileName = m_pImgFileName->GetWindowText();
		if (strImgFileName.IsEmpty())
		{
			DM_MessageBox(L"文件名为空!",MB_OK, L"MSG",m_hWnd);
			m_pImgFileName->DV_SetFocusWnd();
			break;
		}

		CStringW strImgSrc = m_pTitle->m_pDUIXmlInfo->m_strText;
		strImgSrc = strImgSrc.Right(strImgSrc.GetLength()-7);//L"[新加IMG]";
		if (!PathFileExistsW(strImgSrc))//说明没有拖入文件
		{
			DM_MessageBox(L"未拖入文件!",MB_OK, L"MSG",m_hWnd);
			break;
		}
		
		// 3.保存图片,如果是多个图片（注意是多图片，比如你拖入一个png，一个xml，那也只有一个图片），就以多图片直接保存成(格式由最后一张图片的后缀)，如果是单图片，那么就采用单文件同样的方式，直接拷贝
		CStringW strPath = pXml->m_strResDir + DMA2W(m_ImgNode.Attribute(XML_PATH));
		if (m_pbMultImg->DM_IsChecked() && m_pImgEditor->GetImgCount()>1)// 多图片组合
		{
			m_pImgEditor->Save(strPath);
		}
		else
		{
			CStringW strImgSrc = m_pTitle->m_pDUIXmlInfo->m_strText;
			strImgSrc = strImgSrc.Right(strImgSrc.GetLength()-7);//L"[新加IMG]";
			if (!PathFileExistsW(strImgSrc))
			{
				DM_MessageBox(L"文件不存在!",MB_OK, L"MSG",m_hWnd);
			}
			CopyFileW(strImgSrc,strPath,FALSE);
		}

		//4.加入Res解析器中
		if (!DMSUCCEEDED(pXml->m_pRes->AddResItem(strType,strImgName,strPath,strThemeName)))
		{
			DM_MessageBox(L"加入Res失败!",MB_OK, L"MSG",m_hWnd);
			break;
		}

		//5.写入xml中
		DMXmlNode XmlNode = pTypeNode->InsertCopyChildNode(&m_ImgNode);

		//6.增加树形结点
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		pXml->InitProjTreeNode(DataNode,true);
		CStringW strName = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'\\')-1);
		hAdd = pXml->InsertProjTreeItem(DataNode,strName,pXml->m_hProjSel);
		pXml->BindProjTreeData(XmlNode,hAdd);

		//7.设置xml为未保存状态
		pXml->SetDocUnSave(pTypeNode);

		EndDialog(IDOK);
		if (hAdd)
		{
			pProjTree->SelectItem(hAdd);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

