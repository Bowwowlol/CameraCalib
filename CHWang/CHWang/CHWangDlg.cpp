
// CHWangDlg.cpp : 實作檔
//

#include "stdafx.h"
#define __D3DRM_H__
#include "CHWang.h"
#include "CHWangDlg.h"


//*****************************************************************************************多媒體計時器
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
MMRESULT FTimerID;
void CALLBACK TimeProc(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
//*****************************************************************************************
#include <highgui.h> //CImage 類別

#include <direct.h> //_getcwd 路徑

using namespace std;
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

VideoCapture Cap_left;
VideoCapture Cap_right;

IplImage *pImage_left;
IplImage *pImage_right;

int PhotoCount_left=0;
int PhotoCount_right=0;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCHWangDlg 對話方塊




CCHWangDlg::CCHWangDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHWangDlg::IDD, pParent)
	
	, SquareSize(53)
	, nx(9)
	, ny(8)
	
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCHWangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Image_Live_left, m_Image_Live_left_c);
	DDX_Control(pDX, IDC_Image_Show_left, m_Image_Show_left_c);
	DDX_Control(pDX, IDC_Image_Live_right, m_Image_Live_right_c);
	DDX_Control(pDX, IDC_Image_Show_right, m_Image_Show_right_c);

	DDX_Control(pDX, IDC_SelectCamera_left, m_SelectCamera_left_c);
	DDX_Control(pDX, IDC_InitialCCD_left, m_InitialCCD_left_c);
	DDX_Control(pDX, IDC_OptionCCD_left, m_OptionCCD_left_c);
	DDX_Control(pDX, IDC_CloseCCD_left, m_CloseCCD_left_c);

	DDX_Control(pDX, IDC_SelectCamera_right, m_SelectCamera_right_c);
	DDX_Control(pDX, IDC_InitialCCD_right, m_InitialCCD_right_c);
	DDX_Control(pDX, IDC_OptionCCD_right, m_OptionCCD_right_c);
	DDX_Control(pDX, IDC_CloseCCD_right, m_CloseCCD_right_c);

	DDX_Control(pDX, IDC_BOTH, m_BOTH_c);
	DDX_Control(pDX, IDC_StereoCalib, m_StereoCalib_c);

	DDX_Text(pDX, IDC_SquareSize, SquareSize);
	DDX_Text(pDX, IDC_Chessboard_X, nx);
	DDX_Text(pDX, IDC_Chessboard_Y, ny);



	DDX_Control(pDX, IDC_BothClear, m_BothClear_c);

	DDX_Control(pDX, IDC_Image_PhotoCount, m_Image_PhotoCount_c);
}

BEGIN_MESSAGE_MAP(CCHWangDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_InitialCCD_left, &CCHWangDlg::OnBnClickedInitialccdleft)
	ON_BN_CLICKED(IDC_OptionCCD_left, &CCHWangDlg::OnBnClickedOptionccdleft)
	ON_BN_CLICKED(IDC_CloseCCD_left, &CCHWangDlg::OnBnClickedCloseccdleft)
	ON_BN_CLICKED(IDC_left_clear, &CCHWangDlg::OnBnClickedleftclear)
	ON_BN_CLICKED(IDC_left_picture, &CCHWangDlg::OnBnClickedleftpicture)

	ON_BN_CLICKED(IDC_right_clear, &CCHWangDlg::OnBnClickedrightclear)
	ON_BN_CLICKED(IDC_InitialCCD_right, &CCHWangDlg::OnBnClickedInitialccdright)
	ON_BN_CLICKED(IDC_CloseCCD_right, &CCHWangDlg::OnBnClickedCloseccdright)
	ON_BN_CLICKED(IDC_OptionCCD_right, &CCHWangDlg::OnBnClickedOptionccdright)
	ON_BN_CLICKED(IDC_right_picture, &CCHWangDlg::OnBnClickedrightpicture)

	ON_BN_CLICKED(IDC_BOTH, &CCHWangDlg::OnBnClickedBoth)
	ON_BN_CLICKED(IDC_StereoCalib, &CCHWangDlg::OnBnClickedStereoCalib)

	ON_BN_CLICKED(IDC_BothClear, &CCHWangDlg::OnBnClickedBothclear)
