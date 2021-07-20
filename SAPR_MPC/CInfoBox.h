#pragma once


// Диалоговое окно CInfoBox

class CInfoBox : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoBox)

public:
	CInfoBox(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CInfoBox();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFOBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
