#pragma once
#include "CCollider.h"
#include"CFactory2.h"

class CObject;

class CBoxCollider :
    public CCollider
{
public: // Set Function
	// Setting All of Member
	int SetInformation(CObject* _pObj, const Vector2& _pos, const Vector2& _scale, const Vector2& _offset);
	int SetScale(const Vector2& _scale) { m_vScale = _scale; return 0; }
	int SetOffset(const Vector2& _offset) { m_vOffset = _offset; return 0; }
	int SetPos(const Vector2& _pos) { m_vPos = _pos; return 0; }
public: // Get Function
	Vector2 GetScale()const { return m_vScale; }
	Vector2 GetOffset()const { return m_vOffset; }
	virtual COLLIDER GetType()const override { return m_eType; }
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

