#include "pch.h"
#include "CBoxCollider.h"
#include"CCamera.h"

CBoxCollider::CBoxCollider()
	: CCollider(COLLIDER::COLLIDER_RECT)
	,m_vOffset(Vector2({0.f,0.f}))
	,m_vScale(Vector2({ 0.f,0.f }))
{
}

int CBoxCollider::SetInformation(CObject* _pObj, const Vector2& _pos, const Vector2& _scale, const Vector2& _offset)
{
	CCollider::SetOwner(_pObj);
	CCollider::m_vPos = _pos;
	m_vScale = _scale;
	m_vOffset = _offset;
	
	return 0;
}

int CBoxCollider::Render(const HDC _dc) const
{
	if (true)
	{
		Vector2 RenderPos = CCamera::GetInstance()->GetDifference();
		Rectangle(_dc
			, (int)(m_vPos.x - m_vScale.x * 0.5f) + (int)RenderPos.x
			, (int)(m_vPos.y - m_vScale.y * 0.5f) + (int)RenderPos.y
			, (int)(m_vPos.x + m_vScale.x * 0.5f) + (int)RenderPos.x
			, (int)(m_vPos.y + m_vScale.y * 0.5f) + (int)RenderPos.y);
	}
	return 0;
}

int CBoxCollider::FinalUpdate()
{
	CCollider::FinalUpdate();
	m_vPos.x += m_vOffset.x;
	m_vPos.y += m_vOffset.y;

	return 0;
}

int CBoxCollider::Update()
{
	
	return 0;
}



CBoxCollider::~CBoxCollider()
{
}
