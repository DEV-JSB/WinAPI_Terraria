#include "pch.h"
#include "CTransform2D.h"


CTransform2D::CTransform2D()
	:m_vecPosition()
	, m_vecRotation()
	, m_vecScale()
{}

CTransform2D::CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:m_vecPosition(_pos)
	,m_vecRotation(_rot)
	,m_vecScale(_scale)
{
}



CTransform2D::~CTransform2D()
{
}
