#pragma once
#include"CObject.h"
#include"CFactory.h"

class CPlayer : public CObject
{

public:
	virtual int FinalUpdate() override;
	virtual int Update() override;
	virtual int Render(const HDC _dc) override;

private:
	friend class CFactory<CPlayer>;
	CPlayer();
public:
	virtual ~CPlayer();
};

