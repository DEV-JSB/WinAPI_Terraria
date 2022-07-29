#pragma once


class CTexture;


class CAnimation
{
public:

private:
	// Animation Name
	wstring m_strName;
	// Using Texture
	CTexture* m_pTex;
	// All Of Frame Information
	vector<stAnimFrame> m_vecFrame;
private: // Constructor

	friend class CFactory<CAnimation>;
	CAnimation();

public:
	~CAnimation();
};

