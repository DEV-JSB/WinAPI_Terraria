#pragma once


class CTexture;


class CAnimation
{
public:
	// SaveAnimation
	int SaveFile()const;
	int Render(const HDC _dc, const Vector2& _Pos, const bool _xFlip);
public: // Get
	// GetFrame Offset
	Vector2 GetOffset(const int _frameIdx)const { return m_vecFrame[_frameIdx].vOffset; }
	// Get Frame Count
	int GetFrameCount()const { return m_vecFrame.size(); }
	// Get Bool
	bool IsFinish()const { return m_bIsFinish; }
public: // Set

	int SetDefaultDuration(const float _fDuration) {m_fDefaultDuration = _fDuration; return 0;}
	int SetDurationRegular(const float _fDuration);

	int ResetFrame();
	// SetFrameOffset
	int ReposOffset(const int _frameIdx, const Vector2& _off);
	// SetAnimationFrame
	int SetAniFrame(stAnimFrame& _frame) { m_vecFrame.push_back(_frame); return 0; }
	// Set Texture
	int SetTexture(CTexture* _pTexture) { m_pTex = _pTexture; return 0; }
	// SetAnimationName
	int SetAnimationName(const wstring& _name) { m_strName = _name; return 0; }
	// Set Will Accelerando Duration
	int SetAccelerando(const bool _b) { m_bAccelerando = _b; return 0; }
public:
	int Update();
private:
	int FlipBitmap();
private:
	// Animation Name
	wstring m_strName;
	// Using Texture
	CTexture* m_pTex;
	

	// accelerando
	bool m_bAccelerando;

	vector<stAnimFrame> m_vecFrame;
	// Is Play Finish
	bool m_bIsFinish;
	// Default Duration
	float m_fDefaultDuration;
	// Time accumulate
	float m_fAccumulateTime;
	// FrameIndex
	int m_iFrameIndex;

private: // Constructor
	HIDE_CONSTRUCTOR(CAnimation);
public:
	~CAnimation();
};

