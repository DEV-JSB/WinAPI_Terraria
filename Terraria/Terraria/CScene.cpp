#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include"CUIManager.h"
#include"CResourceMgr.h"
#include"CTileMgr.h"
CScene::CScene()
{
	// InputList
	for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
		m_arrObjectVec[i];

}

CPlayer* CScene::GetPlayer() const
{
	CObject* pObj = m_arrObjectVec[(int)OBJECT::OBJECT_PLAYER].front();
	assert(pObj);

	return RTTI_DYNAMIC_CAST(pObj,CPlayer);
}

CScene::~CScene()
{
	for (int i = 0; i < (int)OBJECT::OBJECT_UI; ++i)
	{
		Delete_Vec<CObject*>(m_arrObjectVec[i]);
	}
	CResourceMgr::GetInstance()->Release();
	CUIManager::GetInstance()->Release();
	CTileMgr::GetInstance()->Release();
}

