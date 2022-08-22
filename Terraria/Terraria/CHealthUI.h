#pragma once
#include "CUI.h"
#include "CFactory2.h"

class CHeartUI;
class CPlayer;

class CHealthUI :
    public CUI
{
public:// Logic
    virtual int Update()               override;
    virtual int Render(const HDC _dc)  override;

public:
    int SetOwner(CPlayer* _pPlayer) { m_pOwner = _pPlayer; return 0; }

private:
    int CreateHeartUI();
private:
    CPlayer* m_pOwner;
    vector<CHeartUI*> m_vecHeartUI;
private:
    friend class CFactory2;
    CHealthUI();
public:
    virtual ~CHealthUI();
};

