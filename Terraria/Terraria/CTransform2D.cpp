#include "pch.h"
#include "CTransform2D.h"


CTransform2D::CTransform2D()
	:m_vPosition()
	, m_vRotation()
	, m_vScale()
{}

CTransform2D::CTransform2D(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:m_vPosition(_pos)
	,m_vRotation(_rot)
	,m_vScale(_scale)
{
}



CTransform2D::~CTransform2D()
{
}
