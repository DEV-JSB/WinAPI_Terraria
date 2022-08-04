#include "pch.h"
// Use Define DIALOG
#include "resource.h"
#include "CAnimationTool.h"
#include "CFactory.h"
#include "CUIManager.h"
#include "CAnimationUI.h"
#include "CUI.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CInputMgr.h"
#include "CResourceMgr.h"
#include "CButtonUI.h"

#define BIT_BOUNDARY_LINE 50
#define BIT_BOUNDRAY_LINE 61
#define SAMPLE_ANIMATION_DURATION 0.5f

#define ANI_UI_WIDTH 300.f
#define ANI_UI_HEIGHT

int ChangeOffsetRight   (DWORD_PTR _pAni, DWORD_PTR _pIdx);
int ChangeOffsetDown    (DWORD_PTR _pAni, DWORD_PTR _pIdx);
int ChangeOffsetUp      (DWORD_PTR _pAni, DWORD_PTR _pIdx);
int ChangeOffsetLeft    (DWORD_PTR _pAni, DWORD_PTR _pIdx);
int ChangeIndex         (DWORD_PTR _pAni, DWORD_PTR _pIdx);


CAnimationTool::CAnimationTool()
    : m_pAnimation(nullptr)
    , m_pTexture(nullptr)
    , m_stSelectRect({ 0,0,0,0 })
    , m_strFileName({})
    , m_bIsSetRect(false)
    , m_stAniFrame({0})
    , m_iSettingFrame(0)
    , m_pAnimationUI(nullptr)
{
}


bool CAnimationTool::CheckCutBitmap(const HDC _hdc)
{
    if (!m_bIsSetRect)
        return 0;

    COLORREF rgb;
    RECT CuttingRect = { CLIENT_WIDTH,CLIENT_HEIGHT,0,0 };
    for (int x = m_stSelectRect.left; x <= m_stSelectRect.right; ++x)
    {
        for (int y = m_stSelectRect.top; y <= m_stSelectRect.bottom; ++y)
        {
            rgb = GetPixel(_hdc, x, y);
            if (BIT_BOUNDARY_LINE == GetRValue(rgb)
                && BIT_BOUNDARY_LINE == GetGValue(rgb)
                && BIT_BOUNDARY_LINE == GetBValue(rgb))
            {
                if (CuttingRect.left > x)
                    CuttingRect.left = x;
                else if (CuttingRect.right < x)
                    CuttingRect.right = x;
                if (CuttingRect.top > y)
                    CuttingRect.top = y;
                else if (CuttingRect.bottom < y)
                    CuttingRect.bottom = y;
            }
        }
    }

    // Check Cut is Success
    if (CuttingRect.left != 0 && CuttingRect.right != 0 && CuttingRect.top != 0 && CuttingRect.bottom != 0)
    {
        m_stSelectRect = CuttingRect;  
        SetAnimation();
        return true;
    }
    // Reset Rect
    m_stSelectRect = { 0,0,0,0 };
    return false;
}


int CAnimationTool::DrawSelectRect(const HDC _hdc)
{
    MoveToEx(_hdc, m_stSelectRect.left, m_stSelectRect.top, NULL);
    LineTo(_hdc, m_stSelectRect.right, m_stSelectRect.top);
    LineTo(_hdc, m_stSelectRect.right, m_stSelectRect.bottom);
    LineTo(_hdc, m_stSelectRect.left, m_stSelectRect.bottom);
    LineTo(_hdc, m_stSelectRect.left, m_stSelectRect.top);
    return 0;
}
int CAnimationTool::SetOpenFileName(const wstring& _Key,const wstring& _aniName,const wstring& _objname)
{
    m_strFileName = _Key;

    m_pTexture = CResourceMgr::GetInstance()->LoadTexture(m_strFileName, CPathMgr::GetInstance()->GetContentPath());
    // Exeption Handling
    if (m_pTexture == nullptr)
    {
        m_strFileName.clear();
        return FUNC_ERROR;
    }
    else
    {
        if (m_pAnimationUI->GetAnimationCount() != 0)
        {
            m_pAnimation = CFactory<CAnimation>::Create();
            for (size_t i = 0; i < m_vecBtnUI.size(); ++i)
            {
                m_vecBtnUI[i]->SetParam1((DWORD_PTR)m_pAnimation);
            }

        }
        // Input Texture In Animation
        m_pAnimation->SetTexture(m_pTexture);
        // Setting Animation Name
        m_pAnimation->SetAnimationName(_aniName);
        // Input Animation In UI
        m_pAnimationUI->SetAnimation(m_pAnimation);
    }
    return 0;
}

int CAnimationTool::SetAnimation()
{
    // SetAnimation Frame
    m_stAniFrame.vLT.x = (float)m_stSelectRect.left;
    m_stAniFrame.vLT.y = (float)m_stSelectRect.top;
    m_stAniFrame.vSliceSize.x = (float)(m_stSelectRect.right - m_stSelectRect.left);
    m_stAniFrame.vSliceSize.y = (float)(m_stSelectRect.bottom - m_stSelectRect.top);

    // SetAnimation Duration Time
    m_stAniFrame.fDuration = SAMPLE_ANIMATION_DURATION;

    // SetAnimation
    m_pAnimation->SetAniFrame(m_stAniFrame);

    return 0;
}



