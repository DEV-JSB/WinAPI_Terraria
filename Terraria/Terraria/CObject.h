#pragma once
#include"CComponent.h"

class CObject
{
public:

protected:
	// Component Map
	std::map<COMPONENT, CComponent*> m_mapComponent;
protected:
	CObject();
	virtual ~CObject();
};

