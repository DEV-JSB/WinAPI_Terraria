#include "pch.h"
#include "CTile.h"
#include "CFactory2.h"
#include "CTileMgr.h"

CTileMgr::CTileMgr()
{

}


int CTileMgr::Render(const HDC _dc)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Render(_dc);
	}
	return 0;
}

int CTileMgr::Enter()
{
	//NormalTileSetting
		// 45 Row Max
		// 80 colum Max
	for (int x = -50 ; x < 130; ++x)
	{
		for (int y = 0; y <= 70; ++y)
		{
			if (0 <= x && x <= 80 && 30 <= y && y <= 70)
			{
				// Create Tile
				CTile* pTile = RTTI_DYNAMIC_CAST(CFactory2::CreateObject(OBJECT::OBJECT_TILE), CTile);
				if (y == 30)
					pTile->Setting(TILE::TILE_GROUNDUP, Vector2({ (float)(x * 16), (float)(y * 16) }));
				else
					pTile->Setting(TILE::TILE_GROUNDDOWN, Vector2({ (float)(x * 16), (float)(y * 16) }));
				m_vecTile.push_back(pTile);
			}
			else if( (-50 <= x && x < 0) || (80 < x && x < 130))
			{
				CTile* pTile = RTTI_DYNAMIC_CAST(CFactory2::CreateObject(OBJECT::OBJECT_TILE), CTile);
				pTile->Setting(TILE::TILE_ROCK, Vector2({ (float)(x * 16), (float)(y * 16) }));
				m_vecTile.push_back(pTile);
			}
		}
	}
	return 0;
}


CTileMgr::~CTileMgr()
{

}