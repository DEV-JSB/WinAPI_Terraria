#include "pch.h"
#include "CItemPocketUI.h"
#include "CSkin.h"
#include "CFactory2.h"
#include "CResourceMgr.h"


CItemPocketUI::CItemPocketUI()
	:CUI(true)
	,m_iIndex(0)
{

}


int CItemPocketUI::Setting(const int _x, const int _y)
{
	BITMAP bitInfo =  CreateSkinComponent();
	CObject::CreateTransform(Vector3({ (float)bitInfo.bmWidth * (float)_x + (float)bitInfo.bmWidth , (float)_y * (float)bitInfo.bmHeight + (float)bitInfo.bmHeight , 0.f })
							, Vector3({})
							, Vector2({ (float)bitInfo.bmWidth, (float)bitInfo.bmHeight }));
	return 0;
}


int CItemPocketUI::Update()
{
		
	return 0;
}

int CItemPocketUI::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->RenderLocalSpace(_dc);
	return 0;
}

int CItemPocketUI::FinalUpdate()
{
	return 0;
}

BITMAP CItemPocketUI::CreateSkinComponent()
{
	CComponent* pComponent = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	pSkin->SetTexture(L"Inventory_Back.bmp");
	pSkin->SetOwner(this);
	BITMAP bmInfo = CResourceMgr::GetInstance()->GetTextureSize(L"Inventory_Back.bmp");

	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });
	return bmInfo;
}

CItemPocketUI::~CItemPocketUI()
{
}

