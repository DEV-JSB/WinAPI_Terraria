#pragma once
#include"CComponent.h"



class CTransform2D : public CComponent
{
public:
	virtual ~CTransform2D();
public: // Logic Function
	virtual int Render(const HDC _dc)const override;
	virtual int Update() override;
	virtual int FinalUpdate() override;

public: // Get Function
	Vector3 GetPosition()const { return m_vPosition; }
	Vector2 GetScale()const { return m_vScale; }
	float GetPosition_X()const { return m_vPosition.x; }
	float GetPosition_Y()const { return m_vPosition.y; }
	float GetScale_Width()const { return m_vScale.x; }
	float GetScale_Height()const { return m_vScale.y; }

public: // Set Function
	int Set_Y_Pos(const int _y) { m_vPosition.y = (float)_y; return 0; }
	int Set_X_Pos(const int _x) { m_vPosition.x = (float)_x; return 0; }
	int Set_Z_Pos(const int _z) { m_vPosition.z = (float)_z; return 0; }

	int SetPosition(const Vector2 _pos) { m_vPosition.x = _pos.x; m_vPosition.y = _pos.y; return 0; }
	int SetPosition(const Vector3 _pos) { m_vPosition = _pos; return 0; }
	int SetPosition(const float _x, const float _y, const float _z) { m_vPosition.x = _x; m_vPosition.y = _y; m_vPosition.z = _z; return 0;}
	int SetScale(const Vector2 _scale) { m_vScale = _scale; return 0; }
private: // Member
	Vector3 m_vPosition;
	Vector3 m_vRotation;
	Vector2 m_vScale;
private:
	FRIEND_FACTORY(CTransform2D);
	CTransform2D();
	CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);

};
