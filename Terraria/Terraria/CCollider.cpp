#include "pch.h"
#include "CCollider.h"

CCollider::CCollider()
	:CComponent(false)
	,m_pOwner(nullptr)
	,m_vPos(Vector2({0.f,0.f}))
{
}

CCollider::~CCollider()
{
}
