#include "pch.h"
#include "CSceneMgr.h"
#include "CAnimationTool.h"
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
	

	return 0;
}

int CSceneMgr::Init()
{
	//Create Scene
	m_pCurScene = CFactory<CAnimationTool>::Create();
	
	// Setting Scene
	m_pCurScene->Enter();
	return 0;
}

int CSceneMgr::Release()
{
	m_pCurScene->Release();

	return 0;
}
