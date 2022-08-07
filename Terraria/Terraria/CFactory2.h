#pragma once

class CComponent;
class CObject;
class CFactory2
{
public:
	static CObject* CreateObject(OBJECT _eType);
	static CComponent* CreateComponent(COMPONENT _eType);
private:
	CFactory2();
	~CFactory2();
};

