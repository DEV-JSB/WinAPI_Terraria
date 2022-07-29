#pragma once
#include"CResource.h"

class CTexture : public CResource
{
public:
	int LoadTexture(const wstring& _strfilepath);
public:
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
	// hidden Constructor
	CTexture();
	friend class CFactory<CTexture>;
public:
	virtual ~CTexture();
};

