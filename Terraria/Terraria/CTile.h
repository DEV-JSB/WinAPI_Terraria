#pragma once
#include "CObject.h"
#include"CFactory2.h"
#include"CTileMgr.h"

class CTile :
    public CObject
{
public: // SettingLogic

public:// Logic
    virtual int Update()                override;
    virtual int Render(const HDC _dc)   override;
    virtual int FinalUpdate()           override;
private:
    int CreateCollider(const Vector2 _pos);
private:
    // Only Can Setting int CTileManager
    friend class CTileMgr;
    int Setting(TILE _eType, const Vector2 _pos);
private:
    friend class CFactory2;
    CTile();
public:
    ~CTile();
};

