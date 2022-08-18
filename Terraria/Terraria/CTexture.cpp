#include "pch.h"
#include "CTexture.h"
#include"CEngine.h"


CTexture::CTexture()
	:m_DC(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}


int CTexture::LoadTexture(const wstring& _strfilepath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strfilepath.c_str()
		, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// Failed load Bitmap exception handling
	if(nullptr == m_hBit)
		return FUNC_ERROR;
	//assert(m_hBit);

	// SetDraw DC
	m_DC = CreateCompatibleDC(CEngine::GetInstance()->GetMainDC());

	// Set DC on Bit
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_DC, m_hBit);
	DeleteObject(hPrevBit);

	// GetBitmap Info
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	return 0;
}



CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_hBit);
}
