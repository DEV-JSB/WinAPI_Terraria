#pragma once
#include "CComponent.h"
#include"CFactory.h"
class CRigidbody :
    public CComponent
{
public:
    bool IsMoving();

public:// Get
    float GetMass()const { return m_fMass; }
public:// Set
    int SetMaxSpeed(const float _fMaxspeed) { m_fMaxSpeed = _fMaxspeed; return 0; }
    int SetGravityPower(const float _f);
    int SetMass(const float _f) { m_fMass = _f; return 0;}
    int SetOwner(CObject* _p) { m_pOwner = _p; return 0; }
public:// Func
    int AddForce(Vector2 _vForce) { m_vForce += _vForce; return 0; };
    int Move();
public:// Logic
    virtual int Render(const HDC _dc)const      override;
    virtual int Update()      override;
    virtual int FinalUpdate() override;
private:
    // For Gravity
    Vector2 m_vGravity;
    float m_fGravityPower;

    // MaxSpeed
    float m_fMaxSpeed;
    // Owner
    CObject* m_pOwner;
    // Direction Vec
    Vector2 m_vForce;
    // Acceleration
    Vector2 m_vAcceleration;
    // Mass Weight
    float m_fMass;
    // Veclocity = speed + direction
    Vector2 m_vVelocity;
    // Friction
    float m_fFriction;
private:
    FRIEND_FACTORY(CRigidbody);
    CRigidbody();
public:
    virtual ~CRigidbody();
};

