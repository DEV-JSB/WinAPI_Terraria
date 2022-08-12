#include "pch.h"
#include "CMover.h"
#include "CCollider.h"
#include "CBoxCollider.h"
#include "CRigidbody.h"
#include "CCollisionMgr.h"

CMover::CMover(const OBJECT _eType, const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:CObject(_eType,_pos,_rot,_scale)	
{
}

CMover::~CMover()
{
}

bool CMover::FootRayCast()
{
	// Get Collider LB , RB
	CCollider* pCollider = RTTI_DYNAMIC_CAST_MAP(CCollider, m_mapComponent, COMPONENT::COMPONENT_COLLIDER);
	CBoxCollider* pBoxCollider = RTTI_DYNAMIC_CAST(pCollider, CBoxCollider);
	
	POINT LB,RB;
	LB.x = (int)(pBoxCollider->GetPos().x - pBoxCollider->GetScale().x * 0.5f);
	LB.y = (int)(pBoxCollider->GetPos().y + pBoxCollider->GetScale().y * 0.5f) + 1;

	RB.x = (int)(pBoxCollider->GetPos().x + pBoxCollider->GetScale().x * 0.5f);
	RB.y = LB.y;

	if (CCollisionMgr::GetInstance()->CheckingPointOnTile(LB)
		|| CCollisionMgr::GetInstance()->CheckingPointOnTile(RB))
		return true;
	return false;
}

int CMover::SetRigidbody(const RIGIDBODY _eType, float _f)
{
	CRigidbody* pRigidbody = RTTI_DYNAMIC_CAST_MAP(CRigidbody, m_mapComponent, COMPONENT::COMPONENT_RIGIDBODY);
	switch (_eType)
	{
	case RIGIDBODY::RIGIDBODY_FRICTION:
		pRigidbody->SetFriction(_f);
		break;
	case RIGIDBODY::RIGIDBODY_GRAVITY:
		pRigidbody->SetGravityPower(_f);
		break;
	case RIGIDBODY::RIGIDBODY_MASS:
		pRigidbody->SetMass(_f);
		break;
	case RIGIDBODY::RIGIDBODY_MAXSPEED:
		pRigidbody->SetMaxSpeed(_f);
		break;
	}
	return 0;
}


