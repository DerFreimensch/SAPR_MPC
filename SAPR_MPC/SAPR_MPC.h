
// SAPR_MPC.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CSAPR_MPCApp:
// Сведения о реализации этого класса: SAPR_MPC.cpp
//

class CSAPR_MPCApp : public CWinApp
{
public:
	CSAPR_MPCApp();

// Переопределение
public:
	virtual BOOL InitInstance();


// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSAPR_MPCApp theApp;
