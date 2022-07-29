#include "pch.h"
#include "CResourceMgr.h"
#include "CPathMgr.h"
#include"CTexture.h"

CResourceMgr::CResourceMgr()
{

}

CResourceMgr::~CResourceMgr()
{

}

CTexture* CResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // If this Texture loaded then don't reload
    CTexture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
        return pTex;
      
    wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
    strFilePath += _strRelativePath;

    // Setting New Texture Information
    pTex = CFactory<CTexture>::Create();
    
    pTex->LoadTexture(strFilePath);

    pTex->SetPath(strFilePath);
    pTex->SetKey(_strKey);

    // Insert Map
    m_mapResource.insert({ _strKey,pTex });

    return pTex;
}

CTexture* CResourceMgr::FindTexture(const wstring& _strKey)
{
    auto iter = m_mapResource.find(_strKey);
    // If Can't Find Exeption Handling
    if(m_mapResource.end() == iter)
        return nullptr;
    // Return Texture
    return (CTexture*)(iter->second);
}
