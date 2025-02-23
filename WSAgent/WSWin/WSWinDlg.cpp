
// WSWinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WSWin.h"
#include "WSWinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CWSWinDlg 对话框




CWSWinDlg::CWSWinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWSWinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWSWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WEATHER, m_EditWeather);
	DDX_Control(pDX, IDC_EDIT_CITY, m_EditCity);
}

BEGIN_MESSAGE_MAP(CWSWinDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_QUERY, &CWSWinDlg::OnBnClickedBtnQuery)
END_MESSAGE_MAP()


// CWSWinDlg 消息处理程序

BOOL CWSWinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWSWinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWSWinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWSWinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStringTostring(LPCTSTR C_str, string& c_str)
{
	char buf[256]={0};
	CString str;
	str=C_str;
	int iLength ;  
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, str.GetBuffer(), -1, NULL, 0, NULL, NULL);  
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, str.GetBuffer(), -1, buf, iLength, NULL, NULL);
	c_str=buf;
}

std::string TimeTostring( COleDateTime ctime )
{
	CString strFormat=_T("%Y-%m-%d %H:%M:%S");
    CString cstr;
	cstr = ctime.Format(strFormat);
	std::string strDateTime;
    CStringTostring(cstr,strDateTime);
	return strDateTime;
}

void CWSWinDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstring strWeather;
	CString strCity;
	//std::string strct;
	//COleDateTime ct=COleDateTime::GetCurrentTime();
	//strct = TimeTostring(ct);
	m_EditCity.GetWindowText(strCity);
	if(strCity.IsEmpty()) strCity = _T("杭州");
	strWeather = g_GetWeather(strCity);
   // MessageBoxW(strWeather.c_str());
	m_EditWeather.SetWindowTextW(strWeather.c_str());
}

void CWSWinDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
    
	//CDialog::OnOK();
}
