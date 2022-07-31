#include "pch.h"
#include "CAnimation.h"
#include "CResourceMgr.h"


int CAnimation::SampleRender(const HDC _dc, const Vector2 Pos)
{
	
	return 0;
}

CAnimation::CAnimation()
	:m_strName()
	,m_pTex(nullptr)
	,m_bIsFinish(false)
{
}

CAnimation::~CAnimation()
{
}
