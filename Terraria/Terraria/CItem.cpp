#include "pch.h"
#include "CItem.h"
#include "CFactory2.h"
#include "CSkin.h"
#include "CResourceMgr.h"

int CItem::m_iIdxKey = 0;

CItem::CItem()
	:CObject(OBJECT::OBJECT_ITEM)
	,m_iItemIndex(m_iIdxKey++)
	,m_strItemTexture(L"")
	,m_pOwner(nullptr)
{
}

int CItem::Render(const HDC _dc)
{
	return 0;
}

int CItem::Update()
{
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