int CAnimationTool::Render(const HDC _hdc)
{
    if (nullptr == m_pTexture)
        return 0;
    TransparentBlt(_hdc
        , 0
        , 0
        , m_pTexture->GetBitInfo().bmWidth
        , m_pTexture->GetBitInfo().bmHeight
        , m_pTexture->GetTextureDC()
        , 0
        , 0
        , m_pTexture->GetBitInfo().bmWidth
        , m_pTexture->GetBitInfo().bmHeight
        , NULL);

    // Setting CutBitmap
    if (m_bIsSetRect)
    {
        if (CheckCutBitmap(_hdc))
        {
            // Save Animation and Can Replace Offset
            m_bIsSetRect = false;
        }
    }
    
    DrawSelectRect(_hdc);
    
    //UI Rendering
    CUIManager::GetInstance()->Render(_hdc);
    return 0;
    
}

int CAnimationTool::Update()
{
    // Not File Name Setting Exeption handling
    if (m_strFileName.size() == 0)
        return FUNC_ERROR;


    // UI Update
    CUIManager::GetInstance()->Update();


    if (!CUIManager::GetInstance()->IsFocusingAnything())
    {
        // SetRect Follow MouseDrag
        if (CInputMgr::GetInstance()->IsLBTDown())
        {
            m_stSelectRect.left = CInputMgr::GetInstance()->GetMousePos().x;
            m_stSelectRect.top = CInputMgr::GetInstance()->GetMousePos().y;
            m_bIsSetRect = false;
        }
        if (CInputMgr::GetInstance()->IsLBTUp())
        {
            m_stSelectRect.right = CInputMgr::GetInstance()->GetMousePos().x;
            m_stSelectRect.bottom = CInputMgr::GetInstance()->GetMousePos().y;
            m_bIsSetRect = true;
        }
    }
	return 0;
}

int CAnimationTool::SaveAnimation()
{
    vector<CAnimation*> vecAnimation = m_pAnimationUI->GetAniVector();

    for (size_t i = 0; i < vecAnimation.size(); ++i)
    {
        vecAnimation[i]->SaveFile();
    }

    Release();
    Enter();
    return 0;
}


int CAnimationTool::SettingUI()
{
    // Create UI Test
    CUI* pUi = CFactory<CUI>::Create(Vector3({ (float)CLIENT_WIDTH - ANI_UI_WIDTH * 0.5f , (float)CLIENT_HEIGHT * 0.5f ,0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ ANI_UI_WIDTH , (float)CLIENT_HEIGHT })
        , false);
    
    // Animation UI
    m_pAnimationUI = CFactory<CAnimationUI>::Create(Vector3({ (float)CLIENT_WIDTH - ANI_UI_WIDTH * 0.5f , (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.25f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ ANI_UI_WIDTH , (float)CLIENT_HEIGHT * 0.5f })
        , false);
    pUi->AddChild(m_pAnimationUI);
    
    // Button UI 1
    CButtonUI* pBtnUi = CFactory<CButtonUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f, (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.9f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ 80.f , 40.f })
        , false);
    pBtnUi->SetButtonName(L"OFF_UP");
    pBtnUi->SetFunc(ChangeOffsetUp, (DWORD_PTR)m_pAnimation, (DWORD_PTR)&m_iSettingFrame);
    pUi->AddChild(pBtnUi);

    m_vecBtnUI.push_back(pBtnUi);

    // Button UI 2
    pBtnUi = CFactory<CButtonUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f , (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.8f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ 80.f , 40.f })
        , false);
    pBtnUi->SetFunc(ChangeOffsetDown, (DWORD_PTR)m_pAnimation, (DWORD_PTR)&m_iSettingFrame);
    pBtnUi->SetButtonName(L"OFF_DOWN");
    pUi->AddChild(pBtnUi);

    m_vecBtnUI.push_back(pBtnUi);

    // Button UI 3
    pBtnUi = CFactory<CButtonUI>::Create(Vector3({ (float)CLIENT_WIDTH - ANI_UI_WIDTH + (float)(150.f * 0.3f) ,(float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.85f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ 80.f , 40.f })
        , false);
    pBtnUi->SetFunc(ChangeOffsetLeft, (DWORD_PTR)m_pAnimation, (DWORD_PTR)&m_iSettingFrame);
    pBtnUi->SetButtonName(L"OFF_LEFT");
    pUi->AddChild(pBtnUi);

    m_vecBtnUI.push_back(pBtnUi);

    // Button UI 4
    pBtnUi = CFactory<CButtonUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f + (float)(150.f * 0.7f), (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.85f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ 80.f , 40.f })
        , false);
    pBtnUi->SetFunc(ChangeOffsetRight, (DWORD_PTR)m_pAnimation, (DWORD_PTR)&m_iSettingFrame);
    pBtnUi->SetButtonName(L"OFF_RIGHT");
    pUi->AddChild(pBtnUi);

    m_vecBtnUI.push_back(pBtnUi);

    // Button Switching Index
    pBtnUi = CFactory<CButtonUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f + (float)(150.f * 0.7f), (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.6f),0.f })
        , Vector3({ 0.f ,0.f ,0.f })
        , Vector2({ 80.f , 40.f })
        , false);
    pBtnUi->SetFunc(ChangeIndex, (DWORD_PTR)m_pAnimation, (DWORD_PTR)&m_iSettingFrame);
    pBtnUi->SetButtonName(L"PartChange");
    pUi->AddChild(pBtnUi);

    m_vecBtnUI.push_back(pBtnUi);

    // Add Object in Scene
    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pUi);

    return 0;
}
int CAnimationTool::Enter()
{
    //Create Animation
    m_pAnimation = CFactory<CAnimation>::Create();
    SettingUI();
    return 0;
}

