// StartWindow.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "StartWindow.h"
#include "afxdialogex.h"
#include "SAPR_MPCDlg.h"
#include "CSensorChoise.h"


// Диалоговое окно StartWindow

IMPLEMENT_DYNAMIC(StartWindow, CDialogEx)

StartWindow::StartWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTWINDOW, pParent)
	, part1(FALSE)
	, part2(TRUE)
{

}

BOOL StartWindow::OnInitDialog() {
	CDialogEx::OnInitDialog();
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	return TRUE;
}

StartWindow::~StartWindow()
{
}

void StartWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Radio(pDX, IDC_RADIO2, part1);
	//DDX_Radio(pDX, IDC_RADIO1, part2);
}


BEGIN_MESSAGE_MAP(StartWindow, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO2, &StartWindow::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &StartWindow::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON1, &StartWindow::OnBnClickedStart)
END_MESSAGE_MAP()


// Обработчики сообщений StartWindow

//выбор второго пункта меню
void StartWindow::OnBnClickedRadio2()
{
	part2 = FALSE;
	part1 = TRUE;
}

//выбор первого пункта меню
void StartWindow::OnBnClickedRadio1()
{
	part2 = TRUE;
	part1 = FALSE;
}


void StartWindow::OnBnClickedStart()
{
	if (part2 == TRUE) {
		CSAPRMPCDlg dlg;
		dlg.DoModal();
	}
	else {
		CSensorChoise dlg(m_SensorData, this);
		dlg.DoModal();
	}

}
