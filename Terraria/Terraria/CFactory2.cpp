#include "pch.h"
#include "CFactory2.h"
#include "CSkin.h"

CFactory2::CFactory2()
{
}

CComponent* CFactory2::CreateComponent(COMPONENT _eType)
{
    switch (_eType)
    {
    case COMPONENT::COMPONENT_SKIN:
        CSkin* pComponent = new CSkin(true);
        break;
    }
    return nullptr;
}



CFactory2::~CFactory2()
{
}
