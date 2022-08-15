#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTransform2D.h"
#include "CSceneMgr.h"
CCamera::CCamera()
	: m_vLookAt({})
	, m_vDifference({})
	, m_vResolution({})
	, m_pTarget(nullptr)
{
	
}

CCamera::~CCamera()
{

}

int CCamera::Update()
{
	if (m_pTarget != nullptr)
	{
		Vector3 vPos = m_pTarget->GetTransform()->GetPosition();
		m_vLookAt.x = vPos.x;
		m_vLookAt.y = vPos.y;
		//m_vDifference = Vector2({ 0.f,0.f });
		m_vDifference = m_vResolution - m_vLookAt;
	}
	

	return 0;
}

int CCamera::Init()
{
	m_pTarget = SettingTargetPlayer();
	POINT pResolution = CEngine::GetInstance()->GetResolution();
	m_vResolution.x = (float)pResolution.x;
	m_vResolution.y = (float)pResolution.y;
	m_vResolution /= 2;
	return 0;
}

CObject* CCamera::SettingTargetPlayer()
{
	if (CSceneMgr::GetInstance()->GetType() == SCENE::SCENE_ANITOOL)
		return nullptr;
	vector<CObject*> vecPlayer = CSceneMgr::GetInstance()->GetObjectGroup(OBJECT::OBJECT_PLAYER);
	return vecPlayer[0];;
}