END_MESSAGE_MAP()


// CCHWangDlg 訊息處理常式

BOOL CCHWangDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	
	m_SelectCamera_left_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(1);
	m_OptionCCD_left_c.EnableWindow(0);
	m_CloseCCD_left_c.EnableWindow(0);
	
	m_SelectCamera_right_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(1);
	m_OptionCCD_right_c.EnableWindow(0);
	m_CloseCCD_right_c.EnableWindow(0);
	
	
	m_BothClear_c.EnableWindow(0);
	m_BOTH_c.EnableWindow(0);
	m_StereoCalib_c.EnableWindow(1);
	

	

//*****************************************CCD選擇-左眼*******************************************************
	CString CameraName;
	CString cstr;
	char str[1024] = {0};
	char sName[1024] = {0};
	int nBufferSize = 0;

	for( int i = 0 ; i < Cap_left.GetCaptureCount() ; i++ )
	{
		Cap_left.GetDeviceName( i, sName, 100 );
		sprintf( str, "0%d %s", i, sName );
		cstr = str;
		m_SelectCamera_left_c.AddString( cstr );
	}

	m_SelectCamera_left_c.SetCurSel(0);
	m_SelectCamera_left_c.GetLBText( m_SelectCamera_left_c.GetCurSel(), cstr );
	LPTSTR lpsz = (LPTSTR)(LPCTSTR)cstr;
	CameraName = lpsz + 3;
//******************************************************************************************************
	m_Image_Live_left_c.SetWindowPos( &wndTop, 15, 15, 320, 240, SWP_SHOWWINDOW );//CCD影像貼圖

	m_Image_Show_left_c.SetWindowPos( &wndTop, 15, 300, 320, 240, SWP_SHOWWINDOW );

//*****************************************CCD選擇-右眼*******************************************************
	CString CameraName_r;
	CString cstr_r;
	char str_r[1024] = {0};
	char sName_r[1024] = {0};
	int nBufferSize_r = 0;

	for( int i = 0 ; i < Cap_right.GetCaptureCount() ; i++ )
	{
		Cap_right.GetDeviceName( i, sName_r, 100 );
		sprintf( str_r, "0%d %s", i, sName_r );
		cstr_r = str_r;
		m_SelectCamera_right_c.AddString( cstr_r );
	}

	m_SelectCamera_right_c.SetCurSel(0);
	m_SelectCamera_right_c.GetLBText( m_SelectCamera_right_c.GetCurSel(), cstr_r );
	LPTSTR lpsz_r = (LPTSTR)(LPCTSTR)cstr_r;
	CameraName_r = lpsz_r + 3;
//******************************************************************************************************
	m_Image_Live_right_c.SetWindowPos( &wndTop, 400, 15, 320, 240, SWP_SHOWWINDOW );

	m_Image_Show_right_c.SetWindowPos( &wndTop, 400, 300, 320, 240, SWP_SHOWWINDOW );

	m_Image_PhotoCount_c.SetWindowPos( &wndTop, 15, 280, 32, 16, SWP_SHOWWINDOW );

	PhotoCount = 0;

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CCHWangDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CCHWangDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CCHWangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCHWangDlg::OnBnClickedInitialccdleft()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	m_SelectCamera_left_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(0);
	m_OptionCCD_left_c.EnableWindow(1);
	m_CloseCCD_left_c.EnableWindow(1);
	
	m_SelectCamera_right_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(1);
	m_OptionCCD_right_c.EnableWindow(0);
	m_CloseCCD_right_c.EnableWindow(0);
	
	m_BothClear_c.EnableWindow(0);
	m_BOTH_c.EnableWindow(0);
	m_StereoCalib_c.EnableWindow(1);


	CWnd *Cwnd = AfxGetMainWnd()->GetDlgItem(IDC_Image_Live_left);
	Cap_left.CcdInitial( Cwnd->GetSafeHwnd(), m_SelectCamera_left_c.GetCurSel() );

	Cap_left.Capture();
}

