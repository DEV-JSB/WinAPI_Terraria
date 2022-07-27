#pragma once
#include"CScene.h"

class CAnimationTool : public CScene
{
private:
	CAnimationTool();
public:
	static CAnimationTool* Create();

	virtual ~CAnimationTool();


public:
	virtual int Render(const HDC _hdc) override;
	virtual int Update()			   override;

private:
	
};

