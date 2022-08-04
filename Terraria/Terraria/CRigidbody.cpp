#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CObject.h"
#include"CTransform2D.h"

CRigidbody::CRigidbody()
    :CComponent(false)
    ,m_fMass(1.f)
    ,m_vAcceleration({0,0})
    ,m_vForce({0,0})
    ,m_vVelocity({0,0})
    , m_pOwner(nullptr)
{
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
    printf("플레이어 포지션 업데이트 X : %.f , Y : %.f\n", vOwnerPos.x, vOwnerPos.y);
    m_pOwner->SetPosition(vOwnerPos);
    return 0;
}

int CRigidbody::Render(const HDC _hdc)const
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
        m_vVelocity += m_vAcceleration * GET_DT;


        // PowerReset
        m_vForce = Vector2({ 0.f, 0.f });
    }
    Move();
    return 0;
}

CRigidbody::~CRigidbody()
{
}