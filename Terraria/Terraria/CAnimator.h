#pragma once
#include"CComponent.h"

class CObject;
class CAnimation;
class CTexture;

class CAnimator : public CComponent
{
public:
	


private:
	// Animator Owner
	CObject*					m_pOwner;
	// Animation Map
	map<wstring, CAnimation*>	m_mapAnimation;
	// Will PlayAnimation ( why vec ? -> for Player MultipleAnim )
	vector<CAnimation*>			m_vecCurAnimation;
	

};