#pragma once
#include "CItem.h"
class CTool :
    public CItem
{
public:
    virtual int Render(const HDC _dc)= 0;
    virtual int Update()                override;
private:
    int CreateCollider();
private:
    // Tool Have Damage
    int m_iAttackDamage;
protected:
    CTool(const ITEM_NAME _eItemType);
    virtual ~CTool();
};

