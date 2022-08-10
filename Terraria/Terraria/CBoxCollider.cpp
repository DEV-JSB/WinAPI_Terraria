#include "pch.h"
#include "CBoxCollider.h"


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
	if (m_bRender)
	{
		Rectangle(_dc, (int)(m_vPos.x - m_vScale.x * 0.5f), (int)(m_vPos.y - m_vScale.y*0.5f)
			, (int)(m_vPos.x + m_vScale.x * 0.5f), (int)(m_vPos.y + m_vScale.y * 0.5f));
	}
	return 0;
}

int CBoxCollider::FinalUpdate()
{
	CCollider::FinalUpdate();
	return 0;
}

int CBoxCollider::Update()
{
	return 0;
}



CBoxCollider::~CBoxCollider()
{
}
