#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CObject.h"
#include"CTransform2D.h"

CRigidbody::CRigidbody()
    :CComponent(false)
    , m_fMaxSpeed(100.f)
    , m_fFriction(50.f)
    , m_fMass(1.f)
    , m_vAcceleration({0,0})
    , m_vForce({0,0})
    , m_vVelocity({0,0})
    , m_pOwner(nullptr)
{
}

bool CRigidbody::IsMoving()
{
    if (0 == m_vVelocity.Length())
        return false;
    else
        return true;
}

int CRigidbody::Move()
{
    // MoveSpeed
    float fSpeed = m_vVelocity.Length();
    if (0.f == fSpeed)
        return 0;
    
    // Will Move Direction
    Vector2 vDirection = m_vVelocity;
    vDirection.Normalize();

    //Final Position
    Vector3 vOwnerPos = m_pOwner->GetTransform()->GetPosition();
    vOwnerPos.x += m_vVelocity.x * fSpeed * (float)GET_DT;
    vOwnerPos.y += m_vVelocity.y * fSpeed * (float)GET_DT;
    m_pOwner->SetPosition(vOwnerPos);
    return 0;
}

int CRigidbody::Render(const HDC _dc)const
{
    return 0;
}

int CRigidbody::Update()
{
    return 0;
}

int CRigidbody::FinalUpdate()
{
    // Divide Force -> Power And Direction
    float fForce = m_vForce.Length();

    if (0.f != fForce)
    {
        // Direction
        m_vForce = m_vForce.Normalize();

        // Acceleration Power = Force / Mass
        float m_fAcceleration = fForce / m_fMass;
        // Acceleration
        m_vAcceleration = m_vForce * m_fAcceleration;
        //Final Speed
        m_vVelocity += m_vAcceleration * (float)GET_DT;

        // Check MaxSpeed
        if (m_vVelocity.Length() > m_fMaxSpeed)
        {
            m_vVelocity.Normalize();
            m_vVelocity *= m_fMaxSpeed;
        }

        // PowerReset
        m_vForce = Vector2({ 0.f, 0.f });
    }

    // Caculator Friction
    if (0 != m_vVelocity.Length())
    {
        Vector2 vecFricDirect = -m_vVelocity;
        vecFricDirect.Normalize() *= (float)GET_DT;
        vecFricDirect *= m_fFriction;
        if (m_vVelocity.Length() <= vecFricDirect.Length())
            m_vVelocity = Vector2({ 0.f,0.f });
        else
            m_vVelocity += vecFricDirect;
    }
    Move();
    return 0;
}

CRigidbody::~CRigidbody()
{
}