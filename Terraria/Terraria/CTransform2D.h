#pragma once
#include"CComponent.h"



class CTransform2D : public CComponent
{
private:
	CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
	CTransform2D();


public:
	virtual ~CTransform2D();
public: // Logic Function
	

public: // Get Set Function
	Vector3 GetPosition()const { return m_vecPosition; }
	float GetPosition_X()const { return m_vecPosition.x; }
	float GetPosition_Y()const { return m_vecPosition.y; }
	float GetScale_Width()const { return m_vecScale.x; };
	float GetScale_Height()const { return m_vecScale.y; };



	int SetPosition(const Vector3 _pos) { m_vecPosition = _pos; return 0; }
	int SetPosition(const float _x, const float _y, const float _z) { m_vecPosition.x = _x; m_vecPosition.y = _y; m_vecPosition.z = _z; return 0;}
	int SetScale(const Vector2 _scale) { m_vecScale = _scale; return 0; }
private: // Member
	Vector3 m_vecPosition;
	Vector3 m_vecRotation;
	Vector2 m_vecScale;

	friend class CFactory<CTransform2D>;
};
