
// CHWang.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�
#include "CvvImage.h"

// CCHWangApp:
// �аѾ\��@�����O�� CHWang.cpp
//

class CCHWangApp : public CWinAppEx
{
public:
	CCHWangApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CCHWangApp theApp;