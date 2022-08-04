#pragma once
#include "CComponent.h"
#include"CFactory.h"
class CRigidbody :
    public CComponent
{
public:// Get
    float GetMass()const { return m_fMass; }


public:// Set
    int SetMass(const float _f) { m_fMass = _f; return 0;}
    int SetOwner(CObject* _p) { m_pOwner = _p; return 0; }
public:// Func
    int AddForce(Vector2 _vForce) { m_vForce += _vForce; return 0; };
    int Move();
public:// Logic
    virtual int Render(const HDC _hdc)const      override;
    virtual int Update()      override;
    virtual int FinalUpdate() override;
private:
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
private:
    FRIEND_FACTORY(CRigidbody);
    CRigidbody();
public:
    virtual ~CRigidbody();
};

