#include "pch.h"
#include "CUIManager.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CTransform2D.h"
#include"CInputMgr.h"
#include"CObject.h"
#include"CAnimationUI.h"
#include"CButtonUI.h"

CUIManager::CUIManager()
	:m_pFocusing(nullptr)
	,m_eFocusType(UI_TYPE::UI_END)
{

}
CUIManager::~CUIManager()
{
	
}

int CUIManager::Release()
{
	//Get UI Objcet Group
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
		delete vecUI[i];


	return 0;
}

// UI Update
int CUIManager::Update()
{
	// Need Get UI Objcet Group
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		vecUI[i]->Update();
	}

	FoucusingCheck();

	if (nullptr != m_pFocusing && CInputMgr::GetInstance()->IsLBTDown())
	{
		m_pFocusing->MouseButtonClicked();
	}
	return 0;
}

int CUIManager::Render(const HDC _dc)
{
	//Get UI Objcet Group
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);
	for (size_t i = 0; i < vecUI.size(); ++i)
		vecUI[i]->Render(_dc);
	return 0;
}

bool CUIManager::IsFocusingAnything() const
{
	if (nullptr != m_pFocusing)
		return true;
	else
		return false;
}

int CUIManager::FoucusingCheck()
{
	bool Focus = false;
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);
	
	CTransform2D* pTrans;
	POINT stMousePos = CInputMgr::GetInstance()->GetMousePos();
	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// If Mouse Isn't on ParentUI Then BreakOut
		pTrans = vecUI[i]->GetTransform();
		if (!CHECK_POS_IN_TRANSRECT(pTrans,stMousePos))
			break;
		// ////////////////////////////////////////
		vector<CUI*>ButtonUI = (dynamic_cast<CUI*>(vecUI[i]))->GetUIGroup(UI_TYPE::UI_BUTTON);
		for (size_t j = 0; j < ButtonUI.size(); ++j)
		{
			pTrans = ButtonUI[j]->GetTransform();
			POINT stMousePos = CInputMgr::GetInstance()->GetMousePos();
			if (CHECK_POS_IN_TRANSRECT(pTrans, stMousePos))
			{
				Focus = true;
				m_pFocusing = RTTI_DYNAMIC_CAST(ButtonUI[j], CButtonUI);
				m_pFocusing->SetFocus(true);
				m_eFocusType = UI_TYPE::UI_BUTTON;

				break;
			}
		}
	}
	if (!Focus && m_pFocusing != nullptr)
	{
		m_pFocusing->SetFocus(false);
		m_pFocusing = nullptr;
	}

	return 0;
}
