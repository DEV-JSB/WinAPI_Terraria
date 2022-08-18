#pragma once
#include "CItem.h"
class CTool :
    public CItem
{


private:
    // Tool Have Damage
    int m_iAttackDamage;
    int CreateCollider();
protected:
    CTool();
    virtual ~CTool();
};

