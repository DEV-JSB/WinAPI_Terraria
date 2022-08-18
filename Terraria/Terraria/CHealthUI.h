#pragma once
#include "CUI.h"
#include "CFactory2.h"
class CHealthUI :
    public CUI
{



private:
    friend class CFactory2;
    CHealthUI();
public:
    virtual ~CHealthUI();
};

