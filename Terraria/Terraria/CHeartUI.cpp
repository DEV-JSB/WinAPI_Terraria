#include "pch.h"
#include "CHeartUI.h"
#include "CResourceMgr.h"
#include "CSkin.h"

CHeartUI::CHeartUI()
	:CUI(UI_TYPE::UI_HEALTH,true)
{
}


int CHeartUI::Setting(const int _x, const int _y)
{
	BITMAP bmInfo = CResourceMgr::GetInstance()->GetTextureSize(L"Heart.bmp");

	CObject::CreateTransform(Vector3({ (float)_x , (float)_y  , 0.f })
		, Vector3({})
		, Vector2({ (float)bmInfo.bmWidth, (float)bmInfo.bmHeight }));


	CComponent* pComponent = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	pSkin->SetTexture(L"Heart.bmp");
	pSkin->SetOwner(this);

	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });


	return 0;
}

int CHeartUI::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->RenderLocalSpace(_dc);
	return 0;
}

CHeartUI::~CHeartUI()
{
}
