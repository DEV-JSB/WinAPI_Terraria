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
{

}
CUIManager::~CUIManager()
{
	
}

// Only OneAnimation UI 
int CUIManager::SettingAnimation(CAnimation* pAni)
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	vector<CObject*> vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);


	vector<CUI*> pAniUI = dynamic_cast<CUI*>(vecUI[0])->GetUIGroup(UI_TYPE::UI_ANIMTAION);

	if (1 != pAniUI.size())
		return FUNC_ERROR;
	else
	{
		CAnimationUI* aniUI = dynamic_cast<CAnimationUI*>(pAniUI[0]);
		aniUI->SetAnimation(pAni);
	}
	return 0;
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
	
	return 0;
}

int CUIManager::Render(const HDC _hdc)
{
	//Get UI Objcet Group
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);
	for (size_t i = 0; i < vecUI.size(); ++i)
		vecUI[i]->Render(_hdc);
	return 0;
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
		vector<CUI*>ButtonUI = (dynamic_cast<CUI*>(vecUI[i]))->GetUIGroup(UI_TYPE::UI_BUTTON);
		for (size_t j = 0; j < ButtonUI.size(); ++j)
		{
			pTrans = ButtonUI[j]->GetTransform();
			POINT stMousePos = CInputMgr::GetInstance()->GetMousePos();
			if (CHECK_POS_IN_TRANSRECT(pTrans, stMousePos))
			{
				Focus = true;
				m_pFocusing = (CUI*)vecUI[i];
				printf("器目教 且寸!!\n");
				break;
			}
		}
	}
	if (!Focus && m_pFocusing != nullptr)
	{
		m_pFocusing = nullptr;
		printf("器目教 秦力");
	}

	return 0;
}
