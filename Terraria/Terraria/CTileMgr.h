#pragma once

class CObject;


class CTileMgr
{
public:
	const vector<CObject*> GetTileGroup()const { return m_vecTile; }
public:
	//Tile Render
	int Render(const HDC _dc);
	//Tile Setting
	int Enter();
	int Release();
private:	
	vector<CObject*> m_vecTile;
private:
	SINGLE(CTileMgr);

};

