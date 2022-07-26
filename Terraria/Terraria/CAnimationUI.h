#pragma once
#include"CUI.h"
#include"CFactory.h"
#include"CAnimationTool.h"

class CAnimation;

class CAnimationUI : public CUI
{
public:
	int ResetAnimationVec() { m_vecAnimationSample.clear(); return 0; };
	vector<CAnimation*> GetAniVector()const { return m_vecAnimationSample; }
	int SetAnimation(CAnimation* _p) { m_vecAnimationSample.push_back(_p); return 0; }
	int PlayAnimationSample(const HDC _dc);
	int GetAnimationCount()const { return m_vecAnimationSample.size(); }
	int AddAnimationIndex() { ++m_iAnimationIndex; return 0; }
	int MinAnimationIndex() { --m_iAnimationIndex; return 0; }
public: // Logic
	virtual int Update()        override;
	virtual int Render(const HDC _dc) override;
	virtual int FinalUpdate() override;
	virtual UI_TYPE GetUIType() override { return m_eUI_Type; };
	virtual int MouseButtonClicked() override;

private:
	int m_iAnimationIndex;
	vector<CAnimation*> m_vecAnimationSample;
	Vector2 m_vSamplePos;
private: // Constructor
	HIDE_CONSTRUCTOR(CAnimationUI);
	CAnimationUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
public:
	virtual ~CAnimationUI();
};

