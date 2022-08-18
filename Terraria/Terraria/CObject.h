#pragma once
#include"CComponent.h"

class CTransform2D;
class CRigidbody;
class CCollider;

class CObject
{
public: // Logic
	virtual int Render(const HDC _dc);
	// Component Update
	virtual int Update();
	// Component FinalUpdate
	virtual int FinalUpdate();
public: // Collision Function
	// On Collision
	virtual int OnCollision(const CObject* _pOther)			{ return 0; };
	// Enter Collsiion
	virtual int OnCollisionEnter(const CObject* _pOther)	{ return 0; };
	// Exit Collision
	virtual int OnCollisionExit(const CObject* _pOther)		{ return 0; };
public:
	// GetCollider
	CCollider* GetCollider()const;
	// GetTransform
	CTransform2D* GetTransform() const;
	// Get Rigidbody
	CRigidbody* GetRigidbody() const;
	// Get Type
	OBJECT GetType() const { return m_eType; }
public: // Set Transform Funtion
	// Setting Object Pos
	int SetPosition(const Vector3 _pos);
	int SetPosition(const Vector2 _pos);
	// Setting Object SetRotation
	int SetRotation(const Vector3 _rot);
	// Setting Object SetScale
	int SetScale(const Vector2 _scale);
	// Setting Type
	int SetType(const OBJECT _eType) { m_eType = _eType; return 0; }

public: // Set Rigidbody Function
	int AddForce(const Vector2 _force);

protected:
	// Component Map
	std::map<COMPONENT, CComponent*> m_mapComponent;
protected: // CreateComponent
	int CreateTransform(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
	int CreateRigidbody(const float _fMaxSpeed);
protected:
	OBJECT m_eType;
protected:
	// Normal Constructor
	CObject(const OBJECT _eTpye);
	// Set Transform Constructor
	CObject(const OBJECT _eType, const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
public:
	// Release Component
	virtual ~CObject();
};

