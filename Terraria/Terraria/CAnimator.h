#pragma once
#include"CComponent.h"
#include"CFactory.h"
class CObject;
class CAnimation;
class CTexture;

class CAnimator : public CComponent
{
public:
	int LoadAnimation(const wstring& _filename, const wstring& _texture);

	
private:
	// Animator Owner
	CObject*					m_pOwner;
	// Animation Map
	map<wstring, CAnimation*>	m_mapAnimation;
	// Will PlayAnimation ( why vec ? -> for Player MultipleAnim )
	vector<CAnimation*>			m_vecCurAnimation;
private:
	HIDE_CONSTRUCTOR(CAnimator);
public:
	virtual ~CAnimator();
};