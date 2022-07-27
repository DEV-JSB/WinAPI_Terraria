#pragma once
#include"CResource.h"
class CTexture : public CResource
{
	


public:
	int LoadTexture(const wstring& _strfilepath);


private:
	// Where DrawingDC
	HDC m_DC;
	// HBitmap
	HBITMAP m_hBit;
	// Bitmap Information
	BITMAP m_bitInfo;

private:
	// hidden Constructor
	CTexture();
public:
	static CTexture* Create();
	virtual ~CTexture();
};

