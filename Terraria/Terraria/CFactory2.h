#pragma once

class CComponent;
class CObject;
class CUI;

class CFactory2
{
public:
	static CObject* CreateObject(const OBJECT _eType);
	static CComponent* CreateComponent(const COMPONENT _eType);
	static CUI* CreateUI(const UI_TYPE _eType);
private:
	CFactory2();
	~CFactory2();
};

