#pragma once


class CTexture;


class CAnimation
{
public:
	// SetFrameOffser
	int ReposOffset(const int _frameIdx, const Vector2& _off);
	int SampleRender(const HDC _dc, const Vector2& Pos);
	// SetAnimationFrame
	int SetAniFrame(stAnimFrame& _frame) { m_vecFrame.push_back(_frame); return 0; }
	// Set Texture
	int SetTexture(CTexture* _pTexture) { m_pTex = _pTexture; return 0; }
	// Get Frame Count
	int GetFrameCount()const { return m_vecFrame.size(); }
public:
	int Update();

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
	// FrameIndex
	int m_iFrameIndex;

private: // Constructor

	friend class CFactory<CAnimation>;
	CAnimation();

public:
	~CAnimation();
};

