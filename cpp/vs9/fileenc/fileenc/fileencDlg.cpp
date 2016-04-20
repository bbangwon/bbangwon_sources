
// fileencDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CfileencDlg 대화 상자




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


// CfileencDlg 메시지 처리기

BOOL CfileencDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//암호화에 체크해둔다.
	((CButton*)GetDlgItem(IDC_RADIO_ENC))->SetCheck(true);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CfileencDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CfileencDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CfileencDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog fdlg(TRUE);
	if(fdlg.DoModal() == IDOK)
	{

		m_strOrgFile = fdlg.GetPathName();	
		CString OrgFileName = fdlg.GetFileName();
		CString OnlyFileName = OrgFileName.Left(OrgFileName.ReverseFind('.'));
		CString OrgFilePath = m_strOrgFile.Left(m_strOrgFile.ReverseFind('\\')+1);

		m_strTargetFile = OrgFilePath + OnlyFileName + "_result." + fdlg.GetFileExt();
		
		// TargetFile은 OrgFileName에 _result를 추가함.
		TRACE(m_strOrgFile + "\n");
		TRACE(m_strTargetFile + "\n");

	}
	
	//변수에 적힌 값을 컨트롤에 표시
	UpdateData(FALSE);

}

void CfileencDlg::OnBnClickedButtonAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_strPassword.GetLength() == 0)
	{
		AfxMessageBox("암/복호화에 필요한 패스워드를 넣어주세요");
		return;
	}

	//파일로딩
	CFile file;
	if(file.Open(m_strOrgFile, CFile::modeRead|CFile::typeBinary, NULL) == FALSE)
	{
		AfxMessageBox("암호화 할 파일읽기 실패");
		return;
	}

	//원본파일
	int fileLen = file.GetLength();
	char *fileBuf = new char[fileLen];
	file.Read(fileBuf, fileLen);
	file.Close();

	//아웃버퍼
	char* outBuf = new char[fileLen + 256];
	memset(outBuf, 0x00, fileLen + 256);
	int outLen = 0;


	if(((CButton*)GetDlgItem(IDC_RADIO_ENC))->GetCheck() == BST_CHECKED)
	{
		if(FileEncrypt((const unsigned char*)fileBuf, fileLen, (unsigned char*)outBuf, &outLen) == FALSE)
		{
			AfxMessageBox("파일 암호화 중 에러 발생!");
		}
	}
	else
	{
		if(FileDecrypt((const unsigned char*)fileBuf, fileLen, (unsigned char*)outBuf, &outLen) == FALSE)
		{
			AfxMessageBox("파일 복호화 중 에러 발생!");
		}
	}

	//결과파일쓰기
	if(file.Open(m_strTargetFile, CFile::modeWrite|CFile::modeCreate) == FALSE)
	{
		AfxMessageBox("암호화 파일쓰기 실패");
		return;
	}

	file.Write(outBuf, outLen);
	file.Close();

	delete [] fileBuf;
	delete [] outBuf;

	AfxMessageBox("파일 암/복호화에 성공했습니다.");

}



BOOL CfileencDlg::FileEncrypt(const unsigned char *orgBuf, int orgLen, unsigned char *descBuf, int *descLen)
{
	//Key, IV 만들기
	unsigned char *keyiv = new unsigned char[32];
	int ret = PKCS5_PBKDF2_HMAC_SHA1(m_strPassword.GetBuffer(0), m_strPassword.GetLength(), (unsigned char*)OUR_SALT, strlen(OUR_SALT), ITER, 32, keyiv);	

	int len = 0;

	//암호화
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
	//Key, IV 만들기
	unsigned char *keyiv = new unsigned char[48];
	int ret = PKCS5_PBKDF2_HMAC_SHA1(m_strPassword.GetBuffer(0), m_strPassword.GetLength(), (unsigned char*)OUR_SALT, strlen(OUR_SALT), ITER, 32, keyiv);

	int len = 0;

	//암호화
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

