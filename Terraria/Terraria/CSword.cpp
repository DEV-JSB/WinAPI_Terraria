#include "pch.h"
#include "CSword.h"
#include "CAnimator.h"

CSword::CSword()
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
	return 0;
}


CSword::~CSword()
{
}
