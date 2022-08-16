#include "pch.h"
#include "CTile.h"
#include "CTransform2D.h"
#include "CFactory2.h"
#include "CCamera.h"
#include "CTileMgr.h"

CTileMgr::CTileMgr()
{

}


int CTileMgr::Render(const HDC _dc)
{
	Vector2 vCameraPos = CCamera::GetInstance()->GetLookAt();
	Vector2 vCameraRes = CCamera::GetInstance()->GetResolutuon();

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		Vector2 vTilePos;
		vTilePos.x = m_vecTile[i]->GetTransform()->GetPosition_X();
		vTilePos.y = m_vecTile[i]->GetTransform()->GetPosition_Y() - 16;

		if(vCameraPos.x - vCameraRes.x < vTilePos.x && vTilePos.x < vCameraPos.x + vCameraRes.x
			&& vCameraPos.y - vCameraRes.y < vTilePos.y && vTilePos.y < vCameraPos.y + vCameraRes.y)
			m_vecTile[i]->Render(_dc);

	}
	return 0;
}

int CTileMgr::Enter()
{
	//NormalTileSetting
		// 45 Row Max
		// 80 colum Max
	for (int x = 0 ; x < 80; ++x)
	{
		for (int y = 30; y <= 31; ++y)
		{
			if (0 <= x && x <= 80 && 30 <= y && y <= 31)
			{
				// Create Tile
				CTile* pTile = RTTI_DYNAMIC_CAST(CFactory2::CreateObject(OBJECT::OBJECT_TILE), CTile);
				if (y == 30)
					pTile->Setting(TILE::TILE_GROUNDUP, Vector2({ (float)(x * 16), (float)(y * 16) }));
				else
					pTile->Setting(TILE::TILE_GROUNDDOWN, Vector2({ (float)(x * 16), (float)(y * 16) }));
				m_vecTile.push_back(pTile);
			}
		}
	}
	return 0;
}


CTileMgr::~CTileMgr()
{

}