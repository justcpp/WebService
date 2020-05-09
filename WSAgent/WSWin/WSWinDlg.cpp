
// WSWinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WSWin.h"
#include "WSWinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CWSWinDlg �Ի���




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


// CWSWinDlg ��Ϣ�������

BOOL CWSWinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWSWinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, str.GetBuffer(), -1, NULL, 0, NULL, NULL);  
	//��tcharֵ����_char    
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::wstring strWeather;
	CString strCity;
	//std::string strct;
	//COleDateTime ct=COleDateTime::GetCurrentTime();
	//strct = TimeTostring(ct);
	m_EditCity.GetWindowText(strCity);
	if(strCity.IsEmpty()) strCity = _T("����");
	strWeather = g_GetWeather(strCity);
   // MessageBoxW(strWeather.c_str());
	m_EditWeather.SetWindowTextW(strWeather.c_str());
}

void CWSWinDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
    
	//CDialog::OnOK();
}
