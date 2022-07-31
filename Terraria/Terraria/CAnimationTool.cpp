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

#define BIT_BOUNDARY_LINE 50


CAnimationTool::CAnimationTool()
    : m_pAnimation(nullptr)
    , m_pTexture(nullptr)
    , m_stSelectRect({ 0,0,0,0 })
    , m_strFileName({})
    , m_bIsSetRect(false)
    , m_stAniFrame({0})
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
    return false;
}



CAnimationTool::~CAnimationTool()
{
    delete m_pAnimation;
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


int CAnimationTool::SetAnimation()
{
    m_stAniFrame.vLT.x = (float)m_stSelectRect.left;
    m_stAniFrame.vLT.y = (float)m_stSelectRect.top;
    m_stAniFrame.vSliceSize.x = (float)(m_stSelectRect.right - m_stSelectRect.left);
    m_stAniFrame.vSliceSize.y = (float)(m_stSelectRect.bottom - m_stSelectRect.top);

    m_pAnimation->SetAniFrame(m_stAniFrame);
    
    return 0;
}

int CAnimationTool::Release()
{
    // Scene Parent Will Delete All of Object
    delete this;
    return 0;
}

int CAnimationTool::Render(const HDC _hdc)
{

    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (size_t j = 0; j < m_arrObjectVec[i].size(); ++j)
        {
            m_arrObjectVec[i][j]->Render(_hdc);
        }
    }
    if (nullptr == m_pTexture)
        return 0;
    


    // Setting CutBitmap
    if (m_bIsSetRect)
    {
        DrawSelectRect(_hdc);
        if (CheckCutBitmap(_hdc))
        {
            // Save Animation and Can Replace Offset
            m_bIsSetRect = false;
        }
        DrawSelectRect(_hdc);
    }

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

    // MouseUpdate Test
    wstring str;
    POINT p = CInputMgr::GetInstance()->GetMousePos();
    return 0;
    
}

int CAnimationTool::Update()
{
    // Not File Name Setting Exeption handling
    if (m_strFileName.size() == 0)
        return FUNC_ERROR;

    m_pTexture = CResourceMgr::GetInstance()->LoadTexture(m_strFileName, CPathMgr::GetInstance()->GetContentPath());
    
    // Exeption Handling
    if (m_pTexture == nullptr)
    {
        m_strFileName.clear();
        return FUNC_ERROR;
    }

    // UI Update
    CUIManager::GetInstance()->Update();

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


	return 0;
}

int CAnimationTool::Enter()
{
    // Create UI Test
    CUI* pUi = CFactory<CUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f , (float)CLIENT_HEIGHT * 0.5f ,0.f})
                                   , Vector3({ 0.f ,0.f ,0.f})
                                   , Vector2({ 300.f , (float)CLIENT_HEIGHT })
                                   , false);

    CUI* pAnimationUi = CFactory<CAnimationUI>::Create(Vector3({ (float)CLIENT_WIDTH - 150.f , (float)CLIENT_HEIGHT - (float)(CLIENT_HEIGHT * 0.25f),0.f })
                                            , Vector3({ 0.f ,0.f ,0.f })
                                            , Vector2({ 300.f , (float)CLIENT_HEIGHT * 0.5f })
                                            , false);

    pUi->AddChild(pAnimationUi);


    // Add Object in Scene
    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pUi);

    //Create Animation
    m_pAnimation= CFactory<CAnimation>::Create();
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
            TCHAR tChar[255];
            CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
            //Check Is it Tool scene , -> Only Use In Tool Scene
            CAnimationTool* pToolScene = dynamic_cast<CAnimationTool*>(pCurScene);
            assert(pToolScene);
            
            // GetFilename From dialog
            GetDlgItemText(hDlg, IDC_EDIT1, tChar, 255);
            
            pToolScene->SetOpenFileName(tChar);

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
