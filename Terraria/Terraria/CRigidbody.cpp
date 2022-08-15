#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CObject.h"
#include"CTransform2D.h"


CRigidbody::CRigidbody()
    :CComponent(false)
    , m_fJumpingPower   (0.f)
    , m_fGravityPower   (DEFAULT_GRAVITYPOWER)
    , m_fMaxSpeed       (DEFAULT_MAXSPEED)
    , m_fMass           (DEFAULT_MASS)
    , m_fFriction       (DEFAULT_FRICTION)
    , m_vGravity({0.f,1.f})
    , m_vAcceleration({0,0})
    , m_vForce({0,0})
    , m_vVelocity({0,0})
    , m_pOwner(nullptr)
{
}

bool CRigidbody::IsMoving()
{
    if (0 == m_vForce.Length() && m_fGravityPower == 0.f && m_fJumpingPower <= 0.f)
        return false;
    else
        return true;
}

int CRigidbody::SetGravityPower(const float _f)
{
    m_fGravityPower = _f;
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

int CRigidbody::MoveLogic()
{
    // Divide Force -> Power And Direction
    float fForce = m_vForce.Length();
    if (0.f != fForce)
    {
        // Direction
        m_vForce = m_vForce.Normalize();


        // Acceleration Power = Force / Mass
        float m_fAcceleration = fForce / m_fMass;
        m_fAcceleration *= (float)GET_DT;
        // Acceleration
        m_vAcceleration = m_vForce * m_fAcceleration;
        //Final Speed
        m_vVelocity += m_vAcceleration;

        // Check MaxSpeed
        if (m_vVelocity.Length() > m_fMaxSpeed)
        {
            m_vVelocity.Normalize();
            m_vVelocity *= m_fMaxSpeed;
        }

        // PowerReset
        m_vForce = Vector2({ 0.f, 0.f });
    }
    return 0;
}

int CRigidbody::GravityLogic()
{

    // Gravity Logic
    if (m_fGravityPower != 0.f)
    {
        m_vGravity *= m_fGravityPower * (float)GET_DT;
        if(m_fJumpingPower > 0.0f)
            m_fJumpingPower -= m_fGravityPower * (float)GET_DT;
        m_vVelocity += m_vGravity;
        m_vGravity = Vector2({ 0.f,1.f });
    }
    return 0;
}

int CRigidbody::JumpLogic()
{
    if (m_fJumpingPower != 0.f)
    {
        Vector2 vUp = Vector2({ 0, -1 });
        float fJump = m_fJumpingPower * (float)GET_DT;
        m_fJumpingPower -= fJump;
        vUp *= fJump;
        m_vVelocity += vUp;
    }
    // If Gravity is Zero then must On the ground so Jump Set Zero
    
    return 0;
}

int CRigidbody::FrictionLogic()
{
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
    return 0;
}
int CRigidbody::FinalUpdate()
{
    MoveLogic();
    GravityLogic();
    FrictionLogic();
    JumpLogic();

    Move();
    return 0;
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

    // Speed Setting ?? Delete
    fSpeed *= (float)GET_DT;

    //Final Position
    Vector3 vOwnerPos = m_pOwner->GetTransform()->GetPosition();

    vOwnerPos.x += m_vVelocity.x * fSpeed;
    vOwnerPos.y += m_vVelocity.y * fSpeed;
    m_pOwner->SetPosition(vOwnerPos);
    return 0;
}


CRigidbody::~CRigidbody()
{
}