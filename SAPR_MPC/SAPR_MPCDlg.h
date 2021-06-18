
// SAPR_MPCDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CSAPRMPCDlg
class CSAPRMPCDlg : public CDialogEx
{
// Создание
public:
	CSAPRMPCDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAPR_MPC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton make_button;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL CompAnalyze;
	BOOL SimpAnalyze;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CString station;
	CString sensor;
	CString rtf;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeMfceditbrowse1();
	CButton default_radio_button;
};
