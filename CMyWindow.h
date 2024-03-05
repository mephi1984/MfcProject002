#pragma once

#include "afxwin.h"
#include <fstream>


class CMyWindow : public CFrameWnd {

public:
	CMyWindow();

	void OnButtonClicked();

	void LoadFile();

	void LoadMyBitmap(int shiftX, int shiftY, int index, unsigned char* pointerToImageData);

	CButton myButton;
	CStatic imageStatic;

	HBITMAP bitmap[12];

	DECLARE_MESSAGE_MAP();
};

