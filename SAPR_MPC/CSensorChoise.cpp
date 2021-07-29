// CSensorChoise.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "CSensorChoise.h"
#include "afxdialogex.h"
#include "ListBox.h"
#include "CData.h"

// Диалоговое окно CSensorChoise

IMPLEMENT_DYNAMIC(CSensorChoise, CDialogEx)

CSensorChoise::CSensorChoise(CData &Data, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFMAKE, pParent)
	, m_Data(Data)
	, SensorFile(_T(""))
	, ConfigFolder(_T(""))
	, DeviceName(_T(""))
{

}

CSensorChoise::~CSensorChoise()
{
}

void CSensorChoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON2, ChoiseSensor);
	DDX_Text(pDX, IDC_MFCEDITBROWSE3, SensorFile);
	DDX_Text(pDX, IDC_MFCEDITBROWSE2, ConfigFolder);
	DDX_Text(pDX, IDC_RICHEDIT21, DeviceName);
}


BEGIN_MESSAGE_MAP(CSensorChoise, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CSensorChoise::OnBnClickedTakeSensor)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE3, &CSensorChoise::OnEnChangeFailureFile)
	ON_EN_CHANGE(IDC_RICHEDIT21, &CSensorChoise::OnEnChangeDevice)
END_MESSAGE_MAP()


// Обработчики сообщений CSensorChoise


void CSensorChoise::OnBnClickedTakeSensor()
{
	UpdateData(TRUE);
	m_Data.FillData(SensorFile);
	ListBox box(m_Data, this);
	box.DoModal();
	m_Data.EraseList();
	h = m_Data.FileAdd(ConfigFolder, DeviceName, h);
}




void CSensorChoise::OnEnChangeFailureFile()
{
	UpdateData(TRUE);
	ConfigFolder = SensorFile.Left(SensorFile.ReverseFind('\\'))+L"\\config.txt";
	if (DeviceName != L"" && SensorFile != L"")
		ChoiseSensor.EnableWindow(TRUE);
	else
		ChoiseSensor.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CSensorChoise::OnEnChangeDevice() {
	UpdateData(TRUE);
	if (DeviceName != L"" && SensorFile != L"")
		ChoiseSensor.EnableWindow(TRUE);
	else
		ChoiseSensor.EnableWindow(FALSE);
	UpdateData(FALSE);
}
