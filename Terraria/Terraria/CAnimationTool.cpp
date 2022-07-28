#include "pch.h"
// Use Define DIALOG
#include "resource.h"
#include "CAnimationTool.h"
#include "CFactory.h"
#include "CSceneMgr.h"
#include "CUI.h"

CAnimationTool::CAnimationTool()
{
}

CAnimationTool::~CAnimationTool()
{
}

int CAnimationTool::Release()
{
    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (int j = 0; j < (int)m_vecObjectList[i].size(); ++j)
        {
            if (nullptr != m_vecObjectList[i][j])
                delete m_vecObjectList[i][j];
        }
    }
    return 0;
}

int CAnimationTool::Render(const HDC _hdc)
{
    for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
    {
        for (int j = 0; j < (int)m_vecObjectList[i].size(); ++j)
            m_vecObjectList[i][j]->Render(_hdc);
    }
	return 0;
}

int CAnimationTool::Update()
{



	return 0;
}

int CAnimationTool::Enter()
{
    // Create UI Test
    CUI* pUi = CFactory<CUI>::Create(Vector3({ 50.f ,50.f ,0.f}), Vector3({ 50.f ,50.f ,0.f}), Vector2({50.f,50.f }));
    
    m_vecObjectList[(int)OBJECT::OBJECT_UI].push_back(pUi);

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
            TCHAR tChar[255];
            GetDlgItemText(hDlg, IDC_EDIT1, tChar, 255);
            
            CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
            
            //Check Is it Tool scene , -> Only Use In Tool Scene
            CAnimationTool* pToolScene = dynamic_cast<CAnimationTool*>(pCurScene);
            assert(pToolScene);

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
