#pragma once


// CEditBrowse2

class CEditBrowse2 : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(CEditBrowse2)

public:
	CEditBrowse2();
	virtual ~CEditBrowse2();
	virtual void OnBrowse();
protected:
	DECLARE_MESSAGE_MAP()

};


