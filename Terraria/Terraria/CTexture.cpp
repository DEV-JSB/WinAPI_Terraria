#include "pch.h"
#include "CTexture.h"

int CTexture::LoadTexture(const wstring& _strfilepath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strfilepath.c_str()
		, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// Failed load Bitmap exception handling
	assert(m_hBit);

	// Need Make DC

	return 0;
}

CTexture::CTexture()
	:m_DC(0)
	,m_hBit(0)
	,m_bitInfo{}
{
}

CTexture* CTexture::Create()
{
	return new CTexture();
}

CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_hBit);
}
