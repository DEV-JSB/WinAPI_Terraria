#pragma once
#include"CScene.h"
#include"CFactory.h"

class CWorld : public CScene
{
public:
	virtual int FinalUpdate()			override;
	virtual int Release()				override;
	virtual int Render(const HDC _dc)	override;
	virtual int Update()				override;
	virtual int Enter()					override;
private:
	int SetPlayerItem();
	int LoadItem();
	int LoadResource()const;
	int CreateBackGround();
	int CreateUI();
	int CreateObject();
	int DeadCheck();
private:
	HIDE_CONSTRUCTOR(CWorld);
public:

	virtual ~CWorld();
};

