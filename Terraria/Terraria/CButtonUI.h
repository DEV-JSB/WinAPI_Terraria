#pragma once
#include "CUI.h"
#include "CFactory.h"
class CButtonUI :
    public CUI
{
public:
    int SetButtonName(const wstring& _name) { m_strButtonName = _name; return 0; }
    int SetFunc(int(*_pFunc)(DWORD_PTR,DWORD_PTR) , DWORD_PTR _p1 , DWORD_PTR _p2);
public:
    virtual int MouseButtonClicked() override;

    virtual int Update()                override;
    virtual int Render(const HDC _dc)   override;
    virtual int FinalUpdate()           override;
    virtual UI_TYPE GetType() override { return m_eType; }
private:
    // Button wstring
    wstring m_strButtonName;
    // Function Pointer 
    int(*m_pFunc) (DWORD_PTR, DWORD_PTR);
    // For Function P
    DWORD_PTR m_pParam1;
    DWORD_PTR m_pParam2;
private:
    friend class CFactory<CButtonUI>;
    CButtonUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
};

