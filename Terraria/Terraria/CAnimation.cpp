#include "pch.h"
#include "CAnimation.h"
#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include"CTexture.h"

int CAnimation::ReposOffset(const int _frameIdx, const Vector2& _off)
{
	m_vecFrame[_frameIdx].vOffset = _off;
	return 0;
}

int CAnimation::SampleRender(const HDC _dc, const Vector2& _Pos)
{
	Vector2 Pos = _Pos + m_vecFrame[m_iFrameIndex].vOffset;
	TransparentBlt(_dc
		, (int)(Pos.x - m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f)
		, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
		, m_pTex->GetTextureDC()
		, (int)m_vecFrame[m_iFrameIndex].vLT.x
		, (int)m_vecFrame[m_iFrameIndex].vLT.y
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
		, RGB(255, 255, 255));
	return 0;
}

int CAnimation::Update()
{
	m_fAccumulateTime += (float)CTimeMgr::GetInstance()->GetDT();

	if (m_vecFrame[m_iFrameIndex].fDuration <= m_fAccumulateTime)
	{
		++m_iFrameIndex;
		m_fAccumulateTime = 0.f;
	}

	if (m_vecFrame.size() == m_iFrameIndex)
		m_iFrameIndex = 0;
	return 0;
}

CAnimation::CAnimation()
	:m_strName()
	, m_pTex(nullptr)
	, m_bIsFinish(false)
	, m_fAccumulateTime(0.f)
	, m_iFrameIndex(0)
{
}

CAnimation::~CAnimation()
{
}
