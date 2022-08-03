#pragma once
#include"CComponent.h"
#include"CFactory.h"
class CObject;
class CAnimation;
class CTexture;

class CAnimator : public CComponent
{
public:
	// Only One Time Use , ObjectCreate
	int SettingPlayAnimation(const vector<wstring>& _vecName);
	int LoadAnimation(const wstring& _filename, const wstring& _texture);
	int SubstitutePlayAnimation(const wstring _deleteAni,const wstring& _substitute);

public://Logic
	virtual int Render(const HDC _hdc) override;
	virtual int Update(const HDC _hdc) override;
	virtual int FinalUpdate(const HDC _hdc) override;
private:
	int CutCurFrame(const wstring& _filename);
private:
	// Animator Owner
	CObject*					m_pOwner;
	// Animation Map
	map<wstring, CAnimation*>	m_mapAnimation;
	// Will PlayAnimation ( why vec ? -> for Player MultipleAnim )
	vector<CAnimation*>			m_vecCurAnimation;
private:
	FRIEND_FACTORY(CAnimator);
	CAnimator(const bool _willRender);
public:
	virtual ~CAnimator();
};