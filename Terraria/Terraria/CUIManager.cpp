#include "pch.h"
#include "CUIManager.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include"CObject.h"

CUIManager::CUIManager()
{

}
CUIManager::~CUIManager()
{

}

// UI Update
int CUIManager::Update()
{
	// Need Get UI Objcet Group
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetObjectGroup(OBJECT::OBJECT_UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		//vecUI[i];
	}


	return 0;
}