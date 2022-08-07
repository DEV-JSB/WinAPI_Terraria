#pragma once
#include "CCollider.h"
#include"CFactory2.h"

class CObject;

class CBoxCollider :
    public CCollider
{

public: // Logic
	virtual int Render(const HDC _dc)const	override;
	virtual int FinalUpdate()				override;
	virtual int Update()					override;

private:
	// Collider Scale
	Vector2 m_vScale;
	// Collider Scale
	Vector2 m_vOffset;
private:
	friend class CFactory2;
	CBoxCollider();
public:
	virtual ~CBoxCollider();
};

