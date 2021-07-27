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
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
private:
	// Выбор датчиков передачи в систему из файла описания датчиков
	BOOL part1;
	// Создание файла описания из выборки датчиков
	BOOL part2;
	CData m_SensorData;

public:
	afx_msg void OnBnClickedStart();
};
