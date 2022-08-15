#include "pch.h"
#include "CResourceMgr.h"
#include "CSkin.h"
#include "CComponent.h"
#include "CBackGround.h"

int CBackGround::Setting(const wstring& _str)
{
	CResourceMgr::GetInstance()->FindTexture(_str);
	CObject::CreateTransform(Vector3({ CLIENT_WIDTH * 0.5f, 0 ,0.f }), Vector3({ 0.f,0.f,0.f }), Vector2({ 0.f,0.f }));
	
	// Create Skin and Setting
	CComponent* pComponent = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	pSkin->SetTexture(_str);
	pSkin->SetSkinInfoTexture();
	pSkin->SetOwner(this);
	
	// InsertComponent
	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });

	
	return 0;
}

int CBackGround::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->Render(_dc);
	return 0;
}

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}
