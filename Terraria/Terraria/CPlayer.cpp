#include "pch.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CFactory2.h"
#include "CRigidbody.h"
#include "CBoxCollider.h"
#include "CInputMgr.h"
#include "CTransform2D.h"

#define PLAYER_WIDTH 32.f
#define PLAYER_HEIGHT 40.f
//////////////////////////
#define MOVE_FORCE 45.f
#define MAX_SPEED 15.f
#define JUMP_POWER 30.f
/// ////////////////////////
CPlayer::CPlayer()
    : CMover(OBJECT::OBJECT_PLAYER,Vector3({ (float)(CLIENT_WIDTH * 0.5), (float)(CLIENT_HEIGHT * 0.5) + 110, 0.f }), Vector3(), Vector2())
    , m_eState(MOVER_STATE::STATE_IDLE)
    , m_eWillState(MOVER_STATE::STATE_IDLE)
    , m_bIsOnGround(false)
{
    CreateAnimator();
    CreateCollider(Vector2({ (float)(CLIENT_WIDTH * 0.5), (float)(CLIENT_HEIGHT * 0.5) }));
    CObject::CreateRigidbody(MAX_SPEED);
}

int CPlayer::Update_Gravity()
{
    if (!m_bIsOnGround)
    {
        CMover::SetRigidbody(RIGIDBODY::RIGIDBODY_GRAVITY, 90.f);
    }
    else
    {
        CMover::SetRigidbody(RIGIDBODY::RIGIDBODY_GRAVITY, 0.f);
    }
    return 0;
}

int CPlayer::OnCollision(const CObject* _pOther)
{
    // Set True Object Still On Ground
    if (OBJECT::OBJECT_TILE == _pOther->GetType())
    {
    }
    return 0;
}

int CPlayer::OnCollisionEnter(const CObject* _pOther)
{

    if (OBJECT::OBJECT_TILE == _pOther->GetType())
    {
    }
    return 0;
}

int CPlayer::OnCollisionExit(const CObject* _pOther)
{
    // Tile Overlap
    if (OBJECT::OBJECT_TILE == _pOther->GetType())
    {
    }
    return 0;
}

int CPlayer::FinalUpdate()
{
    CObject::FinalUpdate();
 
    return 0;
}

int CPlayer::Update()
{
    CObject::Update();

    Update_Move();
    Update_Gravity();
    Update_State();
    Update_Animation();

    return 0;
}

int CPlayer::Render(const HDC _dc)
{
    for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
    {
        (*iter).second->Render(_dc);
    }
    return 0;
}

int CPlayer::CreateAnimator()
{
    // SetAnimator
    CAnimator* pAnimator = CFactory<CAnimator>::Create(true);

    pAnimator->LoadAnimation(L"PlayerCloth", L"Player_Cloth.bmp");
    pAnimator->LoadAnimation(L"PlayerHead", L"Player_Head.bmp");
    pAnimator->LoadAnimation(L"PlayerHair", L"Player_Hair.bmp");
    pAnimator->LoadAnimation(L"PlayerFrontArm", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerBackArm", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerLeg", L"Player_Leg.bmp");
    pAnimator->LoadAnimation(L"PlayerJump", L"Player_Leg.bmp");
    pAnimator->LoadAnimation(L"PlayerFrontArmRun", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerBackArmRun", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerRunLeg", L"Player_RunLeg.bmp");

    // ArmJump
    pAnimator->LoadAnimation(L"PlayerFrontArmJump", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerBackArmJump", L"Player_Arm.bmp");


    pAnimator->SettingPlayAnimation(vector<wstring>({ L"PlayerCloth"
                                                     ,L"PlayerHead"
                                                     ,L"PlayerHair"
                                                     ,L"PlayerFrontArm"
                                                     ,L"PlayerBackArm"
                                                     ,L"PlayerLeg"}));
    pAnimator->SetOwner(this);

    m_mapComponent.insert({ COMPONENT::COMPONENT_ANIMATOR,pAnimator });
    return 0;
}

int CPlayer::Update_Move()
{
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_A) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ -MOVE_FORCE,0.f });
        m_eWillState = MOVER_STATE::STATE_LEFTRUN;
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_D) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ MOVE_FORCE,0.f });
        m_eWillState = MOVER_STATE::STATE_RIGHTRUN;
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_SPACE) == INPUTSTATE::INPUTSTATE_TAP)
    {
        if (m_bIsOnGround == true)
        {
            CMover::SetRigidbody(RIGIDBODY::RIGIDBODY_JUMPPOWER, JUMP_POWER);
            m_eWillState = MOVER_STATE::STATE_JUMP;
        }
    }
    return 0;
}

