#include "pch.h"
#include "CCircleCollider.h"
CCircleCollider::CCircleCollider()
	:CCollider(COLLIDER::COLLIDER_CIRCLE)
{
}



int CCircleCollider::Render(const HDC _dc) const
{
	return 0;
}

int CCircleCollider::Update()
{
	return 0;
}

int CCircleCollider::FinalUpdate()
{
	CCollider::FinalUpdate();
	return 0;
}



CCircleCollider::~CCircleCollider()
{
}