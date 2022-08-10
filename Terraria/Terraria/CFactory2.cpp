#include "pch.h"
#include "CFactory2.h"
#include "CTile.h"
#include "CBoxCollider.h"
#include "CSkin.h"

CFactory2::CFactory2()
{
}

CObject* CFactory2::CreateObject(OBJECT _eType)
{
    switch (_eType)
    {
    case OBJECT::OBJECT_TILE:
        CTile* pObject = new CTile();
        return pObject;
        break;
    }
    return nullptr;
}

CComponent* CFactory2::CreateComponent(COMPONENT _eType)
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



CFactory2::~CFactory2()
{
}
