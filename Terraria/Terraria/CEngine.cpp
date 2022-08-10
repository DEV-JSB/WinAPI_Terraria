#include "pch.h"
#include "CEngine.h"
#include"CInputMgr.h"
#include"CPathMgr.h"
#include"CResourceMgr.h"
#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include"CTimeMgr.h"

#define WINDOWSTART_X 100
#define WINDOWSTART_Y 100

CEngine::CEngine()
	:m_bufferDC(0)
	,m_hBit(0)
	,m_dc(0)
	,m_hWnd(0)
	,m_ptResolution({0,0})
	
{}

CEngine::~CEngine()
{
	// Delete Buffer, Buffer DC , GetDC
	DeleteObject(m_hBit);
	DeleteObject(m_bufferDC);
	DeleteObject(m_dc);

	
}

int CEngine::Progress()
{
	// Update
	Update();
	// Rendering
	Render();

	//Final Update
	FinalUpdate();
	return 0;
}

int CEngine::Init(HWND _hwnd, POINT _resoulution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _resoulution;

	// Setting Window RECT
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	// Get Scale Need ReSize scale
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, TRUE);
	// Resize Window
	SetWindowPos(_hwnd, nullptr, WINDOWSTART_X, WINDOWSTART_Y,
		rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Make DC for Draw Main Window
	m_dc = GetDC(m_hWnd);
	
	// Make Bitmap
	m_hBit = CreateBitmap(m_ptResolution.x, m_ptResolution.y,32, 1, nullptr);
	
	// Make AnotherDC
	m_bufferDC = CreateCompatibleDC(m_dc);
	
	// Setting New DC on BitBuffer
	// Then New DC is Ready Draw On new Buffer
	HBITMAP OldBit = (HBITMAP)SelectObject(m_bufferDC, m_hBit);
	DeleteObject(OldBit);

	DeleteObject(SelectObject(m_bufferDC, CreateBitmap(m_ptResolution.x, m_ptResolution.y, 32, 1, nullptr)));

	// New Bit Set WHITE
	PatBlt(m_bufferDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);



	// Initialize Manager
	CTimeMgr::GetInstance()->Init();
	CPathMgr::GetInstance()->Init();
	CInputMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();

	return 0;
}

int CEngine::Release()
{
	CSceneMgr::GetInstance()->Release();
	return 0;
}

int CEngine::FinalUpdate()
{
	CSceneMgr::GetInstance()->FinalUpdate();
	return 0;
}

int CEngine::Update()
{
	// UpdateManager
	CSceneMgr::GetInstance()->Update();
	CInputMgr::GetInstance()->Update();
	CTimeMgr::GetInstance()->Update();
	CCollisionMgr::GetInstance()->Update();
	return 0;
}

int CEngine::Render()
{
	// RenderingManager
	BitBlt(m_bufferDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_bufferDC, 0, 0, SRCCOPY);
	PatBlt(m_bufferDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);

	CTimeMgr::GetInstance()->Render();
	CSceneMgr::GetInstance()->Render(m_bufferDC);

	BitBlt(m_dc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_bufferDC, 0, 0, SRCCOPY);

	return 0;
}

int CEngine::RenderExceptDoubleBuffer()
{
	CSceneMgr::GetInstance()->Render(m_dc);
	CTimeMgr::GetInstance()->Render();

	BitBlt(m_dc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_bufferDC, 0, 0, SRCCOPY);
	return 0;
}


