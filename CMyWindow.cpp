#include "CMyWindow.h"

CMyWindow::CMyWindow()
{
	RECT myRect;
	myRect.left = 0;
	myRect.right = 800;
	myRect.top = 0;
	myRect.bottom = 600;

	Create(NULL, "hhhhhh", WS_OVERLAPPEDWINDOW, myRect, nullptr, nullptr, WS_EX_WINDOWEDGE, nullptr);
	RECT buttonRect;
	buttonRect.left = 10;
	buttonRect.right = 100;
	buttonRect.top = 10;
	buttonRect.bottom = 40;
	myButton.Create("Okay", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, 1);


	RECT staticRect;
	staticRect.left = 10;
	staticRect.right = 10 + 88;
	staticRect.top = 110;
	staticRect.bottom = 110 + 84;
	imageStatic.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect, this, 2);

	LoadFile();

}

	void CMyWindow::OnButtonClicked()
	{
	}

	void CMyWindow::LoadFile()
	{
		std::ifstream f;

		f.open("chip3.bmp", std::ios::binary);

		f.seekg(0, std::ios::end);
		int fileSize = f.tellg();
		f.seekg(0, std::ios::beg);

		unsigned char* bytes = new unsigned char[fileSize];

		f.read((char*)bytes, fileSize);

		unsigned int width = bytes[18];

		width = width + bytes[19] * 0x100;
		width = width + bytes[20] * 0x10000;
		width = width + bytes[21] * 0x1000000;

		unsigned int height = bytes[22];

		height = height + bytes[23] * 0x100;
		height = height + bytes[24] * 0x10000;
		height = height + bytes[25] * 0x1000000;

		unsigned char* pointerToImageData = bytes + 54;

		LoadMyBitmap(0, 0, 0, pointerToImageData);
		LoadMyBitmap(1, 0, 1, pointerToImageData);
		LoadMyBitmap(2, 0, 2, pointerToImageData);
		LoadMyBitmap(3, 0, 3, pointerToImageData);
		LoadMyBitmap(4, 0, 4, pointerToImageData);
		LoadMyBitmap(0, 1, 5, pointerToImageData);
		LoadMyBitmap(1, 1, 6, pointerToImageData);
		LoadMyBitmap(2, 1, 7, pointerToImageData);
		LoadMyBitmap(3, 1, 8, pointerToImageData);
		LoadMyBitmap(4, 1, 9, pointerToImageData);
		LoadMyBitmap(0, 2, 10, pointerToImageData);
		LoadMyBitmap(1, 2, 11, pointerToImageData);

		imageStatic.SetBitmap(bitmap[4]);


		f.close();

		//delete[] chipImage1;

		delete[] bytes;


	}

	void CMyWindow::LoadMyBitmap(int shiftX, int shiftY, int index, unsigned char* pointerToImageData)
	{
		BITMAPINFO info;

		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth = 88;
		info.bmiHeader.biHeight = 84;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 24;
		info.bmiHeader.biCompression = 0;
		info.bmiHeader.biSizeImage = 0;
		info.bmiHeader.biXPelsPerMeter = 0;
		info.bmiHeader.biYPelsPerMeter = 0;
		info.bmiHeader.biClrUsed = 0;
		info.bmiHeader.biClrImportant = 0;
		info.bmiColors[0].rgbBlue = 0;
		info.bmiColors[0].rgbGreen = 0;
		info.bmiColors[0].rgbRed = 0;
		info.bmiColors[0].rgbReserved = 0;

		//DrawContext = DC
		HDC hdc = this->GetDC()->m_hDC;

		unsigned char* chipImage1 = new unsigned char[88 * 84 * 3];

		for (int x = 0; x < 88; x++)
		{
			for (int y = 0; y < 84; y++)
			{
				int positionInPixel = y * 88 + x;

				int positionInOriginalImage = x + shiftX*88 + (y + (256 - 84) - shiftY*84) * 512;

				chipImage1[positionInPixel * 3 + 0] = pointerToImageData[positionInOriginalImage * 3 + 0];
				chipImage1[positionInPixel * 3 + 1] = pointerToImageData[positionInOriginalImage * 3 + 1];
				chipImage1[positionInPixel * 3 + 2] = pointerToImageData[positionInOriginalImage * 3 + 2];

			}
		}

		bitmap[index] = CreateDIBitmap(hdc, &info.bmiHeader, CBM_INIT, chipImage1, &info, 0);

		delete[] chipImage1;
	}

	BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
		ON_COMMAND(1, &CMyWindow::OnButtonClicked)
	END_MESSAGE_MAP()