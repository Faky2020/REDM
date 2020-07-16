#pragma once
#include "DMResZipHelper.h"
#include "DMZipHelper.h"
namespace DM
{
	/// <summary>
	///     ����zipʾ�������ô���ļ���һ��
	///		����Res����ļ���Ϊ���½ṹ:�������ò����������󣬿����Լ��޸�һ�ݣ��Լ�ע���ȥ
	///     Res�ļ��а����������ļ��У�1.layout�ļ��� 2.themes�ļ���
	///		1.1.layout�ļ��ж��������в���xml��skin��style��ȫ��xml
	///     2.1.themes�ļ����¶����˶�������
	///     3.ÿ���ļ����¾���һ��dmindex.xml����ʶ��Դ����
	/// </summary>
	class DMResZipImpl:public IDMRes,public DMArrayT<DMZipItemArrayPtr>
	{
		DMDECLARE_CLASS_NAME(DMResZipImpl,"DMResZipImpl",DMREG_Res);
	public:
		DMResZipImpl();
		~DMResZipImpl();
	public:
		virtual DMCode LoadResPack(WPARAM wp, LPARAM lp);
		virtual DMCode IsItemExists(LPCSTR lpszType, LPCSTR lpszName, LPCSTR lpszThemeName = NULL);
		virtual DMCode GetItemSize(LPCSTR lpszType, LPCSTR lpszName, unsigned long& ulSize, LPCSTR lpszThemeName = NULL);
		virtual DMCode GetItemBuf(LPCSTR lpszType, LPCSTR lpszName, DMBufT<byte>&, PULONG lpULSize, LPCSTR lpszThemeName = NULL);
		virtual DMCode LoadTheme(WPARAM wp, LPARAM lp);// ��ʹ�����ַ�ʽ
		virtual DMCode SetCurTheme(LPCSTR lpszName, LPCSTR lpszOldName=NULL);
		virtual DMCode SendExpandInfo(WPARAM wp, LPARAM lp);  ///< lpΪ0ʱ���ѳ��ȸ�ֵ��*wp

	public:// ����
		DMCode ParseThemes(LPCWSTR lpszIndexPath);
		DMCode ParseIndex(LPCWSTR lpszIndexPath,DMZipItemArray** ppItem);
		LPCWSTR GetItemPath(LPCSTR lpszType,LPCSTR lpszName,LPCSTR lpszThemeName);
		DMZipItemArrayPtr FindResItemObj(LPCSTR lpszName);

	public:
		DM_BEGIN_ATTRIBUTES()
			DM_bool_ATTRIBUTE("bloop", m_bThemeLoop, DM_ECODE_OK)
			DM_STRING_ATTRIBUTE("name", m_strCurTheme, DM_ECODE_OK)
			DM_bool_ATTRIBUTE("boutstyle", m_bOutStyle, DM_ECODE_OK)
			DM_bool_ATTRIBUTE("bassert",m_bAssert, DM_ECODE_OK)
		DM_END_ATTRIBUTES()

	protected:
		virtual void PreArrayObjRemove(const DMZipItemArrayPtr &obj);

	protected:
		DM::CStringW                          m_strDir;
		DM::CStringA                          m_strCurTheme;       // ��ǰʹ�õ�theme Key
		DMZipItemArrayPtr					  m_pCurTheme;         // ��ǰʹ�õ�theme
		bool                                  m_bThemeLoop;        // �Ƿ�����ѭ������theme(��ǰtheme���Ҳ�����Դ,ֱ��ȥ����theme�в���)
		bool                                  m_bOutStyle;         // ��ǰ���ⲿģʽ���ⲿǿ�Ƹı���skin�ص����ݣ���ʱ���е�themeӦ�ö���Ҫˢ��)
		DMSmartPtrT<DMZipItemArray>			  m_pLayout;		   // Layout���б�
		CDMZipHelper						  m_zipFile;           // zip����

	public:
		DM::CStringW                          m_strZipKey;         // ��ZIPʱ����ʶΨһ��ZIP
		bool                                  m_bAssert;
	};
	typedef DMResZipImpl* DMResZipImplPtr;


}//namespace DM