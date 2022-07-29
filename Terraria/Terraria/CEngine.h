#pragma once
class CEngine
{
	SINGLE(CEngine);
public: // Logic , Can Access OutSide
	int Progress();
	int Init(HWND _hwnd , POINT _resoulution);
	int Release();

	HDC GetBufferDC()const { return m_bufferDC; }
private:
	int Update();
	int Render();
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

