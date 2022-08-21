#include "pch.h"
#include "CSword.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CSceneMgr.h"
#include "CTransform2D.h"
#include "CBoxCollider.h"

CSword::CSword()
	:CTool(ITEM_NAME::ITEM_NAME_MASERSWORD)
{
	m_fCoolTime = 0.2f;
	CreateAnimator();
}

int CSword::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_ANIMATOR]->Render(_dc);
	m_mapComponent[COMPONENT::COMPONENT_COLLIDER]->Render(_dc);

	return 0;
}

int CSword::Update()
{
	CObject::Update();
	UpdateCollider();
	return CItem::Update();
}

int CSword::CreateAnimator()
{
	// Load Weapon Animation	
	CAnimator* pAnimator = CFactory<CAnimator>::Create(true);
	wstring strAnimatorName = L"SwordUseAni";

	pAnimator->LoadAnimation(strAnimatorName, L"SwordUse.bmp",false);

	m_mapComponent.insert({COMPONENT::COMPONENT_ANIMATOR, pAnimator});

	pAnimator->SettingPlayAnimation(vector<wstring>{L"SwordUseAni"});
	pAnimator->SetAnimationDurationRegular(strAnimatorName, m_fCoolTime);

	
	m_iFrameMaxCount = pAnimator->GetCurrentAnimationCount(strAnimatorName);

	CreateCollider(pAnimator, strAnimatorName);

	return 0;
} 

int CSword::UpdateCollider()
{
	CAnimator* pAni = RTTI_DYNAMIC_CAST_MAP(CAnimator, m_mapComponent, COMPONENT::COMPONENT_ANIMATOR);
	const int iAnimationIndex = pAni->GetCurrentPlayIndex(L"SwordUseAni");

	m_mapComponent.erase(COMPONENT::COMPONENT_COLLIDER);
	m_mapComponent.insert({ COMPONENT::COMPONENT_COLLIDER , m_vecCollider[iAnimationIndex] });
	return 0;
}

int CSword::CreateCollider(CAnimator* _pAni,const wstring& _strAniname)
{
	//Get Animator Frame Information
	const vector<stAnimFrame> vecAniFrameInfo = _pAni->GetAnimationFrameInfo(_strAniname);

	CBoxCollider* pCollider = nullptr;
	//For Setting Collider Information
	Vector2 vPos = {0};
	Vector2 vScale;
	Vector2 vOffset;




	for (int i = 0; i < m_iFrameMaxCount; ++i)
	{	
		vScale = vecAniFrameInfo[i].vSliceSize;
		vOffset = vecAniFrameInfo[i].vOffset;
		pCollider = RTTI_DYNAMIC_CAST(CFactory2::CreateComponent(COMPONENT::COMPONENT_BOXCOLLIDER), CBoxCollider);
		pCollider->SetInformation(this, vPos, vScale, vOffset);
		m_vecCollider.push_back(pCollider);
	}
	return 0;
}


CSword::~CSword()
{
}
