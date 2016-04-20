
// fileencDlg.h : ��� ����
//

#pragma once


// CfileencDlg ��ȭ ����
class CfileencDlg : public CDialog
{
// �����Դϴ�.
public:
	CfileencDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILEENC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
	CString m_strOrgFile;
	CString m_strTargetFile;
	CString m_strPassword;
	afx_msg void OnBnClickedButtonAction();

	BOOL FileEncrypt(const unsigned char *orgBuf, int orgLen, unsigned char *descBuf, int *descLen);
	BOOL FileDecrypt(const unsigned char *orgBuf, int orgLen, unsigned char *descBuf, int *descLen);

	void OpenErrLog();
};
