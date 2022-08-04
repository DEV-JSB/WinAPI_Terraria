#include "pch.h"
#include "CAnimation.h"
#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include"CTexture.h"
#include"CPathMgr.h"

CAnimation::CAnimation()
	: m_strName()
	, m_pTex(nullptr)
	, m_bIsFinish(false)
	, m_fAccumulateTime(0.f)
	, m_iFrameIndex(0)
{
}

int CAnimation::SaveFile()const
{
	if (L"" == m_strName)
		return 0;
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();

	strFilePath  += L"Animation\\" + m_strName;
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"ab"); 
	assert(pFile);
	for (size_t i = 0; i < m_vecFrame.size(); ++i)
	{
		// struct Save Test
		fwrite(&m_vecFrame[i], sizeof(stAnimFrame), 1, pFile);
	}

	fclose(pFile);
	return 0;
}

int CAnimation::ReposOffset(const int _frameIdx, const Vector2& _off)
{
	m_vecFrame[_frameIdx].vOffset = _off;
	return 0;
}

int CAnimation::Render(const HDC _dc, const Vector2& _Pos)
{
	Vector2 Pos;

	/*Pos = _Pos + m_vecFrame[m_iFrameIndex].vOffset;
	TransparentBlt(_dc
		, (int)(Pos.x - m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f + 14)
		, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
		, m_pTex->GetTextureDC()
		, (int)m_vecFrame[m_iFrameIndex].vLT.x
		, (int)m_vecFrame[m_iFrameIndex].vLT.y
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
		, RGB(255, 255, 255));*/

	// X Pivot Flip Version
	
	//Make Pivot Flip
	Pos.y = _Pos.y + m_vecFrame[m_iFrameIndex].vOffset.y;
	//Y Pivot Don't tocuh
	Pos.x = _Pos.x - m_vecFrame[m_iFrameIndex].vOffset.x;

	StretchBlt(_dc
		, (int)(Pos.x + m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f)
		, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
		, -(int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
		, m_pTex->GetTextureDC()
		, (int)m_vecFrame[m_iFrameIndex].vLT.x
		, (int)m_vecFrame[m_iFrameIndex].vLT.y
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
		, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y, SRCCOPY);
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

int CAnimation::FlipBitmap()
{

	return 0;
}



CAnimation::~CAnimation()
{
}
