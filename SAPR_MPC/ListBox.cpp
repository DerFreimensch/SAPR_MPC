// ListBox.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "ListBox.h"
#include "afxdialogex.h"
#include "CSensorChoise.h"
#include "SAPR_MPCDlg.h"
#include "CData.h"

// Диалоговое окно ListBox

IMPLEMENT_DYNAMIC(ListBox, CDialogEx)

ListBox::ListBox(CData &SensorList, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST, pParent)
	, m_SensorList(SensorList)
{

}

ListBox::~ListBox()
{
}

void ListBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}


BEGIN_MESSAGE_MAP(ListBox, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &ListBox::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &ListBox::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений ListBox
void ListBox::LoadListBox() {
	for (auto const elem : m_SensorList.GetData()) {
		m_listBox.AddString(elem);
	}
}



void ListBox::OnLbnSelchangeList1()
{

}


void ListBox::OnBnClickedButton1()
{
	LoadListBox();
}
