#include "pch.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CInputMgr.h"
#include"CTransform2D.h"

#define MOVE_FORCE 100.f

CPlayer::CPlayer()
    :CObject(Vector3({ (float)(CLIENT_WIDTH * 0.5), (float)(CLIENT_HEIGHT * 0.5), 0.f }), Vector3(), Vector2())
    , m_eState(PLAYER_STATE::STATE_IDLE)
{
    // SetAnimator
    CAnimator* pAnimator = CFactory<CAnimator>::Create(true);

    pAnimator->LoadAnimation(L"PlayerCloth", L"Player_Cloth.bmp");
    pAnimator->LoadAnimation(L"PlayerHead", L"Player_Head.bmp");
    pAnimator->LoadAnimation(L"PlayerHair", L"Player_Hair.bmp");
    pAnimator->LoadAnimation(L"PlayerArm", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerArm2", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerLeg", L"Player_Leg.bmp");

    pAnimator->SettingPlayAnimation(vector<wstring>({ L"PlayerCloth"
                                                     ,L"PlayerHead"
                                                     ,L"PlayerHair"
                                                     ,L"PlayerArm"
                                                     ,L"PlayerArm2"
                                                     ,L"PlayerLeg" }));
    pAnimator->SetOwner(this);

    m_mapComponent.insert({ COMPONENT::COMPONENT_ANIMATOR,pAnimator });

    CObject::CreateRigidbody();

}


int CPlayer::FinalUpdate()
{
    for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
    {
        (*iter).second->FinalUpdate();
    }
    return 0;
}

int CPlayer::Update()
{
    Update_Move();
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

int CPlayer::Update_Move()
{
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_A) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ -MOVE_FORCE,0.f });
        m_eWillState = PLAYER_STATE::STATE_LEFTRUN;
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_D) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ MOVE_FORCE,0.f });
        m_eWillState = PLAYER_STATE::STATE_RIGHTRUN;
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_S) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ 0.f,MOVE_FORCE });
        m_eWillState = PLAYER_STATE::STATE_LEFTRUN;
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_W) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ 0.f,-MOVE_FORCE });
        m_eWillState = PLAYER_STATE::STATE_RIGHTRUN;
    }
    return 0;
}

int CPlayer::Update_Animation()
{
    CAnimator* pAnimator = RTTI_DYNAMIC_CAST_MAP(CAnimator, m_mapComponent, COMPONENT::COMPONENT_ANIMATOR);
    switch (m_eState)
    {
    case PLAYER_STATE::STATE_IDLE:
        break;
    case PLAYER_STATE::STATE_LEFTRUN:
        pAnimator->SetFilp(true);
        break;
    case PLAYER_STATE::STATE_RIGHTRUN:
        pAnimator->SetFilp(false);
        break;
    }
    return 0;
}

int CPlayer::Update_State()
{
    // Later Plus Exeption Handling
    m_eState = m_eWillState;
    return 0;
}


CPlayer::~CPlayer()
{
}
