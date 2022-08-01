#include "pch.h"
#include "CObject.h"
#include "CFactory.h"
#include "CTransform2D.h"

CObject::CObject()
{
}

CObject::CObject(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
{
	CTransform2D* pTransform = CFactory<CTransform2D>::Create(_pos, _rot, _scale);
	// Exception Hending
	assert(pTransform);
	m_mapComponent.insert({ COMPONENT::COMPONENT_TRANSFORM2D,pTransform });
}


int CObject::Update()
{
	return 0;
}

int CObject::Render(HDC _dc)
{
	return 0;
}


CTransform2D* CObject::GetTransform() const
{
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	// Exeption handling
	assert(pTrans);

	return pTrans;
}

int CObject::SetTransform(const Vector3 _pos)
{
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	// Exeption handling
	assert(pTrans);
	pTrans->SetPosition(_pos);
	
	return 0;
}

int CObject::SetScale(const Vector2 _scale)
{
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	// Exeption handling
	assert(pTrans);
	pTrans->SetScale(_scale);
	
	return 0;
}




CObject::~CObject()
{
	for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		if (nullptr != (*iter).second)
			delete (*iter).second;
	}
	
}
