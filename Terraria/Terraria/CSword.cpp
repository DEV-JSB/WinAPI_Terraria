#include "pch.h"
#include "CSword.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CBoxCollider.h"

CSword::CSword()
	:CTool(ITEM_NAME::ITEM_NAME_MASERSWORD)
{
	m_fCoolTime = 0.22f;
	CreateAnimator();
}

int CSword::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_ANIMATOR]->Render(_dc);
	return 0;
}

int CSword::Update()
{
	CObject::Update();
	return CItem::Update();
}

int CSword::CreateAnimator()
{
	CAnimator* pAnimator = CFactory<CAnimator>::Create(true);
	// Load Weapon Animation

	pAnimator->LoadAnimation(L"SwordUseAni", L"SwordUse.bmp",false);

	m_mapComponent.insert({COMPONENT::COMPONENT_ANIMATOR, pAnimator});

	pAnimator->SettingPlayAnimation(vector<wstring>{L"SwordUseAni"});
	pAnimator->SetAnimationDurationRegular(L"SwordUseAni", m_fCoolTime);

	
	m_iFrameMaxCount = pAnimator->GetCurrentAnimationCount(L"SwordUseAni");

	return 0;
}

int CSword::UpdateCollider()
{
	return 0;
}

int CSword::CreateCollider()
{
	CBoxCollider* pCollider;

	//For Setting Collider Information
	Vector2 vPos;
	Vector2 vScale;
	Vector2 vOffset;

	for (int i = 0; i < m_iFrameMaxCount; ++i)
	{
		pCollider = RTTI_DYNAMIC_CAST(CFactory2::CreateComponent(COMPONENT::COMPONENT_BOXCOLLIDER),CBoxCollider);
		//pCollider->SetInformation(this,)
	}
	return 0;
}


CSword::~CSword()
{
}
