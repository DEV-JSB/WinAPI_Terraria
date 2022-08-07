#include "pch.h"
#include "CWorld.h"
#include "CPlayer.h"
#include "CResourceMgr.h"
#include "CInputMgr.h"
#include "CPathMgr.h"
#include "CFactory.h"




CWorld::CWorld()
{
}


int CWorld::FinalUpdate()
{
    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
        {
            m_arrObjectVec[i][j]->FinalUpdate();
        }
    }
    return 0;
}

int CWorld::Render(const HDC _dc)
{
    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
        {
            m_arrObjectVec[i][j]->Render(_dc);
        }
    }
    return 0;
}
int CWorld::Update()
{

    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
        {
            m_arrObjectVec[i][j]->Update();
        }
    }

    return 0;
}
int CWorld::Enter()
{
    LoadResource();
    CPlayer* Player = CFactory<CPlayer>::Create();
    m_arrObjectVec[(int)OBJECT::OBJECT_PLAYER].push_back(Player);
    
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

int CWorld::Release()
{
    return 0;
}
CWorld::~CWorld()
{
}
