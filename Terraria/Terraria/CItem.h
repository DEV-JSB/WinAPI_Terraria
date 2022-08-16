#pragma once
#include "CObject.h"
class CItem : public CObject
{
public: // Logic
	virtual int Render(const HDC _dc)	 = 0;
	virtual int Update()				 = 0;
protected:
	// Setting Texture
	virtual int SetTexture(const wstring& _str);
protected:
	// ItemIndex
	int m_iItemIndex;
	// Making through this Menber variable
	static int m_iIdxKey;

protected:
	CItem();
public:
	virtual ~CItem();
};

