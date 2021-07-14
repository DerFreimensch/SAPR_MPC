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

ListBox::ListBox(CData &c_sensorList, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST, pParent)
	, m_SensorList(c_sensorList)
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
	ON_BN_CLICKED(IDC_BUTTON1, &ListBox::OnBnClickedUpdate)
	ON_BN_CLICKED(IDC_BUTTON2, &ListBox::OnBnClickedSave)
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


void ListBox::OnBnClickedUpdate()
{
	LoadListBox();
}


void ListBox::OnBnClickedSave()
{
	CArray<int, int> aryListSel;
	std::list<CString> ChoiseSensor;
	CString ex;
	aryListSel.SetSize(m_listBox.GetSelCount());
	m_listBox.GetSelItems(m_listBox.GetSelCount(), aryListSel.GetData());
	for (int i = 0; i < m_listBox.GetSelCount(); i++) {
		m_listBox.GetText(aryListSel.GetAt(i), ex);
		ChoiseSensor.push_back(ex);
	}
	m_SensorList.FillSensor(ChoiseSensor);
}
