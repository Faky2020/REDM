//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDUIIE.h 
// File Des:�ṩIE����ӿ�
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-7	1.0			   
//--------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		 Dispatch�¼�����,����˵����ο�https://msdn.microsoft.com/en-us/library/aa752084.aspx
	/// </summary>
	class IDMWebEvent
	{
	public:
		virtual HRESULT BeforeNavigate2(DUIWND hWnd, DMIN IDispatch *pDisp, DMIN wchar_t *pUrl,DMIN int Flags,DMIN wchar_t *pTargetFrameName,DMIN wchar_t *pPostData,DMIN wchar_t *pHeaders,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT ClientToHostWindow(DUIWND hWnd, DMIN long *pCx, DMINOUT long *pCy){return S_OK;}
		virtual HRESULT CommandStateChange(DUIWND hWnd, DMIN LONG command, DMIN VARIANT_BOOL enable){return S_OK;}
		virtual HRESULT DocumentComplete(DUIWND hWnd,DMIN IDispatch *pDisp,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT DownloadBegin(DUIWND hWnd){return S_OK;}
		virtual HRESULT DownloadComplete(DUIWND hWnd){return S_OK;}
		virtual HRESULT FileDownload(DUIWND hWnd, DMIN VARIANT_BOOL ActiveDocument,DMINOUT VARIANT_BOOL *Cancel){return S_OK;}
		virtual HRESULT NavigateComplete2(DUIWND hWnd,DMIN IDispatch *pDisp,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT NavigateError(DUIWND hWnd, DMIN IDispatch *pDisp,DMIN wchar_t *pUrl,DMIN wchar_t *pTargetFrameName,DMIN int statusCode,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT NewWindow2(DUIWND hWnd, DMINOUT IDispatch **pDisp,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT NewWindow3(DUIWND hWnd, DMINOUT IDispatch **pDisp,DMINOUT VARIANT_BOOL *bCancel,DMIN DWORD dwFlags,DMIN wchar_t *pUrlContext,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT OnFullScreen(DUIWND hWnd, DMIN VARIANT_BOOL bFullScreen){return S_OK;}
		virtual HRESULT OnMenuBar(DUIWND hWnd, DMIN VARIANT_BOOL bMenuBar){return S_OK;}
		virtual HRESULT OnQuit(DUIWND hWnd){return S_OK;}
		virtual HRESULT OnStatusBar(DUIWND hWnd, DMIN VARIANT_BOOL bStatusBar){return S_OK;}
		virtual HRESULT OnTheaterMode(DUIWND hWnd, DMIN VARIANT_BOOL bTheaterMode){return S_OK;}
		virtual HRESULT OnToolBar(DUIWND hWnd, DMIN VARIANT_BOOL bToolBar){return S_OK;}
		virtual HRESULT OnVisible(DUIWND hWnd, DMIN VARIANT_BOOL bVisible){return S_OK;}
		virtual HRESULT PrintTemplateInstantiation(DUIWND hWnd,DMIN IDispatch *pDisp){return S_OK;}
		virtual HRESULT PrintTemplateTeardown(DUIWND hWnd,DMIN IDispatch *pDisp){return S_OK;}
		virtual HRESULT PrivacyImpactedStateChange(DUIWND hWnd, DMIN VARIANT_BOOL bPrivacyImpacted){return S_OK;}
		virtual HRESULT ProgressChange(DUIWND hWnd, DMIN LONG Progress,DMIN LONG ProgressMax){return S_OK;}
		virtual HRESULT PropertyChange(DUIWND hWnd, DMIN wchar_t *pProperty){return S_OK;}
		virtual HRESULT SetPhishingFilterStatus(DUIWND hWnd, DMIN LONG phishingFilterStatus){return S_OK;}
		virtual HRESULT SetSecureLockIcon(DUIWND hWnd, DMIN int SecureLockIcon){return S_OK;}
		virtual HRESULT StatusTextChange(DUIWND hWnd,DMIN wchar_t *pText){return S_OK;}
		virtual HRESULT TitleChange(DUIWND hWnd, DMIN wchar_t *pText){return S_OK;}
		virtual HRESULT WindowClosing(DUIWND hWnd, DMIN VARIANT_BOOL IsChildWindow,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT WindowSetHeight(DUIWND hWnd, DMIN LONG height){return S_OK;}
		virtual HRESULT WindowSetLeft(DUIWND hWnd, DMIN LONG left){return S_OK;}
		virtual HRESULT WindowSetResizable(DUIWND hWnd, DMIN VARIANT_BOOL bResizable){return S_OK;}
		virtual HRESULT WindowSetTop(DUIWND hWnd, DMIN LONG top){return S_OK;}
		virtual HRESULT WindowSetWidth(DUIWND hWnd, DMIN LONG width){return S_OK;}
		virtual HRESULT WindowStateChanged(DUIWND hWnd, DMIN DWORD dwFlags,DMIN DWORD dwValidFlagsMask){return S_OK;}
		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(DUIWND hWnd, REFIID riid, LPOLESTR* rgszNames,UINT cNames, LCID lcid, DISPID* rgDispId){return E_NOTIMPL;}
		virtual HRESULT STDMETHODCALLTYPE Invoke(DUIWND hWnd, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo,UINT* puArgErr){return E_NOTIMPL;}
	};

	/// <summary>
	///		 IE����ӿ�
	/// </summary>
	class IDUIWeb
	{
	public:
		/// @brief �����¼�������
		/// @param[in]		pEventHandler		�¼�������ָ��
		/// @return HRESULT��S_OK
		virtual HRESULT SetEvtHandler(IDMWebEvent* pEventHandler) = 0;

		/// @brief ��ָ��ҳ��
		/// @param[in]		pszURL		��Ҫ�򿪵�url�ַ���
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT OpenUrl(LPCWSTR pszURL) = 0;

		/// @brief ��ָ��ҳ��
		/// @param[in]		pszURL		���յ�ǰurl���ַ���������
		/// @param[in]		nMaxLen		�ַ�������������󳤶�
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GetUrl(LPWSTR pszUrl, int nMaxLen) = 0;
		virtual CStringW GetUrl() = 0;

		/// @brief ���OLE���ھ��
		/// @return HWND��ʧ��ΪNULL
		virtual HWND GetOleWindow() = 0;

		/// @brief BUSY״̬
		/// @return ture or false
		virtual bool IsBusy() = 0;

		/// @brief ֹͣ
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Stop() = 0;

		/// @brief �ر������
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Quit() = 0;

		/// @brief ˢ��
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Refresh() = 0;

		/// @brief ָ��ˢ�¼���ˢ��
		/// @param[in]		nLevel		ˢ�³����� ���˲������ͣ� REFRESH_NORMAL 0x0 / REFRESH_IFEXPIRED 0x01 / REFRESH_COMPLETELY 0x03
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Refresh2(UINT32 nLevel) = 0;

		/// @brief ����
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GoBack() = 0;

		/// @brief ǰ��
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GoForward() = 0;

		/// @brief �ڵ�ǰ�������������ִ�нű�
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT ExecuteScript(LPCWSTR pszScript) = 0;

		/// @brief ִ��ָ���������ֵĽű�
		/// @param[in]		 strFun			ָ��Ҫ�ű�ִ�еĺ�������
		/// @param[in]		 vecParams		����Ҫ�ű�ִ�еĺ����Ĳ����б�
		/// @param[out]		 strResult		���ؽű�����ִ�еĽ��
		/// @param[in]		 nMaxLen		���ؽű�����ִ�еĽ������������󳤶�
		/// @return HRESULT��ʧ��ΪE_FAIL
		virtual HRESULT ExecuteScriptFuntion(LPCWSTR strFun, const DM::CArray<LPCWSTR>& vecParams, LPWSTR strResult = NULL,int nMaxLen = -1) = 0;

		/// @brief ��ֹ�ű�����
		/// @param[in]		 bDisable		�Ƿ��ֹ
		/// @return HRESULT��ʧ��ΪE_FAIL
		virtual HRESULT DisableScriptWarning(bool bDisable) = 0;

		/// @brief �Ƿ���ʾIE�Ĺ�����
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual void SetScrollBarShow(bool bShow) = 0;

		/// @brief �Ƿ���ʾIE���Ҽ��˵�
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual void SetContextMenuShow(bool bShow) = 0;

		/// @brief ת��DUIIE��SetAttribute
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual DMCode IESetAttribute(LPCWSTR pszAttribute,LPCWSTR pszValue,bool bLoadXml) = 0;					
	};

}