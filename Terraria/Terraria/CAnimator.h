#pragma once
#include"CComponent.h"
#include"CFactory.h"
class CObject;
class CAnimation;
class CTexture;

class CAnimator : public CComponent
{
public:// Set Func
	int SetOwner(CObject* _p) { m_pOwner = _p; return 0; }
	int SetFilp(const bool _bFlip);
public:
	// Only One Time Use , ObjectCreate
	int SettingPlayAnimation(const vector<wstring>& _vecName);

	int LoadAnimation(const wstring& _filename, const wstring& _texture);
	int SubstitutePlayAnimation(const wstring& _deleteAni,const wstring& _substitute);

public://Logic
	virtual int Render(const HDC _dc)const override;
	virtual int Update() override;
	virtual int FinalUpdate() override;
private:
	int CutCurFrame(const wstring& _filename);
private:
	// Will Flip Animation
	bool m_bXflip;
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