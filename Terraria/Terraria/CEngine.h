#pragma once
class CEngine
{
	SINGLE(CEngine);
public:
	void Init(HWND _hwnd , POINT _resoulution);
	void Update();
private:
	// Main global HWND
	HWND m_hWnd;
	// Main DrawDC;
	HDC m_hDC;

	// For double b uffering DC
	HDC m_bufferDC;
	HBITMAP m_hBit;

	// Window Size
	POINT m_ptResolution;

};

