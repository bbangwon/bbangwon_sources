
// fileenc.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CfileencApp:
// �� Ŭ������ ������ ���ؼ��� fileenc.cpp�� �����Ͻʽÿ�.
//

class CfileencApp : public CWinAppEx
{
public:
	CfileencApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CfileencApp theApp;