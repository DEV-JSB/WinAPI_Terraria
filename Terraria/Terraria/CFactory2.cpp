#include "pch.h"
#include "CFactory2.h"
#include "CTile.h"
#include "CBoxCollider.h"
#include "CSword.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CInventoryUI.h"
#include "CItemPocketUI.h"
#include "CSkin.h"
#include "CZombie.h"

CFactory2::CFactory2()
{
}

CItem* CFactory2::CreateItem(const ITEM _eType)
{
    switch (_eType)
    {
    case ITEM::ITEM_SWORD:
        CSword* pSword = new CSword();
        return pSword;
        break;
    }
    return nullptr;
}

CObject* CFactory2::CreateObject(const OBJECT _eType)
{
    switch (_eType)
    {
    case OBJECT::OBJECT_ZOMBIE:
        {
            CZombie* pObject = new CZombie();
            return pObject;
        }
        break;
    case OBJECT::OBJECT_BACKGROUND:
        {
            CBackGround* pObject = new CBackGround();
            return pObject;
        }
        break;
    case OBJECT::OBJECT_TILE:
        {
            CTile* pObject = new CTile();
            return pObject;
        }
        break;
    }
    return nullptr;
}

CComponent* CFactory2::CreateComponent(const COMPONENT _eType)
{
    switch (_eType)
    {
    case COMPONENT::COMPONENT_SKIN:
        {
            CSkin* pSkin = new CSkin(true);
            return pSkin;
        }
    case COMPONENT::COMPONENT_BOXCOLLIDER:
        {
            CCollider* pCollider = new CBoxCollider();
            return pCollider;
        }
    }
    return nullptr;
}

CUI* CFactory2::CreateUI(const UI_TYPE _eType)
{
    switch (_eType)
    {
    case UI_TYPE::UI_PARENT:
        {
            CUI* pUI = new CUI(UI_TYPE::UI_PARENT,false);
            return pUI;
        }
    case UI_TYPE::UI_INVENTORY:
        {
            CInventoryUI* pPocket = new CInventoryUI();
            return pPocket;
        }
    }
    return nullptr;
}



CFactory2::~CFactory2()
{
}
