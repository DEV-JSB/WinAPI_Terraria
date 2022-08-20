#include "pch.h"
#include "CAnimator.h"
#include "CZombie.h"
#include "CBoxCollider.h"

// Type , Pos , Scale , Rot ÁöÁ¤


#define MONSTER_WIDTH 32.f
#define MONSTER_HEIGHT 40.f


CZombie::CZombie(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:CMover(OBJECT::OBJECT_ZOMBIE, _pos, _rot, _scale)
{

}
int CZombie::FinalUpdate()
{
	return 0;
}

int CZombie::Update()
{
	CObject::Update();
	return 0;
}

int CZombie::Render(const HDC _dc)
{
	CObject::Render(_dc);

	return 0;
}

int CZombie::OnCollision(const CObject* _pOther)
{
	return 0;
}

int CZombie::OnCollisionEnter(const CObject* _pOther)
{
	return 0;
}

int CZombie::OnCollisionExit(const CObject* _pOther)
{
	return 0;
}

int CZombie::CreateCollider()
{
	CComponent* pBoxCollider = CFactory2::CreateComponent(COMPONENT::COMPONENT_BOXCOLLIDER);
	/*RTTI_DYNAMIC_CAST(pBoxCollider, CBoxCollider)->SetInformation(this, _pos
		, Vector2({ MONSTER_WIDTH , MONSTER_HEIGHT})
		, Vector2({ 0.f,0.f }));*/

	m_mapComponent.insert({ COMPONENT::COMPONENT_COLLIDER , pBoxCollider });
	return 0;
}

int CZombie::CreateAnimator()
{
	CAnimator* pAnimator = CFactory<CAnimator>::Create(true);
	pAnimator->LoadAnimation(L"ZombieAni", L"Zombie.bmp", false);

	pAnimator->SettingPlayAnimation(vector<wstring>({ L"ZombieAni"}));


	return 0;
}

int CZombie::Update_Move()
{
	return 0;
}

int CZombie::Update_Animation()
{
	m_mapComponent[COMPONENT::COMPONENT_ANIMATOR]->Update();
	return 0;
}

int CZombie::Update_State()
{
	return 0;
}

int CZombie::Update_Gravity()
{
	return 0;
}




CZombie::~CZombie()
{
}
