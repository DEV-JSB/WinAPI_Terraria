#include "pch.h"
#include "CWorld.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CResourceMgr.h"
#include "CItem.h"
#include "CSword.h"
#include "CCollisionMgr.h"
#include "CComponent.h"
#include "CInputMgr.h"
#include "CPathMgr.h"
#include "CFactory.h"
#include "CFactory2.h"
#include "CInventoryUI.h"
#include "CHealthUI.h"
#include "CTileMgr.h"
#include "CUIManager.h"
#include "CZombie.h"


#define ZOMBIE_COUNT 10


CWorld::CWorld()
{
    m_eType = SCENE::SCENE_WORLD;
}


int CWorld::DeadCheck()
{
    for (auto iter = m_arrObjectVec[(int)OBJECT::OBJECT_ZOMBIE].begin(); iter != m_arrObjectVec[(int)OBJECT::OBJECT_ZOMBIE].end();)
    {
        if ((*iter)->IsDead() == true)
        {
            delete (*iter);
            iter = m_arrObjectVec[(int)OBJECT::OBJECT_ZOMBIE].erase(iter);
        }
        else
        {
            iter++;
        }
    }
    return 0;
}

int CWorld::FinalUpdate()
{
    DeadCheck();


    for (int i = 0; i < (int)OBJECT::OBJECT_UI; ++i)
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
    for (int i = 0; i < (int)OBJECT::OBJECT_UI; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
        {
            if (i == (int)OBJECT::OBJECT_BACKGROUND)
            {
                m_arrObjectVec[i][j]->Render(_dc);
                CTileMgr::GetInstance()->Render(_dc);
            }
            else
                m_arrObjectVec[i][j]->Render(_dc);
        }
    }
    CUIManager::GetInstance()->Render(_dc);
    return 0;
}
int CWorld::Update()
{
    for (int i = 0; i < (int)OBJECT::OBJECT_UI; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
            m_arrObjectVec[i][j]->Update();
    }
    CUIManager::GetInstance()->Update();
    return 0;
}

int CWorld::Enter()
{
    LoadResource();

    CreateObject();


    // Setting Collider CheckBox
    CCollisionMgr::GetInstance()->CheckingGroupBox(OBJECT::OBJECT_TILE, OBJECT::OBJECT_PLAYER);

    CCollisionMgr::GetInstance()->CheckingGroupBox(OBJECT::OBJECT_TILE, OBJECT::OBJECT_ZOMBIE);

    CCollisionMgr::GetInstance()->CheckingGroupBox(OBJECT::OBJECT_ITEM, OBJECT::OBJECT_ZOMBIE);

    CCollisionMgr::GetInstance()->CheckingGroupBox(OBJECT::OBJECT_PLAYER, OBJECT::OBJECT_ZOMBIE);

    // Setting Player Item
    SetPlayerItem();

    return 0;
}

int CWorld::SetPlayerItem()
{
    const vector<CObject*> vecItem = CScene::GetObjectGroup(OBJECT::OBJECT_ITEM);

    for (size_t i = 0; i < vecItem.size(); ++i)
    {
        CScene::GetPlayer()->AcquireItem(RTTI_DYNAMIC_CAST(vecItem[i], CItem));
    }
    
    return 0;
}

int CWorld::LoadItem()
{
    CItem* pSword = CFactory2::CreateItem(ITEM::ITEM_SWORD);
    pSword->SetTexture(L"ItemSword.bmp");
    m_arrObjectVec[(int)OBJECT::OBJECT_ITEM].push_back(pSword);

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
    CResourceMgr::GetInstance()->LoadTexture(L"Heart.bmp", TexPath);

    // Item Texture
    CResourceMgr::GetInstance()->LoadTexture(L"ItemSword.bmp", TexPath);

    // Item Animation
    CResourceMgr::GetInstance()->LoadTexture(L"SwordUse.bmp", TexPath);\

    // MonsterTexture
    CResourceMgr::GetInstance()->LoadTexture(L"Zombie.bmp", TexPath);


    return 0;
}

int CWorld::CreateBackGround()
{    
    // CreateBackground    
    CObject* pBackG = CFactory2::CreateObject(OBJECT::OBJECT_BACKGROUND);
    RTTI_DYNAMIC_CAST(pBackG, CBackGround)->Setting(L"BackGround.bmp");
    m_arrObjectVec[(int)OBJECT::OBJECT_BACKGROUND].push_back(pBackG);
    return 0;
}

int CWorld::CreateUI()
{
    
    CUI* pUI2 = CFactory2::CreateUI(UI_TYPE::UI_INVENTORY);
    CInventoryUI* pInvenUI = RTTI_DYNAMIC_CAST(pUI2, CInventoryUI);

    pInvenUI->SetOwner(CScene::GetPlayer());
    

    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pUI2);

    pUI2 = CFactory2::CreateUI(UI_TYPE::UI_HEALTH);
    CHealthUI* pHealthUI = RTTI_DYNAMIC_CAST(pUI2, CHealthUI);

    pHealthUI->SetOwner(CScene::GetPlayer());


    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pUI2);



    return 0;
}

int CWorld::CreateObject()
{

    // CreatePlayer
    CPlayer* pPlayer = CFactory<CPlayer>::Create();
    m_arrObjectVec[(int)OBJECT::OBJECT_PLAYER].push_back(pPlayer);

    CObject* pZombie;
    float x = CLIENT_WIDTH + 400;
    float y = (float)CLIENT_HEIGHT * 0.6f;



    for (int i = 0 ; i < ZOMBIE_COUNT; ++i)
    {
        pZombie = CFactory2::CreateObject(OBJECT::OBJECT_ZOMBIE);
        RTTI_DYNAMIC_CAST(pZombie, CZombie)->Setting(x,y);
        m_arrObjectVec[(int)OBJECT::OBJECT_ZOMBIE].push_back(pZombie);
        x -= 60.f;
    }

    // CreateTile
    CTileMgr::GetInstance()->Enter();

    // Setting Backgound
    CreateBackGround();
    // Setting UI
    CreateUI();

    // Setting Item
    LoadItem();
    
    return 0;
}


int CWorld::Release()
{
    return 0;
}
CWorld::~CWorld()
{
}
