
// mfcClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcClient.h"
#include "mfcClientDlg.h"
#include "SimpleHttpClient.h"
#include <string>
#include "minibson.hpp"
#include "base64.h"
#include <atlfile.h>
#include "HttpUtility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CmfcClientDlg 对话框




CmfcClientDlg::CmfcClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CmfcClientDlg 消息处理程序

BOOL CmfcClientDlg::OnInitDialog()
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

void CmfcClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcClientDlg::OnPaint()
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
HCURSOR CmfcClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
通过mongoose+bson+base64 实现http传输

bson数据通过base64编码再通过mongoose实现http传输
*/
void CmfcClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CSimpleHttpClient httpClient;
	std::string strUrl = "http://192.168.0.28:13996/UploadReportInfo";
	SimpleHttpResponse response;
	minibson::document d;
	d.set("Account", "zhang");
	CString strName = _T("张三");
	std::string strTemp;
	HttpUtility::ConvertToUTF8(strName,strTemp);
	d.set("Name", strTemp);
	d.set("RoleID", "1");
	d.set("RecordID", "H1711113EUZ5E");
	strName = _T("窦性心律");
	HttpUtility::ConvertToUTF8(strName,strTemp);
	d.set("DGSResult", strTemp);
	d.set("AlyTimeSpan", "00:12:12");
	d.set("FileName", "H1711113EUZ5E.ebi");
	CAtlFile mFileReader;
	mFileReader.Create(_T("D://H1711113EUZ5E.ebi"), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
	std::string strBuffer;
	ULONGLONG  nLength = 0;
	DWORD  nReadBytes = 0;
	mFileReader.GetSize(nLength);
	strBuffer.resize((int)nLength);
	HRESULT hrRet=mFileReader.Read((LPVOID)strBuffer.c_str(),(DWORD)nLength,nReadBytes);
	mFileReader.Close();
	d.set("FileData", minibson::binary::buffer((void*)strBuffer.c_str(), (size_t)nLength));
	size_t size = d.get_serialized_size();	
	char* buffer = new char[size];
	d.serialize(buffer, size);
	std::string strEn = ZBase64::Encode(buffer,size); 
	//std::string strBuffer(p);
	int isize = strEn.size();
	CSimpleHttpClient::SendJsonRequset(strUrl,strEn,response);
	//CSimpleHttpClient::SendJsonRequsetEx(strUrl,buffer,size,response);
	std::string str = response.content;
	int iOut;
    std::string strDe = ZBase64::Decode(str.c_str(),str.length(),iOut);
	minibson::document m(strDe.c_str(), strDe.length());
	int iRep = m.get("RepCode", 0);
	std::string msg = m.get("Message", "text");
	//delete[] buffer;
	return;
}

void CmfcClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string strUrl = "http://192.168.0.28:13996/Stream";
	SimpleHttpResponse response;
	minibson::document d;
	d.set("Name", "zhang");
	d.set("RoleID", "1");
	d.set("RecordID", "H1711113EUZ5E");
	ULONGLONG  nLength = 0;
	DWORD  nReadBytes = 0;
	size_t size = d.get_serialized_size();	
	char* buffer = new char[size];
	d.serialize(buffer, size);
	std::string strEn = ZBase64::Encode(buffer,size); 
	//std::string strBuffer(p);
	int isize = strEn.size();
	CSimpleHttpClient::SendJsonRequset(strUrl,strEn,response);
	std::string str = response.content;
	int iOut;
	std::string strDe = ZBase64::Decode(str.c_str(),str.length(),iOut);
	minibson::document m(strDe.c_str(), strDe.length());
	//delete[] buffer;
	return;
}
