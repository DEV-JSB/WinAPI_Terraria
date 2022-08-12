#pragma once
#include "CComponent.h"
#include "CFactory2.h"
class CObject;

class CCollider :
    public CComponent
{
public: // Set Function

	int SetOwner(CObject* _pObj) { m_pOwner = _pObj; return 0; }
public:// Get Function
	UINT GetID()const { return m_iID; }
	virtual COLLIDER GetType()const { return m_eType; }
	Vector2 GetPos()const { return m_vPos; }
public:
	virtual int Render(const HDC _dc)const = 0;
	virtual int Update() = 0;
	virtual int FinalUpdate();
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
	friend class CFactory2;
	CCollider(COLLIDER _eType);
	~CCollider();

};

