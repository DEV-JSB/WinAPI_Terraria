#include "pch.h"
#include "CItemPocketUI.h"
#include "CSkin.h"
#include "CFactory2.h"
#include "CTexture.h"
#include "CTransform2D.h"
#include "CResourceMgr.h"


CItemPocketUI::CItemPocketUI()
	:CUI(UI_TYPE::UI_ITEMPOCKET,true)
	,m_iIndex(0)
	, m_bIsPlayerSelect(false)
	, m_pSkinTmp(nullptr)
{
}


int CItemPocketUI::Setting(const int _x, const int _y)
{
	CUI::m_eUI_Type = UI_TYPE::UI_ITEMPOCKET;

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
	if (m_bIsPlayerSelect)
		m_pSkinTmp->RenderLocalSpace(_dc);
	else
		m_mapComponent[COMPONENT::COMPONENT_SKIN]->RenderLocalSpace(_dc);
	if (m_strItemTexture != L"")
	{
		RenderingItem(_dc);
	}

	return 0;
}

int CItemPocketUI::FinalUpdate()
{
	return 0;
}

int CItemPocketUI::RenderingItem(const HDC _dc)
{
	// Load Item Texture
	CTexture* pTex = CResourceMgr::GetInstance()->FindTexture(m_strItemTexture);

	// Get UI Pos
	CTransform2D* pMyTrans = CObject::GetTransform();
	Vector2 vPos;
	vPos.x = pMyTrans->GetPosition().x;
	vPos.y = pMyTrans->GetPosition().y;

	Vector2 vScale = pMyTrans->GetScale();

	//Get Item Info
	BITMAP bitInfo = pTex->GetBitInfo();

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)bitInfo.bmWidth
		, (int)bitInfo.bmHeight
		, pTex->GetTextureDC()
		, (int)0
		, (int)0
		, (int)bitInfo.bmWidth
		, (int)bitInfo.bmHeight
		, RGB(255, 255, 255));

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


	// Create Another FocusState Skin
	CSkin* pTemp;
	m_pSkinTmp = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	pTemp = RTTI_DYNAMIC_CAST(m_pSkinTmp, CSkin);
	pTemp->SetTexture(L"Inventory_Select.bmp");
	pTemp->SetOwner(this);

	return bmInfo;
}

CItemPocketUI::~CItemPocketUI()
{
	delete m_pSkinTmp;
}

