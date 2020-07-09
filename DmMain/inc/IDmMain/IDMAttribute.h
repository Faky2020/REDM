//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMAttribute.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-10	1.0			
//-------------------------------------------------------
#pragma once
namespace DM
{
	/// <summary>
	///		XML���Խ�������չ�ӿ�,classtype=<see cref="DMREG_Attribute"/>
	/// </summary>
	/// <remarks>
	///     ���ʹ���߾���ϣ�������Լ��ķ�ʽ����XML,��ô��������!
	/// </remarks>
	class IDMAttribute:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMAttribute,"IDMAttribute",DMREG_Attribute);
	public:
		virtual DMCode ParseInt(LPCSTR lpszValue,int&Obj) = 0;				///<��lpszValue������Obj(int)
		virtual DMCode ParseBool(LPCSTR lpszValue,bool&Obj) = 0;			///<��lpszValue������Obj(bool)
		virtual DMCode ParseColor(LPCSTR lpszValue,DMColor&Obj) = 0;		///<��lpszValue������Obj(COLORREF)
		virtual DMCode ParseSize(LPCSTR lpszValue,DM::CSize&Obj) = 0;		///<��lpszValue������Obj(CSize)
		virtual DMCode ParsePoint(LPCSTR lpszValue,DM::CPoint&Obj) = 0;	///<��lpszValue������Obj(Obj)
		virtual DMCode ParseRect(LPCSTR lpszValue,DM::CRect&Obj) = 0;		///<��lpszValue������Obj(CRect)
	};
}
