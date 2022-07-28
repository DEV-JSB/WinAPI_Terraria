#pragma once
#include "CObject.h"
#include"CFactory.h"

class CUI :
    public CObject
{
public:
    virtual int Update() override;
    virtual int Render(HDC _dc) override;
    
private:
    friend class CFactory<CUI>;

    CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
    CUI();
public:
    virtual ~CUI();


};

