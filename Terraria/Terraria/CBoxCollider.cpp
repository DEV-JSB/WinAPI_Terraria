#include "pch.h"
#include "CBoxCollider.h"


CBoxCollider::CBoxCollider()
	: CCollider(COLLIDER::COLLIDER_CIRCLE)
	,m_vOffset(Vector2({0.f,0.f}))
	,m_vScale(Vector2({ 0.f,0.f }))

{
}

int CBoxCollider::Render(const HDC _dc) const
{
	return 0;
}

int CBoxCollider::FinalUpdate()
{
	return 0;
}

int CBoxCollider::Update()
{
	return 0;
}



CBoxCollider::~CBoxCollider()
{
}
