#include "pch.h"
#include "CCollider.h"



UINT CCollider::g_iIdValue = 0;

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
