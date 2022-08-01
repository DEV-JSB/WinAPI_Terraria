#pragma once
#include"CUI.h"
#include"CFactory.h"


class CAnimation;

class CAnimationUI : public CUI
{
public:
	int SetAnimation(CAnimation* _p) { m_pAnimationSample = _p; return 0; }
	int PlayAnimationSample(const HDC _dc);
public: // Logic
	virtual int Update()        override;
	virtual int Render(const HDC _dc) override;
	virtual int FinalUpdate() override;
	virtual UI_TYPE GetType() override { return m_eType; };
	virtual int MouseButtonClicked() override;

private:
	CAnimation* m_pAnimationSample;
	Vector2 m_vSamplePos;
private: // Constructor
	friend class CFactory<CAnimationUI>;
	CAnimationUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
};

