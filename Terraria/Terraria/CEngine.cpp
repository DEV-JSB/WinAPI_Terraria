#include "pch.h"
#include "CEngine.h"

#define WINDOWSTART_X 100
#define WINDOWSTART_Y 100

CEngine::CEngine()
{

}

CEngine::~CEngine()
{

}

void CEngine::Init(HWND _hwnd, POINT _resoulution)
{
	m_hWnd = _hwnd;
	
	// Make DC for Draw Main Window
	m_hDC = GetDC(m_hWnd);

	m_ptResolution = _resoulution;

	// For Setting Window RECT
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	// Get Scale Need ReSize scale
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, TRUE);
	// Resize Window
	SetWindowPos(_hwnd, nullptr, WINDOWSTART_X, WINDOWSTART_Y,
		rt.right - rt.left, rt.top - rt.bottom, 0);

	// Make Bitmap
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	// Make AnotherDC
	m_bufferDC = CreateCompatibleDC(m_hDC);

	// Setting New DC on BitBuffer
	// Then New DC is Ready Draw On new Buffer
	HBITMAP OldBit = (HBITMAP)SelectObject(m_bufferDC, m_hBit);
	DeleteObject(OldBit);


}

void CEngine::Update()
{
}
