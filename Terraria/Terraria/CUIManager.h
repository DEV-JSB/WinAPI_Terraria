#pragma once

class CUI;
class CAnimation;

class CUIManager
{
public:
	int SettingAnimation(CAnimation* pAni);
	int Release();
	int Update();
	int Render(const HDC _hdc);
private:
	UI_TYPE m_eFocusType;
	CUI* m_pFocusing;
private:
	// Checking Focusing Pivot MousePos
	int FoucusingCheck();
private:
	SINGLE(CUIManager);
};

