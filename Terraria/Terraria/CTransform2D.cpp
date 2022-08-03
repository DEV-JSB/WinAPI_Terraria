#include "pch.h"
#include "CTransform2D.h"




CTransform2D::CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:CComponent(false)
	,m_vPosition(_pos)
	,m_vRotation(_rot)
	,m_vScale(_scale)
{
}



CTransform2D::~CTransform2D()
{
}

int CTransform2D::Render(const HDC _hdc)
{
	return 0;
}

int CTransform2D::Update(const HDC _hdc)
{
	return 0;
}

int CTransform2D::FinalUpdate(const HDC _hdc)
{
	return 0;
}
