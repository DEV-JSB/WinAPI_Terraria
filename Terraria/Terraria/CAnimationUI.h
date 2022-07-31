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
	Vector2 m_vSamplePos;
private: // Constructor
	friend class CFactory<CAnimationUI>;
	CAnimationUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
};

