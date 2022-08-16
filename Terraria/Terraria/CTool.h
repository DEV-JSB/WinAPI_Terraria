#pragma once
#include "CItem.h"
class CTool :
    public CItem
{


private:
    // Tool Have Damage
    int m_iAttackDamage;
protected:
    CTool();
    virtual ~CTool();
};

