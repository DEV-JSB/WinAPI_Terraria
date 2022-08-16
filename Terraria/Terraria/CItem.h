#pragma once
#include "CObject.h"
#include "CFactory2.h"
class CItem : public CObject
{
public: // Logic
	virtual int Render(const HDC _dc)	 = 0;
	virtual int Update()				 = 0;
protected:
	// Setting Texture
	virtual int SetTexture(const wstring& _str);
private:
	friend class CFactory2;
	CItem();
public:
	virtual ~CItem();
};

