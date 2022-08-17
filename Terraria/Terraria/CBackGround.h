#pragma once
#include"CObject.h"
#include"CFactory2.h"
class CBackGround : public CObject
{
public:
	
	int Setting(const wstring& _str);

public: // Logic
	virtual int Render(const HDC _dc) override;
	virtual int Update();
private:
	friend class CFactory2;
	CBackGround();
public:
	virtual ~CBackGround();
};

