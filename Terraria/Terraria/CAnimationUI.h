#pragma once
#include"CUI.h"
#include"CFactory.h"
#include"CAnimationTool.h"

class CAnimation;

class CAnimationUI : public CUI
{
public:
	int SetAnimation(CAnimation* _p) { m_vecAnimationSample.push_back(_p); return 0; }
	int PlayAnimationSample(const HDC _dc);
	int GetAnimationCount()const { return m_iAnimationIndex; }
	int AddAnimationIndex() { ++m_iAnimationIndex; return 0; }
	int MinAnimationIndex() { --m_iAnimationIndex; return 0; }
public: // Logic
	virtual int Update()        override;
	virtual int Render(const HDC _dc) override;
	virtual int FinalUpdate() override;
	virtual UI_TYPE GetType() override { return m_eType; };
	virtual int MouseButtonClicked() override;

private:
	int m_iAnimationIndex;
	vector<CAnimation*> m_vecAnimationSample;
	Vector2 m_vSamplePos;
private: // Constructor
	friend class CFactory<CAnimationUI>;
	CAnimationUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
};

