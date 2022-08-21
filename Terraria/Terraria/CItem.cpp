#include "pch.h"
#include "CItem.h"
#include "CFactory2.h"
#include "CSkin.h"
#include "CResourceMgr.h"
#include "CPlayer.h"
#include "CTransform2D.h"
#include "CFrameMgr.h"
#include "CAnimator.h"


CItem::CItem(const ITEM_NAME _eType)
	:CObject(OBJECT::OBJECT_ITEM)
	, m_eItemCategory(_eType)
	,m_strItemTexture(L"")
	,m_strItemAnimation(L"")
	,m_pOwner(nullptr)
	,m_fCoolTime(0.f)
	,m_fAccumTime(0.f)
	, m_bIsFilp(true)

{
}

int CItem::Update()
{
	m_fAccumTime += (float)GET_DT;
	return 0;
}

int CItem::FinalUpdate()
{
	CObject::FinalUpdate();
	if (m_fAccumTime >= m_fCoolTime)
	{
		auto iter = m_mapComponent.find(COMPONENT::COMPONENT_ANIMATOR);
		if (iter != m_mapComponent.end())
		{
			RTTI_DYNAMIC_CAST((*iter).second, CAnimator)->CurPlayAnimationReset();
		}
		
		m_fAccumTime = 0.f;
		return FINISH;
	}

	return 0;
}

int CItem::SetTexture(const wstring& _str)
{
	CComponent* pComponent= CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	m_strItemTexture = _str;
	pSkin->SetTexture(_str);

	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });
	return 0;
}

CItem::~CItem()
{
}

int CItem::SetAnimatorFlip(const bool _b)
{
	RTTI_DYNAMIC_CAST(m_mapComponent[COMPONENT::COMPONENT_ANIMATOR], CAnimator)->SetFilp(_b);
	return 0;
}

int CItem::SetOwner(CPlayer* _pPlayer)
{
	m_pOwner = _pPlayer;

	CTransform2D* pPlayerTrans = m_pOwner->GetTransform();

	CComponent* pComponent = CFactory<CTransform2D>::Create();
	CTransform2D* pTrans = RTTI_DYNAMIC_CAST(pComponent, CTransform2D);
	*pTrans = *pPlayerTrans;

	RTTI_DYNAMIC_CAST(m_mapComponent[COMPONENT::COMPONENT_ANIMATOR], CAnimator)->SetOwner(_pPlayer);
	m_mapComponent.insert({ COMPONENT::COMPONENT_TRANSFORM2D, pTrans });

	return 0;
}