int CPlayer::Update_Animation()
{
    CAnimator* pAnimator = RTTI_DYNAMIC_CAST_MAP(CAnimator, m_mapComponent, COMPONENT::COMPONENT_ANIMATOR);
    switch (m_eState)
    {
    case MOVER_STATE::STATE_JUMP:
        pAnimator->SubstitutePlayAnimation(L"PlayerLeg", L"PlayerJump");
        pAnimator->SubstitutePlayAnimation(L"PlayerRunLeg", L"PlayerJump");
        pAnimator->SubstitutePlayAnimation(L"PlayerFrontArm", L"PlayerFrontArmJump");
        pAnimator->SubstitutePlayAnimation(L"PlayerBackArm", L"PlayerBackArmJump");
        break;
    case MOVER_STATE::STATE_IDLE:
        pAnimator->SubstitutePlayAnimation(L"PlayerJump", L"PlayerLeg");

        pAnimator->SubstitutePlayAnimation(L"PlayerFrontArmRun", L"PlayerFrontArm");
        pAnimator->SubstitutePlayAnimation(L"PlayerBackArmRun", L"PlayerBackArm");
        pAnimator->SubstitutePlayAnimation(L"PlayerRunLeg", L"PlayerLeg");

        pAnimator->SubstitutePlayAnimation(L"PlayerFrontArmJump", L"PlayerFrontArm");
        pAnimator->SubstitutePlayAnimation(L"PlayerBackArmJump", L"PlayerBackArm");
        break;
    case MOVER_STATE::STATE_LEFTRUN:
        pAnimator->SetFilp(true);
        if (!m_bIsOnGround)
        {
            pAnimator->SubstitutePlayAnimation(L"PlayerRunLeg", L"PlayerJump");
            pAnimator->SubstitutePlayAnimation(L"PlayerFrontArmRun", L"PlayerFrontArmJump");
            pAnimator->SubstitutePlayAnimation(L"PlayerBackArmRun", L"PlayerBackArmJump");
            break;
        }
        pAnimator->SubstitutePlayAnimation(L"PlayerFrontArm", L"PlayerFrontArmRun");
        pAnimator->SubstitutePlayAnimation(L"PlayerBackArm", L"PlayerBackArmRun");
        pAnimator->SubstitutePlayAnimation(L"PlayerLeg", L"PlayerRunLeg");
        pAnimator->SubstitutePlayAnimation(L"PlayerJump", L"PlayerRunLeg");

        break;
    case MOVER_STATE::STATE_RIGHTRUN:
        if (!m_bIsOnGround)
        {
            pAnimator->SubstitutePlayAnimation(L"PlayerRunLeg", L"PlayerJump");
            pAnimator->SubstitutePlayAnimation(L"PlayerFrontArmRun", L"PlayerFrontArmJump");
            pAnimator->SubstitutePlayAnimation(L"PlayerBackArmRun", L"PlayerBackArmJump");
            break;
        }
        pAnimator->SetFilp(false);
        // ArmAnimation Setting
        pAnimator->SubstitutePlayAnimation(L"PlayerFrontArm", L"PlayerFrontArmRun");
        pAnimator->SubstitutePlayAnimation(L"PlayerBackArm", L"PlayerBackArmRun");
        // LegAnimation Setting
        pAnimator->SubstitutePlayAnimation(L"PlayerLeg", L"PlayerRunLeg");
        pAnimator->SubstitutePlayAnimation(L"PlayerJump", L"PlayerRunLeg");

        break;
    }
    return 0;
}


int CPlayer::Update_State()
{
    CRigidbody* pRigidbody = RTTI_DYNAMIC_CAST_MAP(CRigidbody, m_mapComponent, COMPONENT::COMPONENT_RIGIDBODY);

    // Later Plus Exeption Handlings
    if (m_eState != m_eWillState)
    {
        m_eState = m_eWillState;
    }
    if (CMover::FootRayCast())
    {
        m_bIsOnGround = true;
        m_eWillState = MOVER_STATE::STATE_IDLE;
    }
    else
    {
        m_bIsOnGround = false;
        m_eWillState = MOVER_STATE::STATE_JUMP;
    }

    return 0;
}



int CPlayer::CreateCollider(const Vector2 _pos)
{
    CComponent* pBoxCollider = CFactory2::CreateComponent(COMPONENT::COMPONENT_BOXCOLLIDER);
    RTTI_DYNAMIC_CAST(pBoxCollider, CBoxCollider)->SetInformation(this,_pos
        , Vector2({ PLAYER_WIDTH , PLAYER_HEIGHT })
        , Vector2({ 0.f,-2.f }));
    
    m_mapComponent.insert({ COMPONENT::COMPONENT_COLLIDER , pBoxCollider });
    return 0;
}


CPlayer::~CPlayer()
{
}
