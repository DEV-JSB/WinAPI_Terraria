#include "pch.h"
#include "CWorld.h"
#include"CPlayer.h"
#include"CFactory.h"
int CWorld::Release()
{
    return 0;
}
int CWorld::Render(const HDC _hdc)
{
    return 0;
}
int CWorld::Update()
{
    return 0;
}
int CWorld::Enter()
{
    CPlayer* Player = CFactory<CPlayer>::Create();
    
    
    return 0;
}

CWorld::CWorld()
{
}

CWorld::~CWorld()
{
}
