#pragma once
#include "CComponent.h"

class CObject;

class CCollider :
    public CComponent
{
public:
	virtual int Render(const HDC _dc)const = 0;
	virtual int Update() = 0;
	virtual int FinalUpdate() = 0;
protected:
	// Owner
	CObject* m_pOwner;
	// Collider pos
	Vector2 m_vPos;
protected:
	CCollider();
	~CCollider();

};

