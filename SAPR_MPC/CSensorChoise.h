#pragma once

// Диалоговое окно CSensorChoise
class CData;
class CSensorChoise : public CDialogEx
{
	DECLARE_DYNAMIC(CSensorChoise)

public:
	CSensorChoise(CData &Data, CWnd* pParent = nullptr);   // стандартный конструктор
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
	afx_msg void OnBnClickedTakeSensor();
	CString SensorFile;
	CString ConfigFolder;
	CString DeviceName;
private:
	CData &m_Data;
	int h = 0;
public:
	afx_msg void OnBnClickedMakeConfig();
	afx_msg void OnEnChangeFailureFile();
};
