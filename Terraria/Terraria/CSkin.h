#pragma once
#include "CComponent.h"
#include"CFactory2.h"

class CTexture;
class CObject;

class CSkin : public CComponent
{
public:// Set Func
    int SetTexture(const wstring& _str);
    int SetSkinInfo(const stSkinInfo& _skinInfo) { m_stSkinInfo = _skinInfo; return 0; }
public:// Logic
    virtual int Render(const HDC _dc)const override;
    virtual int Update()                    override;
    virtual int FinalUpdate()               override;
private:
    // Owner
    CObject* m_pOwner;
    // TextureCuttingInfo , LT , SIZE
    stSkinInfo m_stSkinInfo;
    // Texture
    CTexture*   m_pTex;
private:
    friend class CFactory2;
    CSkin(const bool _willrender);
public:
    ~CSkin();
};

