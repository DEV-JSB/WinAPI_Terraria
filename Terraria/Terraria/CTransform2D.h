#pragma once
#include"CComponent.h"



class CTransform2D : public CComponent
{
public:
	virtual ~CTransform2D();
public: // Logic Function
	

public: // Get Set Function
	Vector3 GetPosition()const { return m_vPosition; }
	float GetPosition_X()const { return m_vPosition.x; }
	float GetPosition_Y()const { return m_vPosition.y; }
	float GetScale_Width()const { return m_vScale.x; }
	float GetScale_Height()const { return m_vScale.y; }



	int SetPosition(const Vector3 _pos) { m_vPosition = _pos; return 0; }
	int SetPosition(const float _x, const float _y, const float _z) { m_vPosition.x = _x; m_vPosition.y = _y; m_vPosition.z = _z; return 0;}
	int SetScale(const Vector2 _scale) { m_vScale = _scale; return 0; }
private: // Member
	Vector3 m_vPosition;
	Vector3 m_vRotation;
	Vector2 m_vScale;
private:
	HIDE_CONSTRUCTOR(CTransform2D);
	CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);

};
