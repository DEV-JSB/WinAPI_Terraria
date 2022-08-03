#include "pch.h"
#include "CWorld.h"
#include"CPlayer.h"
#include"CResourceMgr.h"
#include"CPathMgr.h"
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
    LoadResource();


    CPlayer* Player = CFactory<CPlayer>::Create();
    
    
    return 0;
}

int CWorld::LoadResource()const
{
    wstring TexPath = CPathMgr::GetInstance()->GetContentPath();
    TexPath += L"Texture\\";
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Cloth.bmp", TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Head.bmp" , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Hair.bmp" , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Arm.bmp"  , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Leg.bmp"  , TexPath);


    return 0;
}

CWorld::CWorld()
{
}

CWorld::~CWorld()
{
}
