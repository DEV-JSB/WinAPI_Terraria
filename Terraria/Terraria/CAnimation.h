#pragma once


class CTexture;


class CAnimation
{
public:
	
	int SampleRender(const HDC _dc, const Vector2 Pos);
	// SetAnimationFrame
	int SetAniFrame(stAnimFrame& _frame) { m_vecFrame.push_back(_frame); return 0; }

private:
	// Animation Name
	wstring m_strName;
	// Using Texture
	CTexture* m_pTex;
	// All Of Frame Information
	vector<stAnimFrame> m_vecFrame;
	// Is Play Finish
	bool m_bIsFinish;
	// Time accumulate
	float m_fAccumulateTime;

private: // Constructor

	friend class CFactory<CAnimation>;
	CAnimation();

public:
	~CAnimation();
};

