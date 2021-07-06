// CSensorChoise.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "CSensorChoise.h"
#include "afxdialogex.h"
#include "ListBox.h"


// Диалоговое окно CSensorChoise

IMPLEMENT_DYNAMIC(CSensorChoise, CDialogEx)

CSensorChoise::CSensorChoise(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFMAKE, pParent)
{

}

CSensorChoise::~CSensorChoise()
{
}

void CSensorChoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON2, ChoiseSensor);
}


BEGIN_MESSAGE_MAP(CSensorChoise, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CSensorChoise::OnBnClickedMfcbutton2)
END_MESSAGE_MAP()


// Обработчики сообщений CSensorChoise


void CSensorChoise::OnBnClickedMfcbutton2()
{
	ListBox box;
	box.DoModal();
}
