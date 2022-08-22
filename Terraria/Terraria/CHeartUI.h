#pragma once
#include "CUI.h"
#include "CFactory2.h"
class CHeartUI :
    public CUI
{
public:
    int Render(const HDC _dc);
public:
    int Setting(const int _x, const int _y);
private:
    friend class CFactory2;
    CHeartUI();
public:
    virtual ~CHeartUI();
};

