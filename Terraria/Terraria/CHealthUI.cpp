#include "pch.h"
#include "CHealthUI.h"
#include "CResourceMgr.h"
#include "CSkin.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CHeartUI.h"

#define HEALTH_COUNT 5
#define UI_X 1150.f
#define UI_Y 65.f

CHealthUI::CHealthUI()
	:CUI(UI_TYPE::UI_HEALTH, true)
	, m_pOwner(nullptr)
{
	CComponent* pComponent = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	pSkin->SetTexture(L"HeartUI.bmp");
	pSkin->SetOwner(this);

	BITMAP bmInfo = CResourceMgr::GetInstance()->GetTextureSize(L"HeartUI.bmp");


	CObject::CreateTransform(Vector3({ UI_X,UI_Y,0.f })
		, Vector3({})
		, Vector2({ (float)bmInfo.bmWidth,(float)bmInfo.bmHeight }));

	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });

	CreateHeartUI();

}

int CHealthUI::Update()
{
	return 0;
}
int CHealthUI::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->RenderLocalSpace(_dc);
	for (int i = 0; i < m_pOwner->GetHealth(); ++i)
	{
		m_vecHeartUI[i]->Render(_dc);
	}
	return 0;
}

int CHealthUI::CreateHeartUI()
{
	int x = (int)UI_X - 80;
	for (int i = 0; i < HEALTH_COUNT; ++i, x += 39)
	{
		CUI* pUI = CFactory2::CreateUI(UI_TYPE::UI_HEART);
		CHeartUI* pHeart = RTTI_DYNAMIC_CAST(pUI, CHeartUI);
		pHeart->Setting(x, (int)(UI_Y));

		m_vecHeartUI.push_back(pHeart);
	}
	return 0;
}

CHealthUI::~CHealthUI()
{

}