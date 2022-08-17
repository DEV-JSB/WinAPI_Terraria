#include "pch.h"
#include "CItem.h"
#include "CFactory2.h"
#include "CSkin.h"
#include "CResourceMgr.h"

int CItem::m_iIdxKey = 0;

CItem::CItem()
	:m_iItemIndex(m_iIdxKey++)
	,m_strItemTexture(L"")
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
	return 0;
}

CItem::~CItem()
{
}
