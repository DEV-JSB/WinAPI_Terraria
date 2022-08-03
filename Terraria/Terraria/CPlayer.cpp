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
    pAnimator->LoadAnimation(L"Player");
}

CPlayer::~CPlayer()
{
}
