#pragma once
#include"CScene.h"
#include"CFactory.h"

class CAnimationTool : public CScene
{
private:
	friend class CFactory<CAnimationTool>;
	CAnimationTool();
public:
	virtual ~CAnimationTool();

public:
	// Delete Object;
	virtual int Release()			   override;
	// Rendering
	virtual int Render(const HDC _hdc) override;
	// Update Scene
	virtual int Update()			   override;
	virtual int Enter()				   override;
private:

};

