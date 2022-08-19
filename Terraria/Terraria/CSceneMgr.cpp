#include "pch.h"
#include "CSceneMgr.h"
#include "CAnimationTool.h"
#include "CCollisionMgr.h"
#include "CWorld.h"
#include "CResourceMgr.h"
#include "CFactory.h"
CSceneMgr::CSceneMgr()
	:m_pCurScene(nullptr)
{

}
CSceneMgr::~CSceneMgr()
{
	
}

SCENE CSceneMgr::GetType() const
{
	return m_pCurScene->GetSceneType();
}

const vector<CObject*> CSceneMgr::GetObjectGroup(const OBJECT _eType)
{
	return m_pCurScene->GetObjectGroup(_eType);
}

int CSceneMgr::FinalUpdate()
{
	m_pCurScene->FinalUpdate();
	return 0;
}

int CSceneMgr::Update()
{
	if (nullptr == m_pCurScene)
		return 0;
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
	return 0;
}

int CSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
	return 0;
}


int CSceneMgr::Init()
{
	
	// CreateWorld
	m_pCurScene = CFactory<CWorld>::Create();
	// Create Tool
	//m_pCurScene = CFactory<CAnimationTool>::Create();
	
	m_pCurScene->Enter();
	return 0;
}

int CSceneMgr::Release()
{
	

	m_pCurScene->Release();
	delete m_pCurScene;
	return 0;
}
