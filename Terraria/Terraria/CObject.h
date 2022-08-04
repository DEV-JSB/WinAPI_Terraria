#pragma once
#include"CComponent.h"

class CTransform2D;
class CRigidbody;

class CObject
{
public:
	virtual int Update()			= 0;
	virtual int Render(const HDC _dc)		= 0;
	virtual int FinalUpdate()		= 0;

public:
	// GetTransform
	CTransform2D* GetTransform() const;
	// Get Rigidbody
	CRigidbody* GetRigidbody() const;

public: // Set Transform Funtion
	// Setting Object Pos
	int SetPosition(const Vector3 _pos);
	int SetPosition(const Vector2 _pos);
	// Setting Object SetRotation
	int SetRotation(const Vector3 _rot);
	// Setting Object SetScale
	int SetScale(const Vector2 _scale);
public: // Set Rigidbody Function
	int AddForce(const Vector2 _force);

protected:
	int CreateRigidbody();
protected:
	// Component Map
	std::map<COMPONENT, CComponent*> m_mapComponent;
private: // CreateComponent
	int CreateTransform(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
protected:
	// Set Transform Constructor
	CObject(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
public:
	// Release Component
	virtual ~CObject();
};

