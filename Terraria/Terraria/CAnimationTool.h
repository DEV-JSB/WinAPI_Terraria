#pragma once
#include"CScene.h"
#include"CFactory.h"

class CAnimation;
class CTexture;
class CAnimationUI;
class CButtonUI;

class CAnimationTool : public CScene
{
public:
	// SaveAnimation
	int SaveAnimation();
	// Setting FileName and Animation Name
	int SetOpenFileName(const wstring& _Key,const wstring& _aniName, const wstring& _objname);
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
	virtual int FinalUpdate()			override;

private: // Member

	// Coupling Animation UI , Manager !!
	CAnimationUI* m_pAnimationUI;
	// Coupling BTN UI , Manager !!
	vector<CButtonUI*> m_vecBtnUI;
	// Will Fix Frame
	int m_iSettingFrame;

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
private: // Private Function
	// Setting UI
	int SettingUI();
	// CutBitmap
	bool CheckCutBitmap(const HDC _hdc);
private: // Constructor
	HIDE_CONSTRUCTOR(CAnimationTool);
public:
	virtual ~CAnimationTool();
};

