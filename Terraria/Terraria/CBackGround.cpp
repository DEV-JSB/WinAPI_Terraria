#include "pch.h"
#include "CResourceMgr.h"
#include "CSkin.h"
#include "CCamera.h"
#include "CComponent.h"
#include "CTexture.h"
#include "CBackGround.h"

CBackGround::CBackGround()
	:CObject(OBJECT::OBJECT_BACKGROUND)

{
}

int CBackGround::Setting(const wstring& _str)
{
	CTexture* pTex = CResourceMgr::GetInstance()->FindTexture(_str);
	BITMAP bitInfo = pTex->GetBitInfo();
	CObject::CreateTransform(Vector3({ (float)CLIENT_WIDTH * 0.5f, (float)CLIENT_HEIGHT * 0.5f ,0.f }), Vector3({ 0.f,0.f,0.f }), Vector2({ (float)bitInfo.bmWidth,(float)bitInfo.bmHeight }));
	
	// Create Skin and Setting
	CComponent* pComponent = CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN);
	CSkin* pSkin = RTTI_DYNAMIC_CAST(pComponent, CSkin);
	pSkin->SetTexture(_str);
	pSkin->SetOwner(this);
	
	// InsertComponent
	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN,pSkin });

	
	return 0;
}

int CBackGround::Render(const HDC _dc)
{
	// For FPS
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->Render(_dc);
	return 0;
}

int CBackGround::Update()
{
	return 0;
}


CBackGround::~CBackGround()
{
}