void CCHWangDlg::OnBnClickedOptionccdleft()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	Cap_left.ConfigVideoFilter();
}

void CCHWangDlg::OnBnClickedCloseccdleft()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	Cap_left.StopCapture();
}

void CCHWangDlg::OnBnClickedleftclear()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	DeletePhoto_left();	
	
	
}

void CCHWangDlg::ShowImage( IplImage *Image, CWnd *Show )
{

	CDC	*dc = Show->GetWindowDC(); //宣告dc

	IplImage *Temp ;


	if( Image->width == 320, Image->height == 240 )
	{
		Temp = cvCloneImage( Image ); //圖片複製
	}
	else
	{
		Temp = cvCreateImage( cvSize(320, 240), IPL_DEPTH_8U, 3 ); //圖片預定大小
		cvResize(Image, Temp, CV_INTER_LINEAR); //圖片縮放
	}

	cvFlip( Temp, Temp ); //圖片上下翻轉

	CvvImage Temp2;	
	Temp2.CopyOf( Temp );		
	Temp2.Show( *dc, 0, 0, Temp->width ,Temp->height ); //貼圖

	cvReleaseImage( &Temp ); //釋放
}
/*
void CALLBACK TimeProc(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CCHWangDlg *pointer = (CCHWangDlg *)dwUser;

	pointer->DoEvent_left();
}
*/
void CCHWangDlg::DoEvent_left()
{
	CWnd *pWnd = GetDlgItem(IDC_Image_Show_left);

	GetImage_left();	

	ShowImage( pImage_left, pWnd );
}

void CCHWangDlg::GetImage_left()
{
	pImage_left = Cap_left.GetOneImage(); //取得即時影像圖片
}

void CCHWangDlg::DeletePhoto_left()
{
	PhotoCount_left = 0;

	char str[1024];
	char *path;
	path = _getcwd( NULL, 0 );

	while(1)
	{
		sprintf( str, "photo\\left%.2d.bmp", PhotoCount_left );
		ifstream in_file( str, ios::in );

		if( in_file )
		{
			in_file.close();
			char cstr[1024];
			sprintf( cstr, "%s\\%s", path, str );
			remove( cstr );
			PhotoCount_left++;
		}
		else
		{
			in_file.close();
			PhotoCount_left = 0;

			break;
		}
	}
}

void CCHWangDlg::OnBnClickedleftpicture()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	pImage_left = Cap_left.GetOneImage(); //取得即時影像圖片
	DoEvent_left();

	char STR[1024];
	char str[1024];
	char *path;
	path = _getcwd(NULL, 0);
	sprintf_s(str, "%s\\photo", path);
	_mkdir(str);
	
	sprintf_s(STR, "%s\\left%.2d.bmp", str, PhotoCount_left);

	IplImage *Temp;
	Temp = cvCloneImage(pImage_left);
	cvFlip(Temp, Temp);
	cvSaveImage(STR, Temp);
	cvReleaseImage(&Temp); 

	PhotoCount_left++;
}

//------------------------------------------------right------------------------------------------------------//

void CCHWangDlg::DeletePhotoright()
{
	PhotoCount_right = 0;

	char str[1024];
	char *path;
	path = _getcwd( NULL, 0 );

	while(1)
	{
		sprintf( str, "photo\\right%.2d.bmp", PhotoCount_right );
		ifstream in_file( str, ios::in );

		if( in_file )
		{
			in_file.close();
			char cstr[1024];
			sprintf( cstr, "%s\\%s", path, str );
			remove( cstr );
			PhotoCount_right++;
		}
		else
		{
			in_file.close();
			PhotoCount_right = 0;

			break;
		}
	}
}


void CCHWangDlg::OnBnClickedrightclear()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	DeletePhotoright();
}

