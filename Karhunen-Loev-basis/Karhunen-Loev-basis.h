
// Karhunen-Loev-basis.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CKarhunenLoevbasisApp:
// Сведения о реализации этого класса: Karhunen-Loev-basis.cpp
//

class CKarhunenLoevbasisApp : public CWinApp
{
public:
	CKarhunenLoevbasisApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CKarhunenLoevbasisApp theApp;
