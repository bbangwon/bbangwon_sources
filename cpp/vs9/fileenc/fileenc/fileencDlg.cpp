
// fileencDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "fileenc.h"
#include "fileencDlg.h"

#include <openssl/conf.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define OUR_SALT "fileenc_oursalt"
#define ITER 4096


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CfileencDlg ��ȭ ����




CfileencDlg::CfileencDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CfileencDlg::IDD, pParent)
	, m_strOrgFile(_T(""))
	, m_strTargetFile(_T(""))
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfileencDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ORGFILE, m_strOrgFile);
	DDX_Text(pDX, IDC_EDIT_TARGETFILE, m_strTargetFile);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}

BEGIN_MESSAGE_MAP(CfileencDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CfileencDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CfileencDlg::OnBnClickedButtonAction)
END_MESSAGE_MAP()


// CfileencDlg �޽��� ó����

BOOL CfileencDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	//��ȣȭ�� üũ�صд�.
	((CButton*)GetDlgItem(IDC_RADIO_ENC))->SetCheck(true);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CfileencDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CfileencDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CfileencDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CfileencDlg::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog fdlg(TRUE);
	if(fdlg.DoModal() == IDOK)
	{

		m_strOrgFile = fdlg.GetPathName();	
		CString OrgFileName = fdlg.GetFileName();
		CString OnlyFileName = OrgFileName.Left(OrgFileName.ReverseFind('.'));
		CString OrgFilePath = m_strOrgFile.Left(m_strOrgFile.ReverseFind('\\')+1);

		m_strTargetFile = OrgFilePath + OnlyFileName + "_result." + fdlg.GetFileExt();
		
		// TargetFile�� OrgFileName�� _result�� �߰���.
		TRACE(m_strOrgFile + "\n");
		TRACE(m_strTargetFile + "\n");

	}
	
	//������ ���� ���� ��Ʈ�ѿ� ǥ��
	UpdateData(FALSE);

}

void CfileencDlg::OnBnClickedButtonAction()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_strPassword.GetLength() == 0)
	{
		AfxMessageBox("��/��ȣȭ�� �ʿ��� �н����带 �־��ּ���");
		return;
	}

	//���Ϸε�
	CFile file;
	if(file.Open(m_strOrgFile, CFile::modeRead|CFile::typeBinary, NULL) == FALSE)
	{
		AfxMessageBox("��ȣȭ �� �����б� ����");
		return;
	}

	//��������
	int fileLen = file.GetLength();
	char *fileBuf = new char[fileLen];
	file.Read(fileBuf, fileLen);
	file.Close();

	//�ƿ�����
	char* outBuf = new char[fileLen + 256];
	memset(outBuf, 0x00, fileLen + 256);
	int outLen = 0;


	if(((CButton*)GetDlgItem(IDC_RADIO_ENC))->GetCheck() == BST_CHECKED)
	{
		if(FileEncrypt((const unsigned char*)fileBuf, fileLen, (unsigned char*)outBuf, &outLen) == FALSE)
		{
			AfxMessageBox("���� ��ȣȭ �� ���� �߻�!");
		}
	}
	else
	{
		if(FileDecrypt((const unsigned char*)fileBuf, fileLen, (unsigned char*)outBuf, &outLen) == FALSE)
		{
			AfxMessageBox("���� ��ȣȭ �� ���� �߻�!");
		}
	}

	//������Ͼ���
	if(file.Open(m_strTargetFile, CFile::modeWrite|CFile::modeCreate) == FALSE)
	{
		AfxMessageBox("��ȣȭ ���Ͼ��� ����");
		return;
	}

	file.Write(outBuf, outLen);
	file.Close();

	delete [] fileBuf;
	delete [] outBuf;

	AfxMessageBox("���� ��/��ȣȭ�� �����߽��ϴ�.");

}



BOOL CfileencDlg::FileEncrypt(const unsigned char *orgBuf, int orgLen, unsigned char *descBuf, int *descLen)
{
	//Key, IV �����
	unsigned char *keyiv = new unsigned char[32];
	int ret = PKCS5_PBKDF2_HMAC_SHA1(m_strPassword.GetBuffer(0), m_strPassword.GetLength(), (unsigned char*)OUR_SALT, strlen(OUR_SALT), ITER, 32, keyiv);	

	int len = 0;

	//��ȣȭ
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(ctx);

	if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, &keyiv[0], &keyiv[16]))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}

	if (1 != EVP_EncryptUpdate(ctx, descBuf, &len, orgBuf, orgLen))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}
	*descLen = len;

	if(1 != EVP_EncryptFinal_ex(ctx, descBuf + len, &len))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}
	*descLen += len;

	EVP_CIPHER_CTX_free(ctx);
	delete [] keyiv;



	return TRUE;
}

BOOL CfileencDlg::FileDecrypt(const unsigned char *orgBuf, int orgLen, unsigned char *descBuf, int *descLen)
{
	//Key, IV �����
	unsigned char *keyiv = new unsigned char[48];
	int ret = PKCS5_PBKDF2_HMAC_SHA1(m_strPassword.GetBuffer(0), m_strPassword.GetLength(), (unsigned char*)OUR_SALT, strlen(OUR_SALT), ITER, 32, keyiv);

	int len = 0;

	//��ȣȭ
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(ctx);

	if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, &keyiv[0], &keyiv[16]))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}

	if (1 != EVP_DecryptUpdate(ctx, descBuf, &len, orgBuf, orgLen))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}
	*descLen = len;

	if(1 != EVP_DecryptFinal_ex(ctx, descBuf + len, &len))
	{
		OpenErrLog();
		EVP_CIPHER_CTX_free(ctx);
		return FALSE;
	}
	*descLen += len;

	EVP_CIPHER_CTX_free(ctx);
	delete [] keyiv;

	return TRUE;
}

void CfileencDlg::OpenErrLog()
{
	FILE *fp = fopen("opensslerr.log", "wt+");
	ERR_print_errors_fp(fp);
	fclose(fp);
}

