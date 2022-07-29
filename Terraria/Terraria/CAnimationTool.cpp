#include "pch.h"
// Use Define DIALOG
#include "resource.h"
#include "CAnimationTool.h"
#include "CFactory.h"
#include "CUI.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CInputMgr.h"
#include "CResourceMgr.h"

CAnimationTool::CAnimationTool()
    :m_pWillMake(nullptr)
    ,m_pTexture(nullptr)
    ,m_stSelectRect({0,0,0,0})
    ,m_strFileName({})
{
}

CAnimationTool::~CAnimationTool()
{
    delete m_pWillMake;
}
 

int CAnimationTool::DrawSelectRect(const HDC _hdc)
{
    MoveToEx(_hdc, m_stSelectRect.left, m_stSelectRect.right, NULL);
    LineTo(_hdc, m_stSelectRect.right, m_stSelectRect.bottom);
    LineTo(_hdc, m_stSelectRect.bottom, m_stSelectRect.left);
    LineTo(_hdc, m_stSelectRect.left, m_stSelectRect.top);
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
    
    
    DrawSelectRect(_hdc);

    // MouseUpdate Test
    wstring str;
    POINT p = CInputMgr::GetInstance()->GetMousePos();
    return 0;
    
}

int CAnimationTool::Update()
{
    // Not File Name Setting Exeption handling
    if (m_strFileName.size() == 0)
        return 1;
    
    m_pTexture = CResourceMgr::GetInstance()->LoadTexture(m_strFileName, CPathMgr::GetInstance()->GetContentPath());

    // SetRect Follow MouseDrag
    if (CInputMgr::GetInstance()->IsLBTDown())
    {
        m_stSelectRect.left = CInputMgr::GetInstance()->GetMousePos().x;
        m_stSelectRect.top = CInputMgr::GetInstance()->GetMousePos().y;
        printf("LBT_DOWN! \n");
    }
    if (CInputMgr::GetInstance()->IsLBTUp())
    {
        m_stSelectRect.right = CInputMgr::GetInstance()->GetMousePos().x;
        m_stSelectRect.bottom = CInputMgr::GetInstance()->GetMousePos().y;
        printf("LBT_UP! \n");

    }


	return 0;
}

int CAnimationTool::Enter()
{
    // Create UI Test
    CUI* pUi = CFactory<CUI>::Create(Vector3({ CLIENT_WIDTH - 50 ,CLIENT_HEIGHT * 0.5f ,0.f})
                                   , Vector3({ 0.f ,0.f ,0.f})
                                   , Vector2({(float)CLIENT_WIDTH / 2,(float)CLIENT_HEIGHT })
                                   , false);
    // Create Child UI Test
    CUI* pChildUi = CFactory<CUI>::Create(Vector3({ CLIENT_WIDTH - 50 ,CLIENT_HEIGHT * 0.25f ,0.f })
                                        , Vector3({ 0.f ,0.f ,0.f })
                                        , Vector2({ (float)CLIENT_WIDTH / 2,(float)100 })
                                        , false);
    // Push Child UI
    pUi->AddChild(pChildUi);

    // Add Object in Scene
    m_arrObjectVec[(int)OBJECT::OBJECT_UI].push_back(pUi);

    m_pWillMake = CFactory<CAnimation>::Create();
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
