#include "pch.h"
#include "CFactory.h"
#include "CTexture.h"
#include"CAnimationTool.h"
#include"CPlayer.h"

// Resource Factory
const CResource* CFactory::CreateResource(RESOURCE _type) const
{
    CResource* tmp = nullptr;
    switch (_type)
    {
    case RESOURCE::RESOURCE_TEXTURE:
        tmp = CTexture::Create();
    }
    return tmp;
}


// Object Factory
const CObject* CFactory::CreateObject(OBJECT _type) const
{
    CObject* tmp = nullptr;
    switch (_type)
    {
    case OBJECT::OBJECT_PLAYER:
        //tmp = CTexture::Create();
        break;
    }
    return tmp;
}

// Scene Factory
const CScene* CFactory::CreateScene(SCENE _type) const
{
    CScene* tmp = nullptr;
    switch (_type)
    {
    case SCENE::SCENE_ANITOOL:
        tmp = CAnimationTool::Create();
        break;
    }
    return tmp;
}
