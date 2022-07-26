#pragma once
#include"CScene.h"

class CAnimationTool : public CScene
{
public:
	virtual int Render(const HDC _hdc) override;
	virtual int Update()			   override;

	
};

