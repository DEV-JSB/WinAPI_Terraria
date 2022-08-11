#include "pch.h"
#include "CTile.h"
#include "CFactory2.h"
#include"CTransform2D.h"
#include "CBoxCollider.h"
#include "CSkin.h"

#define Y_COMPENSATE_VALUE 3
#define TILE_SIZE 16.f

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
	SkinInfo.vSliceSize = Vector2({ TILE_SIZE,TILE_SIZE });

	// Setting Type
	CObject::SetType(OBJECT::OBJECT_TILE);

	// Pos will follow Pos
	Vector3 Pos;
	Pos.x = _pos.x + TILE_SIZE * 0.5f;
	Pos.y = _pos.y + TILE_SIZE * 0.5f;
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
	CreateCollider(Vector2{ Pos.x,Pos.y });
	
	m_mapComponent.insert({ COMPONENT::COMPONENT_SKIN , pSkin });
	

	return 0;
}

int CTile::OnCollision(const CObject* _pOther)
{
	
	return 0;
}

int CTile::OnCollisionEnter(const CObject* _pOther)
{
	if (OBJECT::OBJECT_PLAYER == _pOther->GetType())
	{
		// For Collider Bottom
		Vector2 vColliderPos = _pOther->GetCollider()->GetPos();
		Vector2 vColliderScale = RTTI_DYNAMIC_CAST(_pOther->GetCollider(), CBoxCollider)->GetScale();

		// For Tile Top
		Vector3 vTilePos = CObject::GetTransform()->GetPosition();
		Vector2 vTileScale = CObject::GetTransform()->GetScale();

		//int DiffValue = (int)(vColliderPos.y + vColliderScale.y * 0.5f) - (int)(vTilePos.y - vTileScale.y * 0.5f);
		// Difference Value
		int Y_Pos = (int)(vTilePos.y - vTileScale.y * 0.5f) - (int)(vColliderScale.y * 0.5);

		/*_pOther->GetTransform()->Set_Y_Pos((int)_pOther->GetTransform()->GetPosition_Y() - DiffValue);*/
		// Player Position Up
		_pOther->GetTransform()->Set_Y_Pos(Y_Pos + Y_COMPENSATE_VALUE);
	}
	return 0;
}

int CTile::OnCollisionExit(const CObject* _pOther)
{
	return 0;
}

int CTile::Update()
{
	CObject::Update();
	return 0;
}

int CTile::FinalUpdate()
{
	CObject::FinalUpdate();
	return 0;
}

int CTile::Render(const HDC _dc)
{
	m_mapComponent[COMPONENT::COMPONENT_SKIN]->Render(_dc);
	CObject::Render(_dc);
	return 0;
}



int CTile::CreateCollider(const Vector2 _pos)
{
	CComponent* pBoxCollider = CFactory2::CreateComponent(COMPONENT::COMPONENT_BOXCOLLIDER);
	RTTI_DYNAMIC_CAST(pBoxCollider, CBoxCollider)->SetInformation(this,_pos
																  ,Vector2({TILE_SIZE, TILE_SIZE})
																  , Vector2({ 0.f,0.f }));
	m_mapComponent.insert({ COMPONENT::COMPONENT_COLLIDER,pBoxCollider });
	return 0;
}


CTile::~CTile()
{
}
