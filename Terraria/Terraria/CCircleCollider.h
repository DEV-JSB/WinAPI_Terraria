#pragma once
#include"CCollider.h"
#include"CFactory2.h"



class CCircleCollider : public CCollider
{

public:
	virtual int Render(const HDC _dc)const override;
	virtual int Update() override;
	virtual int FinalUpdate() override;
private:
	friend class CFactory2;
	CCircleCollider();
public:
	virtual ~CCircleCollider();
};

