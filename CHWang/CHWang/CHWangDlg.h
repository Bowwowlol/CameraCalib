
// CHWangDlg.h : 標頭檔
//

#pragma once
#include "..//RoboticsPlatform//VideoCapture//DXCapture.h"
#include "..//StereoCalib//StereoCalib.h"

#include "afxwin.h"


// CCHWangDlg 對話方塊
class CCHWangDlg : public CDialog
{
// 建構
public:
	CCHWangDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_CHWANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Stereo Stc;
	

	CStatic m_Image_Live_left_c;
	CStatic m_Image_Show_left_c;
	CComboBox m_SelectCamera_left_c;
	afx_msg void OnBnClickedInitialccdleft();
	afx_msg void OnBnClickedOptionccdleft();
	afx_msg void OnBnClickedCloseccdleft();
	afx_msg void OnBnClickedleftpicture();
	afx_msg void OnBnClickedleftclear();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();

	void ShowImage( IplImage *Image, CWnd *Show );
	void GetImage_left();
	void DoEvent_left();
	void DeletePhoto_left();
	
	
	

	CStatic m_Image_Live_right_c;
	CStatic m_Image_Show_right_c;
	CComboBox m_SelectCamera_right_c;
	afx_msg void OnBnClickedrightclear();
	afx_msg void OnBnClickedInitialccdright();
	afx_msg void OnBnClickedCloseccdright();
	afx_msg void OnBnClickedOptionccdright();
	afx_msg void OnBnClickedrightpicture();
	void DeletePhotoright();
	void DoEvent_right();
	void GetImage_right();
	
	
	
	
	afx_msg void OnBnClickedBoth();
	afx_msg void OnBnClickedStereoCalib();
	
	
	
	float SquareSize;
	int nx;
	int ny;
	CButton m_InitialCCD_left_c;
	CButton m_OptionCCD_left_c;
	CButton m_CloseCCD_left_c;
	CButton m_InitialCCD_right_c;
	CButton m_OptionCCD_right_c;
	CButton m_CloseCCD_right_c;
	CButton m_BOTH_c;
	CButton m_StereoCalib_c;
	CButton m_BothClear_c;
	afx_msg void OnBnClickedBothclear();
	
	
	CStatic m_Image_PhotoCount_c;
	int PhotoCount;
	void CCHWangDlg::ShowPhotoCount( const int PhotoCount, CWnd* pWnd );
};
