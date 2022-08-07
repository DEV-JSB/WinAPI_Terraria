#include "pch.h"
#include "CTile.h"
#include "CFactory2.h"
#include "CTileMgr.h"

int CTileMgr::Render(const HDC _dc)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i].Render(_dc);
	}

	return 0;
}

int CTileMgr::Enter()
{
	//NormalTileSetting
		// 30 Row
		// 80 colum Make Tile
	for (int x = 0; x < 80; ++x)
	{
		for (int y = 0; y < 30; ++y)
		{
			CTile* pTile = RTTI_DYNAMIC_CAST(CFactory2::CreateObject(OBJECT::OBJECT_TILE), CTile);
			pTile->Setting(TILE::TILE_GROUND, Vector2({ (float)(x * 16), (float)(y * 16) }));
		}
	}
	return 0;
}
