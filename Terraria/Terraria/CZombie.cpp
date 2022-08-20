#include "pch.h"
#include "CAnimator.h"
#include "CZombie.h"
#include "CBoxCollider.h"
#include "CTransform2D.h"
// Type , Pos , Scale , Rot ÁöÁ¤


#define MONSTER_WIDTH 32.f
#define MONSTER_HEIGHT 40.f


CZombie::CZombie()
	:CMover(OBJECT::OBJECT_ZOMBIE, Vector3({}), Vector3({}), Vector2({}))
{

}

int CZombie::Setting(const float _x, const float _y)
{
	CObject::SetPosition(Vector2({ _x,_y }));
	CreateCollider();
	CreateAnimator();
	return 0;
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
	CTransform2D* pTransform = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	RTTI_DYNAMIC_CAST(pBoxCollider, CBoxCollider)->SetInformation(this, Vector2({ pTransform->GetPosition_X(),pTransform->GetPosition_Y() })
		, Vector2({ MONSTER_WIDTH , MONSTER_HEIGHT })
		, Vector2({ 0.f, 0.f }));

	m_mapComponent.insert({ COMPONENT::COMPONENT_COLLIDER , pBoxCollider });
	return 0;
}

int CZombie::CreateAnimator()
{
	CAnimator* pAnimator = CFactory<CAnimator>::Create(true);
	pAnimator->LoadAnimation(L"ZombieAni", L"Zombie.bmp", false);

	pAnimator->SettingPlayAnimation(vector<wstring>({ L"ZombieAni"}));

	m_mapComponent.insert({ COMPONENT::COMPONENT_ANIMATOR,pAnimator });
	pAnimator->SetOwner(this);


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
