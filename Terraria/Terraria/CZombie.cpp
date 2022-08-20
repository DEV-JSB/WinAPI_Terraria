#include "pch.h"
#include "CAnimator.h"
#include "CZombie.h"
#include "CBoxCollider.h"
#include "CTransform2D.h"
// Type , Pos , Scale , Rot 지정


#define MONSTER_WIDTH 32.f
#define MONSTER_HEIGHT 40.f



CZombie::CZombie()
	:CMover(OBJECT::OBJECT_ZOMBIE, Vector3({}), Vector3({}), Vector2({}))
{
	CObject::CreateRigidbody(10.f);

	m_vecMoveDirection = Vector2({ -100.f, 0.f });

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
	CObject::FinalUpdate();

	return 0;
}

int CZombie::Update()
{
	CObject::Update();

	Update_Move();
	Update_Gravity();
	Update_State();
	Update_Animation();
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
	if (CMover::FootRayCast())
	{
		m_bIsOnGround = true;
		printf("땅에있음\n");
	}
	else
		m_bIsOnGround = false;
	if(m_bIsOnGround == true)
		CMover::AddForce(m_vecMoveDirection);

	return 0;
}

int CZombie::Update_Animation()
{
	return 0;
}

int CZombie::Update_State()
{
	return 0;
}

int CZombie::Update_Gravity()
{
	if (!m_bIsOnGround)
	{
		CMover::SetRigidbody(RIGIDBODY::RIGIDBODY_GRAVITY, 90.f);
	}
	else
	{
		CMover::SetRigidbody(RIGIDBODY::RIGIDBODY_GRAVITY, 0.f);
	}
	return 0;
}




CZombie::~CZombie()
{
}
