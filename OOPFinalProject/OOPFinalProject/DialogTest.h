#pragma once


// CDialogTest dialog

class CDialogTest : public CDialog
{
	DECLARE_DYNAMIC(CDialogTest)

public:
	CDialogTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTest();

// Dialog Data
	enum { IDD = IDD_DIALOGTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
