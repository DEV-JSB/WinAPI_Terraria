#pragma once

class CComponent;

class CFactory2
{
public:
	static CComponent* CreateComponent(COMPONENT _eType);
private:
	CFactory2();
	~CFactory2();
};

