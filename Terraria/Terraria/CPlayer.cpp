#include "pch.h"
#include "CPlayer.h"
#include"CAnimator.h"


int CPlayer::FinalUpdate()
{
    return 0;
}

int CPlayer::Update()
{
    return 0;
}

int CPlayer::Render(const HDC _dc)
{
    return 0;
}

CPlayer::CPlayer()
{
    // SetAnimator
    CAnimator* pAnimator = CFactory<CAnimator>::Create();
    
    pAnimator->LoadAnimation(L"PlayerCloth",    L"Player_Cloth.bmp");
    pAnimator->LoadAnimation(L"PlayerHead",     L"Player_Head.bmp");
    pAnimator->LoadAnimation(L"PlayerHair",     L"Player_Hair.bmp");
    pAnimator->LoadAnimation(L"PlayerLeftArm",  L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerRightArm", L"Player_Arm.bmp");
    pAnimator->LoadAnimation(L"PlayerLeg",      L"Player_Leg.bmp");

}

CPlayer::~CPlayer()
{
}
