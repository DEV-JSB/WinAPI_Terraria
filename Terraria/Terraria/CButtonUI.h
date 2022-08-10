#pragma once
#include "CUI.h"
#include "CFactory.h"
class CButtonUI : public CUI 
{
public:
    // SetParam1 
    int SetParam1(const DWORD_PTR _param) { m_pParam1 = _param; return 0; }
    int SetButtonName(const wstring& _name) { m_strButtonName = _name; return 0; }
    int SetFunc(int(*_pFunc)(DWORD_PTR,DWORD_PTR) , DWORD_PTR _p1 , DWORD_PTR _p2);
public:
    virtual int MouseButtonClicked() override;

    virtual int Update()                override;
    virtual int Render(const HDC _dc)   override;
    virtual int FinalUpdate()           override;
    virtual UI_TYPE GetUIType() override { return m_eUI_Type; }
private:
    // Button wstring
    wstring m_strButtonName;
    // Function Pointer 
    int(*m_pFunc) (DWORD_PTR, DWORD_PTR);
    // For Function P

    // In SceneTool : Animation*
    DWORD_PTR m_pParam1;
    DWORD_PTR m_pParam2;
private:
    HIDE_CONSTRUCTOR(CButtonUI);
    CButtonUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
};

