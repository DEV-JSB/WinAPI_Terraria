#pragma once

#include"CObject.h"

class CPlayer : public CObject
{
public:
	static CPlayer* Create();

private:
	CPlayer();
public:
	virtual ~CPlayer();
};

