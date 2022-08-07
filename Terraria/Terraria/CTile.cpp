#include "pch.h"
#include "CTile.h"
#include "CFactory2.h"
#include "CSkin.h"

CTile::CTile()
	:CObject()
{
}

int CTile::Setting(TILE _eType, const Vector2 _pos)
{
	CSkin* pSkin = RTTI_DYNAMIC_CAST(CFactory2::CreateComponent(COMPONENT::COMPONENT_SKIN), CSkin);
	pSkin->SetOwner(this);
	// Tile Only Cut Size 16,16
	stSkinInfo SkinInfo;
	SkinInfo.vSliceSize = Vector2({ 16.f,16.f });

	// Pos will follow Pos
	Vector3 Pos;
	Pos.x = _pos.x + 8.f;
	Pos.y = _pos.y + 8.f;
	Pos.z = 0.f;
	switch (_eType)
	{
	case TILE::TILE_GROUNDUP:
		CObject::CreateTransform(Pos, Vector3({ 0.f,0.f,0.f }), SkinInfo.vSliceSize);
		pSkin->SetTexture(L"Tiles_Ground.bmp");
		// Hard Coding Setting LT 
		SkinInfo.vLT = Vector2({ 18.f,0.f });
		pSkin->SetSkinInfo(SkinInfo);
		break;
	case TILE::TILE_GROUNDDOWN:
		CObject::CreateTransform(Pos, Vector3({ 0.f,0.f,0.f }), SkinInfo.vSliceSize);
		pSkin->SetTexture(L"Tiles_Ground.bmp");
		// Hard Coding Setting LT 
		SkinInfo.vLT = Vector2({ 18.f,18.f });
		pSkin->SetSkinInfo(SkinInfo);
		break;
		
	}

	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN , pSkin });
	
	return 0;
}

int CTile::Update()
{
	return 0;
}

int CTile::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->Render(_dc);
	return 0;
}

int CTile::FinalUpdate()
{
	return 0;
}


CTile::~CTile()
{
}
