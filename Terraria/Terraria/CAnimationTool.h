#pragma once
#include"CScene.h"
#include"CFactory.h"

class CAnimation;
class CTexture;
class CAnimationUI;


class CAnimationTool : public CScene
{
public:
	// Setting FileName
	int SetOpenFileName(const wstring& _Key);
	// DrawSelectRect Line
	int DrawSelectRect(const HDC _hdc);
	// SettingAnimationFrame
	int SetAnimation();

public:
	// Delete Object
	virtual int Release()			   override;
	// Rendering
	virtual int Render(const HDC _hdc) override;
	// Update Scene
	virtual int Update()			   override;
	virtual int Enter()				   override;

private:// Member

	// Check SettingRect
	bool m_bIsSetRect;

	// SaveFileName_Setting_Dialog
	wstring m_strFileName;

	// Wiil MakeAnimation Frame
	stAnimFrame m_stAniFrame;

	// Will MakeAnimation
	CAnimation* m_pAnimation;

	// Will Load Texture
	CTexture* m_pTexture;

	// Select RectRange
	RECT m_stSelectRect;
private:// Private Function

	// CutBitmap
	bool CheckCutBitmap(const HDC _hdc);
private: // Constructor
	friend class CFactory<CAnimationTool>;
	CAnimationTool();
public:
	virtual ~CAnimationTool();
};

