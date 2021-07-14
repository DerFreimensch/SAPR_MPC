#pragma once
#include <list>

// Диалоговое окно ListBox
class CData;
class ListBox : public CDialogEx
{
	DECLARE_DYNAMIC(ListBox)

public:
	ListBox(CData &c_sensorList, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ListBox();
	void LoadListBox();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listBox;
private:
	CData &m_SensorList;
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedSave();
};
