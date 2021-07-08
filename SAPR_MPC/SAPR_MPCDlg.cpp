
// SAPR_MPCDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "SAPR_MPC.h"
#include "SAPR_MPCDlg.h"
#include "afxdialogex.h"
#include "DirtWork.h"
#include "CSensorChoise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CSAPRMPCDlg



CSAPRMPCDlg::CSAPRMPCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAPR_MPC_DIALOG, pParent)
	, CompAnalyze(FALSE)
	, SimpAnalyze(TRUE)
	, station(_T(""))
	, sensor(_T(""))
	, rtf(_T(""))
	, An(FALSE)
	, Dig(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CSAPRMPCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, make_button);
	//DDX_Radio(pDX, IDC_RADIO1, CompAnalyze);
	//DDX_Radio(pDX, IDC_RADIO2, SimpAnalyze);
	DDX_Text(pDX, IDC_EDIT1, station);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, sensor);
	DDX_Text(pDX, IDC_MFCEDITBROWSE2, rtf);
	DDX_Control(pDX, IDC_RADIO2, default_radio_button);
	//DDX_Radio(pDX, IDC_RADIO4, An);
	//DDX_Radio(pDX, IDC_RADIO3, Dig);
}

BEGIN_MESSAGE_MAP(CSAPRMPCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSAPRMPCDlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO1, &CSAPRMPCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSAPRMPCDlg::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT1, &CSAPRMPCDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CSAPRMPCDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_RADIO4, &CSAPRMPCDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CSAPRMPCDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CSAPRMPCDlg::OnBnClickedMfcbutton1)
END_MESSAGE_MAP()


// Обработчики сообщений CSAPRMPCDlg

BOOL CSAPRMPCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	((CButton *) GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	((CButton *) GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSAPRMPCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSAPRMPCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSAPRMPCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSAPRMPCDlg::OnBnClickedButton1()
{	
	UpdateData(TRUE);
	readfile(sensor, rtf, station, SimpAnalyze, An);
	UpdateData(FALSE);
	// TODO: добавьте свой код обработчика уведомлений
}




int CSAPRMPCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Добавьте специализированный код создания
	SetWindowText(L"САПР передачи в МПЦ-ЭЛ");
	return 0;
}


void CSAPRMPCDlg::OnSize(UINT nType, int cx, int cy) {
	CDialog::OnSize(nType, cx, cy);
		CRect m_do_button;
		if (make_button.GetSafeHwnd() != 0) {
			make_button.GetWindowRect(m_do_button);
			if (cy - 15 - (m_do_button.bottom - m_do_button.top) > 357)
				make_button.MoveWindow(30,
					cy - 15 - (m_do_button.bottom - m_do_button.top),
					m_do_button.right - m_do_button.left,
					m_do_button.bottom - m_do_button.top);
		}
}


void CSAPRMPCDlg::OnBnClickedRadio1()
{
	CompAnalyze = TRUE;
	SimpAnalyze = FALSE;
}


void CSAPRMPCDlg::OnBnClickedRadio2()
{
	CompAnalyze = FALSE;
	SimpAnalyze = TRUE;
}





void CSAPRMPCDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	if (station != L"" && sensor != L"")
		make_button.EnableWindow(TRUE);
	else
		make_button.EnableWindow(FALSE);
	UpdateData(FALSE);
	// TODO:  Добавьте код элемента управления
}


void CSAPRMPCDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	if (station != L"" && sensor != L"")
		make_button.EnableWindow(TRUE);
	else
		make_button.EnableWindow(FALSE);
	if (rtf == L"") {
		rtf = sensor.Left(sensor.ReverseFind('\\'));
	}
	UpdateData(FALSE);
	// TODO:  Добавьте код элемента управления
}


void CSAPRMPCDlg::OnBnClickedRadio4()
{
	Dig = FALSE;
	An = TRUE;
}


void CSAPRMPCDlg::OnBnClickedRadio3()
{
	Dig = TRUE;
	An = FALSE;
}


void CSAPRMPCDlg::OnBnClickedMfcbutton1()
{
	CSensorChoise SensorDialog(m_SensorData, this);
	SensorDialog.DoModal();
}