int CAnimationTool::FinalUpdate()
{
    return 0;
}


int CAnimationTool::Release()
{
    // Object Will Delete In Scene
    vector<CAnimation*> vecAnimation = m_pAnimationUI->GetAniVector();
    Delete_Vec(vecAnimation);
    m_pAnimationUI->ResetAnimationVec();
    // Scene Parent Will Delete All of Object
    return 0;
}



CAnimationTool::~CAnimationTool()
{
}


int ChangeIndex(DWORD_PTR _pAni, DWORD_PTR _pIdx)
{
    int MaxIdx = ((CAnimation*)_pAni)->GetFrameCount();
    if (MaxIdx < (*(int*)_pIdx) + 1)
        *(int*)_pIdx = 0;
    else
        ++(*(int*)_pIdx);
    return 0;
}

int ChangeOffsetUp(DWORD_PTR _pAni, DWORD_PTR _pIdx)
{
    CAnimation* pAni = (CAnimation*)_pAni;
    if (0 == pAni->GetFrameCount())
        return 0;
    int Idx = *(int*)_pIdx;
    Vector2 FrameOffset = ((CAnimation*)_pAni)->GetOffset(Idx);
    --FrameOffset.y;
    ((CAnimation*)_pAni)->ReposOffset(Idx, FrameOffset);
    return 0;
}
int ChangeOffsetDown(DWORD_PTR _pAni, DWORD_PTR _pIdx)
{
    CAnimation* pAni = (CAnimation*)_pAni;
    if (0 == pAni->GetFrameCount())
        return 0;
    int Idx = *(int*)_pIdx;
    Vector2 FrameOffset = ((CAnimation*)_pAni)->GetOffset(Idx);
    ++FrameOffset.y;
    ((CAnimation*)_pAni)->ReposOffset(Idx, FrameOffset);
    return 0;
}
int ChangeOffsetLeft(DWORD_PTR _pAni, DWORD_PTR _pIdx)
{
    CAnimation* pAni = (CAnimation*)_pAni;
    if (0 == pAni->GetFrameCount())
        return 0;
    int Idx = *(int*)_pIdx;
    Vector2 FrameOffset = ((CAnimation*)_pAni)->GetOffset(Idx);
    --FrameOffset.x;
    ((CAnimation*)_pAni)->ReposOffset(Idx, FrameOffset);
    return 0;
}
int ChangeOffsetRight(DWORD_PTR _pAni, DWORD_PTR _pIdx)
{
    CAnimation* pAni = (CAnimation*)_pAni;
    if (0 == pAni->GetFrameCount())
        return 0;
    int Idx = *(int*)_pIdx;
    Vector2 FrameOffset = ((CAnimation*)_pAni)->GetOffset(Idx);
    ++FrameOffset.x;
    ((CAnimation*)_pAni)->ReposOffset(Idx, FrameOffset);
    return 0;
}

// ==========================================
// This is Tool Proc , Not Member Function
// ==========================================
INT_PTR CALLBACK AnimationToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            // FileName
            TCHAR tChar[255] = { L"\0" };;
            TCHAR tChar2[255] = { L"\0" };
            TCHAR tChar3[255] = { L"\0" };

            CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();    
            //Check Is it Tool scene , -> Only Use In Tool Scene
            CAnimationTool* pToolScene = dynamic_cast<CAnimationTool*>(pCurScene);
            assert(pToolScene);
            
            // GetFilename From dialog
            GetDlgItemText(hDlg, IDC_EDIT1, tChar, 255);
            GetDlgItemText(hDlg, IDC_EDIT2, tChar2, 255);
            GetDlgItemText(hDlg, IDC_EDIT3, tChar3, 255);

            pToolScene->SetOpenFileName(tChar, tChar2, tChar3);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SaveAnimationProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
            //Check Is it Tool scene , -> Only Use In Tool Scene
            CAnimationTool* pToolScene = dynamic_cast<CAnimationTool*>(pCurScene);
            assert(pToolScene);

            pToolScene->SaveAnimation();

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

