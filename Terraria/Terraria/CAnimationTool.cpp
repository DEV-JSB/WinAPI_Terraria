#include "pch.h"
#include "CAnimationTool.h"
#include"CSceneMgr.h"


#include"resource.h"
CAnimationTool* CAnimationTool::Create()
{
    return new CAnimationTool();
}
CAnimationTool::~CAnimationTool()
{
}
int CAnimationTool::Render(const HDC _hdc)
{
	return 0;
}

int CAnimationTool::Update()
{
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
