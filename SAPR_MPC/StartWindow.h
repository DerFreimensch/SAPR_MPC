#pragma once
#include "CData.h"

// Диалоговое окно StartWindow

class StartWindow : public CDialogEx
{
	DECLARE_DYNAMIC(StartWindow)

public:
	StartWindow(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~StartWindow();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTWINDOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
private:
	CData m_SensorData;

public:
	afx_msg void OnBnClickedCreateFile();
	afx_msg void OnBnClickedSensorCheck();
};
