#pragma once
#include "CComponent.h"
#include"CFactory2.h"
class CSkin : public CComponent
{

public:
    virtual int Render(const HDC _hdc)const override;
    virtual int Update()                    override;
    virtual int FinalUpdate()               override;

private:
    friend class CFactory2;
    CSkin(const bool _willrender);
public:
    ~CSkin();
};

