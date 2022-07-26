#pragma once
#include"CResource.h"

class CTexture : public CResource
{
public:
	int LoadTexture(const wstring& _strfilepath);
public:
	HBITMAP GetHBitmap()const { return m_hBit; }
	BITMAP GetBitInfo()const { return m_bitInfo; }
	HDC GetTextureDC()const { return m_DC; }
private:
	// Where DrawingDC
	HDC m_DC;
	// HBitmap
	HBITMAP m_hBit;
	// Bitmap Information
	BITMAP m_bitInfo;

private:
	HIDE_CONSTRUCTOR(CTexture);

public:
	virtual ~CTexture();
};

