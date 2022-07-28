#pragma once

#include"CObject.h"

class CPlayer : public CObject
{

public:
	virtual int FinalUpdate() override;
	virtual int Update() override;
	virtual int Render(const HDC _dc) override;

private:
	CPlayer();
public:
	virtual ~CPlayer();
};

