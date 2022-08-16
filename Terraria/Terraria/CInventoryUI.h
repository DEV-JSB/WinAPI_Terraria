#pragma once
#include "CUI.h"
#include "CFactory2.h"

class CItemPocketUI;

class CInventoryUI : public CUI
{
public:
	virtual int Update()				override;
	virtual int Render(const HDC _dc)	override;
	virtual int FinalUpdate()			override;

private:
	bool m_bHidden;
	map<int, CItemPocketUI*> m_mapPocket;
private:
	friend class CFactory2;
	CInventoryUI();
	int Setting();
public:
	virtual ~CInventoryUI();

};

