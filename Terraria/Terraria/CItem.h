#pragma once
#include "CObject.h"
class CItem : public CObject
{
public: // GetFunction
	const wstring GetTextureName()const { return m_strItemTexture; }
public: // Logic
	virtual int Render(const HDC _dc)	 = 0;
	virtual int Update()				 = 0;
public:
	// Setting Texture
	virtual int SetTexture(const wstring& _str);
protected:
	// ItemIndex
	int m_iItemIndex;
	// Making through this Menber variable
	static int m_iIdxKey;
	// Item Texture
	wstring m_strItemTexture;
protected:
	CItem();
public:
	virtual ~CItem();
};

