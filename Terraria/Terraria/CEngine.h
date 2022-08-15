#pragma once
class CEngine
{
	SINGLE(CEngine);
public: // Logic , Can Access OutSide
	int Progress();
	int Init(HWND _hwnd, POINT _resoulution);
	int Release();

public: // Get
	POINT GetResolution()const { return m_ptResolution; }
	HWND GetMainHWND()const { return m_hWnd; }
	HDC GetBufferDC()const { return m_bufferDC; }
	HDC GetMainDC()const { return m_dc; }
private: // Cycle
	int Update();
	int Render();
	int RenderExceptDoubleBuffer();
private:
	// Main global HWND
	HWND m_hWnd;
	// Main DrawDC;
	HDC m_dc;

	// For double b uffering DC
	HDC m_bufferDC;
	HBITMAP m_hBit;

	// Window Size
	POINT m_ptResolution;

};

