#include "pch.h"
#include "CWorld.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include"CComponent.h"
#include "CInputMgr.h"
#include "CPathMgr.h"
#include "CFactory.h"
#include "CInventoryUI.h"
#include "CTileMgr.h"
#include "CUIManager.h"



CWorld::CWorld()
{
    m_eType = SCENE::SCENE_WORLD;
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
    CTileMgr::GetInstance()->Render(_dc);
    CUIManager::GetInstance()->Render(_dc);
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

    CUIManager::GetInstance()->Update();
    return 0;
}
int CWorld::Enter()
{
    LoadResource();

    // CreatePlayer
    CPlayer* Player = CFactory<CPlayer>::Create();
    m_arrObjectVec[(int)OBJECT::OBJECT_PLAYER].push_back(Player);
    
    // CreateTile
    CTileMgr::GetInstance()->Enter();
    
    // Setting Collider CheckBox
    CCollisionMgr::GetInstance()->CheckingGroupBox(OBJECT::OBJECT_TILE, OBJECT::OBJECT_PLAYER);

    CreateBackGround();
    CreateUI();

    return 0;
}

int CWorld::LoadResource()const
{
    wstring TexPath = CPathMgr::GetInstance()->GetContentPath();
    TexPath += L"Texture\\";
    // PlayerTexture
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Cloth.bmp", TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Head.bmp" , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Hair.bmp" , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Arm.bmp"  , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_Leg.bmp"  , TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Player_RunLeg.bmp", TexPath);

    // BackGroundTexture
    CResourceMgr::GetInstance()->LoadTexture(L"BackGround.bmp", TexPath);

    // UI Texture
    CResourceMgr::GetInstance()->LoadTexture(L"Inventory_Back.bmp", TexPath);
    CResourceMgr::GetInstance()->LoadTexture(L"Inventory_Select.bmp", TexPath);

    return 0;
}

int CWorld::CreateBackGround()
{    // CreateBackground    
    CObject* pBackG = CFactory2::CreateObject(OBJECT::OBJECT_BACKGROUND);
    RTTI_DYNAMIC_CAST(pBackG, CBackGround)->Setting(L"BackGround.bmp");
    m_arrObjectVec[(int)OBJECT::OBJECT_BACKGROUND].push_back(pBackG);
    return 0;
}

int CWorld::CreateUI()
{
    CUI* pInvenUI= CFactory2::CreateUI(UI_TYPE::UI_INVENTORY);
    pInvenUI = RTTI_DYNAMIC_CAST(pInvenUI, CInventoryUI);

    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pInvenUI);

    return 0;
}

int CWorld::Release()
{
    return 0;
}
CWorld::~CWorld()
{
}
