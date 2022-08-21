#pragma once
#include "CItem.h"
class CTool :
    public CItem
{
public:
    virtual int Render(const HDC _dc)= 0;
    virtual int Update()                override;
    virtual int SetOwner(CPlayer* _pPlayer)override = 0;
    virtual int FinalUpdate()			override    = 0;

private:
    int CreateCollider();
private:
    // Tool Have Damage
    int m_iAttackDamage;
protected:
    CTool(const ITEM_NAME _eItemType);
    virtual ~CTool();
};

