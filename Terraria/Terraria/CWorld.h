#pragma once
#include"CScene.h"
#include"CFactory.h"

class CWorld : public CScene
{
public:
	virtual int Release()				override;
	virtual int Render(const HDC _hdc)	override;
	virtual int Update()				override;
	virtual int Enter()					override;

private:
	CWorld();
public:
	friend class CFactory<CWorld>;

	virtual ~CWorld();
};

