#pragma once

class CComponent;
class CObject;
class CUI;
class CItem;

class CFactory2
{
public:
	static CItem* CreateItem(const ITEM _eType);
	static CObject* CreateObject(const OBJECT _eType);
	static CComponent* CreateComponent(const COMPONENT _eType);
	static CUI* CreateUI(const UI_TYPE _eType);
private:
	CFactory2();
	~CFactory2();
};

