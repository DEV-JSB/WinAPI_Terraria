#include "pch.h"
#include "CObject.h"
#include "CFactory.h"
#include "CCollider.h"
#include "CComponent.h"
#include "CTransform2D.h"
#include "CRigidbody.h"

CObject::CObject(const OBJECT _eTpye)
	:m_eType(_eTpye)
	,m_bIsDead(false)
{
}

CObject::CObject(const OBJECT _eType,const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:m_eType(_eType)
{
	CreateTransform(_pos,_rot,_scale);
}

int CObject::CreateTransform(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
{
	CTransform2D* pTransform = CFactory<CTransform2D>::Create(_pos, _rot, _scale);
	// Exception Hending
	assert(pTransform);
	m_mapComponent.insert({ COMPONENT::COMPONENT_TRANSFORM2D,pTransform });
	return 0;
}

int CObject::CreateRigidbody(const float _fMaxSpeed)
{
	CRigidbody* pRigidbody = CFactory<CRigidbody>::Create();
	assert(pRigidbody);
	pRigidbody->SetOwner(this);
	pRigidbody->SetMaxSpeed(_fMaxSpeed);
	m_mapComponent.insert({ COMPONENT::COMPONENT_RIGIDBODY,pRigidbody });
	return 0;
}

int CObject::Update()
{
	for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		(*iter).second->Update();
	}
	return 0;
}

int CObject::FinalUpdate()
{
	for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		(*iter).second->FinalUpdate();
	}
	return 0;
}

int CObject::Render(HDC _dc)
{
	// Component Rendering Test
	for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		(*iter).second->Render(_dc);
	}
	return 0;
}


CCollider* CObject::GetCollider() const
{
	auto iter = m_mapComponent.find(COMPONENT::COMPONENT_COLLIDER);
	// Exeption handling
	if (iter == m_mapComponent.end())
		return nullptr;
	else
	{
		CCollider* pCollider = dynamic_cast<CCollider*>(iter->second);
		return pCollider;
	}
		
}

CTransform2D* CObject::GetTransform() const
{
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	// Exeption handling
	assert(pTrans);
	return pTrans;
}

CRigidbody* CObject::GetRigidbody() const
{
	CRigidbody* pRigid = RTTI_DYNAMIC_CAST_MAP(CRigidbody, m_mapComponent, COMPONENT::COMPONENT_RIGIDBODY);
	// Exeption handling
	assert(pRigid);

	return pRigid;
}



int CObject::SetPosition(const Vector3 _pos)
{
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST_MAP(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
	// Exeption handling
	assert(pTrans);
	pTrans->SetPosition(_pos);
	
	return 0;
}

int CObject::SetPosition(const Vector2 _pos)
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

int CObject::AddForce(const Vector2 _force)
{
	CRigidbody* pRigid = RTTI_DYNAMIC_CAST_MAP(CRigidbody, m_mapComponent, COMPONENT::COMPONENT_RIGIDBODY);
	// Exeption handling
	assert(pRigid);
	pRigid->AddForce(_force);
	return 0;
}




CObject::~CObject()
{
	for (auto iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		if (nullptr != (*iter).second)
		{
			delete (*iter).second;
		}
	}
	m_mapComponent.clear();
}
