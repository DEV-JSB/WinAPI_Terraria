#include "pch.h"
// Use Define DIALOG
#include "resource.h"
#include "CAnimationTool.h"
#include "CFactory.h"
#include "CUI.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CResourceMgr.h"

CAnimationTool::CAnimationTool()
    :m_pWillMake(nullptr)
    ,m_pTexture(nullptr)
{
}

CAnimationTool::~CAnimationTool()
{
    delete m_pWillMake;
}

int CAnimationTool::Release()
{
    // Scene Parent Will Delete All of Object
    delete this;
    return 0;
}

int CAnimationTool::Render(const HDC _hdc)
{
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
    return 0;
    
}

int CAnimationTool::Update()
{
    // Not File Name Setting Exeption handling
    if (m_strFileName.size() == 0)
        return 1;
    
    m_pTexture = CResourceMgr::GetInstance()->FindTexture(m_strFileName);

	return 0;
}

int CAnimationTool::Enter()
{
    // Create UI Test
    CUI* pUi = CFactory<CUI>::Create(Vector3({ CLIENT_WIDTH - 50 ,CLIENT_HEIGHT * 0.5f ,0.f})
                                   , Vector3({ 0.f ,0.f ,0.f})
                                   , Vector2({(float)CLIENT_WIDTH / 2,(float)CLIENT_HEIGHT }));
    
    // Create Child UI Test
    CUI* pChildUi = CFactory<CUI>::Create(Vector3({ CLIENT_WIDTH - 50 ,CLIENT_HEIGHT * 0.25f ,0.f })
                                        , Vector3({ 0.f ,0.f ,0.f })
                                        , Vector2({ (float)CLIENT_WIDTH / 2,(float)100 }));
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
