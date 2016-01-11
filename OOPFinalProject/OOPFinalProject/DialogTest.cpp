// DialogTest.cpp : implementation file
//

#include "stdafx.h"
#include "OOPFinalProject.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// CDialogTest dialog

IMPLEMENT_DYNAMIC(CDialogTest, CDialog)

CDialogTest::CDialogTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTest::IDD, pParent)
{

}

CDialogTest::~CDialogTest()
{
}

void CDialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);




}


BEGIN_MESSAGE_MAP(CDialogTest, CDialog)
END_MESSAGE_MAP()


// CDialogTest message handlers
