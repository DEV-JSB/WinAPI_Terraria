#pragma once
#include"CUI.h"
#include"CFactory.h"


class CAnimation;

class CAnimationUI : public CUI
{



public:
	int PlayAnimationSample(CAnimation& _animator);
public: // Logic
	virtual int Update()        override;
	virtual int Render(const HDC _dc) override;
	virtual int FinalUpdate() override;
private:
	friend class CFactory<CAnimationUI>;
	CAnimationUI();
};

