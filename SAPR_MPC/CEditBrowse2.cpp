// CEditBrowse2.cpp: файл реализации
//

#include "pch.h"
#include "SAPR_MPC.h"
#include "CEditBrowse2.h"


// CEditBrowse2

IMPLEMENT_DYNAMIC(CEditBrowse2, CMFCEditBrowseCtrl)

CEditBrowse2::CEditBrowse2()
{

}

CEditBrowse2::~CEditBrowse2()
{
}


BEGIN_MESSAGE_MAP(CEditBrowse2, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()

void CEditBrowse2::OnBrowse()
{
	ASSERT_VALID(this);
	ENSURE(GetSafeHwnd() != NULL);

	switch (m_Mode)
	{
	case BrowseMode_Folder:
		if (afxShellManager != NULL)
		{
			CString strFolder;
			GetWindowText(strFolder);

			CString strResult;
			if (afxShellManager->BrowseForFolder(strResult, this, strFolder, m_strBrowseFolderTitle.IsEmpty() ? NULL : (LPCTSTR)m_strBrowseFolderTitle, m_ulBrowseFolderFlags) &&
				(strResult != strFolder))
			{
				SetWindowText(strResult);
				SetModify(TRUE);
				OnAfterUpdate();
			}
		}
		else
		{
			ASSERT(FALSE);
		}
		break;

	case BrowseMode_File:
	{
		CString strFile;
		GetWindowText(strFile);

		if (!strFile.IsEmpty())
		{
			TCHAR fname[_MAX_FNAME];

			_tsplitpath_s(strFile, NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);

			CString strFileName = fname;
			strFileName.TrimLeft();
			strFileName.TrimRight();

			if (strFileName.IsEmpty())
			{
				strFile.Empty();
			}

			const CString strInvalidChars = _T("*?<>|");
			if (strFile.FindOneOf(strInvalidChars) >= 0)
			{
				if (!OnIllegalFileName(strFile))
				{
					SetFocus();
					return;
				}
			}
		}

		CFileDialog dlg(TRUE, !m_strDefFileExt.IsEmpty() ? (LPCTSTR)m_strDefFileExt : (LPCTSTR)NULL, strFile, m_dwFileDialogFlags, !m_strFileFilter.IsEmpty() ? (LPCTSTR)m_strFileFilter : (LPCTSTR)NULL, NULL);
		CString sPath;
		GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH), MAX_PATH);// поиск пути к файлу
		CString s(sPath);
		sPath.ReleaseBuffer(s.ReverseFind('\\'));
		dlg.m_ofn.lpstrInitialDir = sPath.GetString();
		if (dlg.DoModal() == IDOK && strFile != dlg.GetPathName())
		{
			SetWindowText(dlg.GetPathName());
			SetModify(TRUE);
			OnAfterUpdate();
		}

		if (GetParent() != NULL)
		{
			GetParent()->RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
		}
	}
	break;
	}

	SetFocus();
}

// Обработчики сообщений CEditBrowse2


