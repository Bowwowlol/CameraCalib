
// CHWang.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#define __D3DRM_H__
#include "CHWang.h"
#include "CHWangDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCHWangApp

BEGIN_MESSAGE_MAP(CCHWangApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCHWangApp �غc

CCHWangApp::CCHWangApp()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CCHWangApp ����

CCHWangApp theApp;


// CCHWangApp ��l�]�w

BOOL CCHWangApp::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));

	CCHWangDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �b����m��ϥ� [�T�w] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �b����m��ϥ� [����] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}

	// �]���w�g������ܤ���A�Ǧ^ FALSE�A�ҥH�ڭ̷|�������ε{���A
	// �ӫD���ܶ}�l���ε{�����T���C
	return FALSE;
}