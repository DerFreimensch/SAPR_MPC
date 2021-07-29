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
{

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
	ON_BN_CLICKED(IDC_BUTTON1, &StartWindow::OnBnClickedCreateFile)
	ON_BN_CLICKED(IDC_BUTTON3, &StartWindow::OnBnClickedSensorCheck)
END_MESSAGE_MAP()


// Обработчики сообщений StartWindow

//выбор второго пункта меню


void StartWindow::OnBnClickedCreateFile()
{
		CSAPRMPCDlg dlg;
		dlg.DoModal();
}


void StartWindow::OnBnClickedSensorCheck()
{
	CSensorChoise dlg(m_SensorData, this);
	dlg.DoModal();
}
