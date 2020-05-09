
// mfcClientDlg.cpp : ʵ���ļ�
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


// CmfcClientDlg �Ի���




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


// CmfcClientDlg ��Ϣ�������

BOOL CmfcClientDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcClientDlg::OnPaint()
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
HCURSOR CmfcClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
ͨ��mongoose+bson+base64 ʵ��http����

bson����ͨ��base64������ͨ��mongooseʵ��http����
*/
void CmfcClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CSimpleHttpClient httpClient;
	std::string strUrl = "http://192.168.0.28:13996/UploadReportInfo";
	SimpleHttpResponse response;
	minibson::document d;
	d.set("Account", "zhang");
	CString strName = _T("����");
	std::string strTemp;
	HttpUtility::ConvertToUTF8(strName,strTemp);
	d.set("Name", strTemp);
	d.set("RoleID", "1");
	d.set("RecordID", "H1711113EUZ5E");
	strName = _T("�������");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
