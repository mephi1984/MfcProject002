#include "afxwin.h"
#include <fstream>
#include "CMyWindow.h"

#define WM_MY_TIMER (WM_USER + 1)

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR evnt, DWORD time)
{
	::PostThreadMessage(AfxGetThread()->m_nThreadID, WM_MY_TIMER, 0, 0);
}

int bitmapCounter = 0;

class CMyApp : CWinApp
{
	CMyWindow* window;

	virtual BOOL InitApplication()
	{
		window = new CMyWindow();
		this->m_pMainWnd = window;
		this->m_pMainWnd->ShowWindow(SW_SHOW);
		this->m_pMainWnd->UpdateWindow();


		this->m_pMainWnd->SetTimer(NULL, 30, &TimerProc);
		
		return TRUE;
	}

	

	afx_msg void OnMyTimer(WPARAM wParam, LPARAM lParam)
	{
		bitmapCounter = bitmapCounter + 1;
		if (bitmapCounter >= 12)
		{
			bitmapCounter = 0;
		}

		window->imageStatic.SetBitmap(window->bitmap[bitmapCounter]);

	}

	DECLARE_MESSAGE_MAP()
};


BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_THREAD_MESSAGE(WM_MY_TIMER, OnMyTimer)
END_MESSAGE_MAP()


CMyApp myApplication;


