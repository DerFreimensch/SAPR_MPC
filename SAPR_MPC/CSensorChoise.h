﻿#pragma once


// Диалоговое окно CSensorChoise

class CSensorChoise : public CDialogEx
{
	DECLARE_DYNAMIC(CSensorChoise)

public:
	CSensorChoise(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CSensorChoise();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFMAKE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CMFCButton ChoiseSensor;
	afx_msg void OnBnClickedMfcbutton2();
};