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
private:
	static UINT g_iIdValue;
protected:
	// Collider Type
	COLLIDER m_eType;
	// For Make ID , Overlap block
	// ID Value
	UINT m_iID;
	// Owner
	CObject* m_pOwner;
	// Collider pos
	Vector2 m_vPos;
protected:
	CCollider(COLLIDER _eType);
	~CCollider();

};