void CCHWangDlg::OnBnClickedInitialccdright()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_SelectCamera_left_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(0);
	m_OptionCCD_left_c.EnableWindow(1);
	m_CloseCCD_left_c.EnableWindow(1);
	
	m_SelectCamera_right_c.EnableWindow(1);
	m_InitialCCD_left_c.EnableWindow(0);
	m_OptionCCD_right_c.EnableWindow(1);
	m_CloseCCD_right_c.EnableWindow(1);
	
	m_BothClear_c.EnableWindow(1);
	m_BOTH_c.EnableWindow(1);
	m_StereoCalib_c.EnableWindow(1);
	
	CWnd *Cwnd = AfxGetMainWnd()->GetDlgItem(IDC_Image_Live_right);
	Cap_right.CcdInitial( Cwnd->GetSafeHwnd(), m_SelectCamera_right_c.GetCurSel() );

	Cap_right.Capture();
}

void CCHWangDlg::OnBnClickedCloseccdright()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	Cap_right.StopCapture();
}

void CCHWangDlg::OnBnClickedOptionccdright()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	Cap_right.ConfigVideoFilter();
}

void CCHWangDlg::OnBnClickedrightpicture()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	pImage_right = Cap_right.GetOneImage(); //取得即時影像圖片
	DoEvent_right();

	char STR[1024];
	char str[1024];
	char *path;
	path = _getcwd(NULL, 0);
	sprintf_s(str, "%s\\photo", path);
	_mkdir(str);
	
	sprintf_s(STR, "%s\\right%.2d.bmp", str, PhotoCount_right);

	IplImage *Temp;
	Temp = cvCloneImage(pImage_right);
	cvFlip(Temp, Temp);
	cvSaveImage(STR, Temp);
	cvReleaseImage(&Temp); 

	PhotoCount_right++;
}

void CCHWangDlg::DoEvent_right()
{
	CWnd *pWnd = GetDlgItem(IDC_Image_Show_right);

	GetImage_right();	

	ShowImage( pImage_right, pWnd );

	CWnd* pWnd_Image_PhotoCount = GetDlgItem(IDC_Image_PhotoCount);
	ShowPhotoCount( PhotoCount, pWnd_Image_PhotoCount );
	
	
}

void CCHWangDlg::GetImage_right()
{
	pImage_right = Cap_right.GetOneImage(); //取得即時影像圖片
}

void CCHWangDlg::ShowPhotoCount( const int PhotoCount, CWnd* pWnd )
{
	 CDC *dc = pWnd->GetWindowDC();

	char count[10];
	sprintf_s( count, "%0.4d", PhotoCount );
	dc->TextOut( 0, 0, (CString)count );

	ReleaseDC(dc);
}
/*-------------------------------------------------------單眼校正---------------------------------------------------*/




/*-------------------------------------------------------雙眼校正---------------------------------------------------*/
void CCHWangDlg::OnBnClickedBoth()
{
	// TODO: 在此加入控制項告知處理常式程式碼\
	
		
	OnBnClickedleftpicture();
	OnBnClickedrightpicture();
	PhotoCount ++;
	UpdateData(true);
		
		if (PhotoCount==15)
		{
			OnBnClickedStereoCalib();
		}

}

void CCHWangDlg::OnBnClickedBothclear()
{
	// TODO: 在此加入控制項告知處理常式程式碼
		OnBnClickedrightclear();
		OnBnClickedleftclear();

}

void CCHWangDlg::OnBnClickedStereoCalib()

{

	remove("photo\\stereo_calib.txt");

	int p;
	int o=0;
	char s[20];
	char w[20];

	sprintf_s(w, "photo\\left");
	sprintf_s(s, "photo\\right");
	


	fstream outl("photo\\stereo_calib.txt",ios::app);
		
		outl<< nx-1 <<" "<< ny-1 <<endl;
		
		for (p=0;p<15;p++)
		{
			outl << w; 			
			outl.fill('0');
			outl.width(2); 
			outl << p << ".bmp" << endl;
			outl << s; 			
			outl.fill('0');
			outl.width(2); 
			outl << p << ".bmp" << endl;
			
		}
		
			
		outl.close();


	char STR[1024];
	
	
	sprintf_s(STR, "photo\\stereo_calib.txt");

	UpdateData(true);

	Stc.squareSize=SquareSize;
	

	Stc.StereoCalib(STR, 0);

	MessageBox( TEXT("校正結束!") );
	
}
