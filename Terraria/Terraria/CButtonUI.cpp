#include "pch.h"
#include "CButtonUI.h"
#include"CTransform2D.h"

int CButtonUI::Update()
{
    return 0;
}
int CButtonUI::Render(const HDC _dc)
{
    CUI::Render(_dc);
    CTransform2D* pTrans = CUI::GetTransform();
    TextOut(_dc, (int)(pTrans->GetPosition_X() - pTrans->GetScale_Width() * 0.5f)
               , (int)(pTrans->GetPosition_Y() - pTrans->GetScale_Height() * 0.5f)
               , m_strButtonName.c_str()
               , m_strButtonName.length());

    return 0;
}

int CButtonUI::FinalUpdate()
{
    CUI::FinalUpdate();
    return 0;
}
int CButtonUI::SetFunc(int(*_pFunc)(DWORD_PTR, DWORD_PTR), DWORD_PTR _p1, DWORD_PTR _p2)
{
    m_pFunc = _pFunc;
    m_pParam1 = _p1;
    m_pParam2 = _p2;
    return 0;
}
int CButtonUI::MouseButtonClicked()
{
    if (nullptr != m_pFunc)
        m_pFunc(m_pParam1,m_pParam2);
    return 0;
}
CButtonUI::CButtonUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected)
    : CUI(_pos, _rot, _scale, _bAffected)
    , m_pFunc(nullptr)
    , m_strButtonName({})
{
    m_eType = UI_TYPE::UI_BUTTON;
}
