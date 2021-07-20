// CInfoBox.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "CInfoBox.h"
#include "afxdialogex.h"


// Диалоговое окно CInfoBox

IMPLEMENT_DYNAMIC(CInfoBox, CDialogEx)

CInfoBox::CInfoBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFOBOX, pParent)
{

}

CInfoBox::~CInfoBox()
{
}

void CInfoBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInfoBox::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInfoBox::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений CInfoBox


void CInfoBox::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void CInfoBox::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
