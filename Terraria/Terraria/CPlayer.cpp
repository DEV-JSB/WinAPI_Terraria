#include "pch.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CInputMgr.h"
#include"CTransform2D.h"

#define MOVE_FORCE 50.f

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
    CAnimator* pAnimator = RTTI_DYNAMIC_CAST_MAP(CAnimator, m_mapComponent, COMPONENT::COMPONENT_ANIMATOR);
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_A) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        pAnimator->SetFilp(true);
        CObject::AddForce(Vector2{ -MOVE_FORCE,0.f });
    }
    if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_D) == INPUTSTATE::INPUTSTATE_HOLD)
    {
        CObject::AddForce(Vector2{ MOVE_FORCE,0.f });
        pAnimator->SetFilp(false);
    }


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

CPlayer::CPlayer()
    :CObject(Vector3({ (float)(CLIENT_WIDTH * 0.5), (float)(CLIENT_HEIGHT * 0.5), 0.f }), Vector3(), Vector2())
{
    // SetAnimator
    CAnimator* pAnimator = CFactory<CAnimator>::Create(true);
    
    pAnimator->LoadAnimation(L"PlayerCloth",    L"Player_Cloth.bmp");
    pAnimator->LoadAnimation(L"PlayerHead",     L"Player_Head.bmp");
    pAnimator->LoadAnimation(L"PlayerHair",     L"Player_Hair.bmp");
    pAnimator->LoadAnimation(L"PlayerArm",  L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerArm2", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerLeg",      L"Player_Leg.bmp");

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

CPlayer::~CPlayer()
{
}
