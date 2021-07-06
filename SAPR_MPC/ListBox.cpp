// ListBox.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "ListBox.h"
#include "afxdialogex.h"


// Диалоговое окно ListBox

IMPLEMENT_DYNAMIC(ListBox, CDialogEx)

ListBox::ListBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST, pParent)
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
END_MESSAGE_MAP()


// Обработчики сообщений ListBox
void ListBox::LoadListBox(std::list<CString> SensorList) {
	for (auto const elem : SensorList) {
		m_listBox.AddString(elem);
	}
}