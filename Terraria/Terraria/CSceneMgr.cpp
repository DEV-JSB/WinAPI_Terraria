#include "pch.h"
#include "CSceneMgr.h"
#include "CAnimationTool.h"
#include"CWorld.h"
#include "CFactory.h"
CSceneMgr::CSceneMgr()
	:m_pCurScene(nullptr)
{

}
CSceneMgr::~CSceneMgr()
{
	
}

int CSceneMgr::Update()
{
	if (nullptr == m_pCurScene)
		return 0;
	m_pCurScene->Update();
	return 0;
}

int CSceneMgr::Render(HDC _hdc)
{
	m_pCurScene->Render(_hdc);
	return 0;
}

int CSceneMgr::Enter()
{
	// Setting Scene
	m_pCurScene->Enter();

	return 0;
}

int CSceneMgr::Init()
{
	
	// CreateWorld
	//m_pCurScene = CFactory<CWorld>::Create();
	// Create Tool
	m_pCurScene = CFactory<CAnimationTool>::Create();

	Enter();
	return 0;
}

int CSceneMgr::Release()
{
	m_pCurScene->Release();
	delete m_pCurScene;
	return 0;
}
