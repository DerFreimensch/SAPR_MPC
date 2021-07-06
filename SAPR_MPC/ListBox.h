#pragma once
#include <list>

// Диалоговое окно ListBox

class ListBox : public CDialogEx
{
	DECLARE_DYNAMIC(ListBox)

public:
	ListBox(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ListBox();
	void LoadListBox(std::list<CString> SensorList);

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listBox;
};
