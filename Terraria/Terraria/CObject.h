#pragma once
#include"CComponent.h"

class CTransform2D;

class CObject
{
public:
	virtual int Update();
	virtual int Render(HDC _dc);
	

protected:
	// GetTransform
	CTransform2D* GetTransform()const;

public: // Set Funtion
	// Setting Object Pos
	int SetTransform(const Vector3 _pos);
	// Setting Object SetRotation
	int SetRotation(const Vector3 _rot);
	// Setting Object SetScale
	int SetScale(const Vector2 _scale);
protected:
	// Component Map
	std::map<COMPONENT, CComponent*> m_mapComponent;
protected:
	// Normal Constructor
	CObject();
	// Set Transform Constructor
	CObject(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);

public:
	// Release Component
	virtual ~CObject();
};

