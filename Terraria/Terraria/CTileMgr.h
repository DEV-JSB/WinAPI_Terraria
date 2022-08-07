#pragma once

class CTile;

class CTileMgr
{
public:
	//Tile Render
	int Render(const HDC _dc);
	//Tile Setting
	int Enter();
private:
	vector<CTile> m_vecTile;
private:
	SINGLE(CTileMgr);

};

