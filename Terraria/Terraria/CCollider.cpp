#include "pch.h"
#include "CCollider.h"
#include "CTransform2D.h"
#include "CObject.h"


UINT CCollider::g_iIdValue = 0;

int CCollider::FinalUpdate()
{
	Vector3 OwnerPos = m_pOwner->GetTransform()->GetPosition();

	m_vPos.x = OwnerPos.x;
	m_vPos.y = OwnerPos.y;
 	return 0;
}

CCollider::CCollider(COLLIDER _eType)
	:CComponent(false)
	, m_eType(_eType)
	, m_pOwner(nullptr)
	, m_vPos(Vector2({ 0.f,0.f }))
	, m_iID(g_iIdValue++)
{
}

CCollider::~CCollider()
{
}
