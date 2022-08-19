#include "pch.h"
#include "CAnimation.h"
#include "CResourceMgr.h"
#include "CFrameMgr.h"
#include"CTexture.h"
#include"CPathMgr.h"

CAnimation::CAnimation()
	: m_strName()
	, m_pTex(nullptr)
	, m_bIsFinish(false)
	, m_fDefaultDuration(1.f)
	, m_fAccumulateTime(0.f)
	, m_iFrameIndex(0)
	, m_bAccelerando(false)
{
}

int CAnimation::SaveFile()const
{
	if (L"" == m_strName)
		return 0;
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();

	// [PlayerAnimation]
	// PlayerArm
	// eof
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

int CAnimation::SetDurationRegular(const float _fDuration)
{
	float fRegular = _fDuration / m_vecFrame.size();
	m_fDefaultDuration = fRegular;
	for (size_t i = 0; i < m_vecFrame.size(); ++i)
	{
		m_vecFrame[i].fDuration = fRegular;
	}
	return 0;
}

int CAnimation::ResetFrame()
{
	for (size_t i = 0; i < m_vecFrame.size(); ++i)
	{
		m_vecFrame[i].fDuration = m_fDefaultDuration;
	}
	m_iFrameIndex = 0;
	m_fAccumulateTime = 0;
	m_bIsFinish = false;
	return 0;
}

int CAnimation::ReposOffset(const int _frameIdx, const Vector2& _off)
{
	m_vecFrame[_frameIdx].vOffset = _off;
	return 0;
}

int CAnimation::Render(const HDC _dc, const Vector2& _Pos,const bool _xFlip)
{
	if (m_strName == L"SwordUseAni")
	{
		printf("%d °Ë ·»´õ¸µ\n",m_iFrameIndex);
		
	}
	Vector2 Pos;

	if (false == _xFlip)
	{
		Pos = _Pos + m_vecFrame[m_iFrameIndex].vOffset;
		
		// Rendering Pos
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
	}
	else
	{
		// X Pivot Flip Version

		// Make Pivot Flip
		Pos.y = _Pos.y + m_vecFrame[m_iFrameIndex].vOffset.y;
		// Y Pivot Don't tocuh
		Pos.x = _Pos.x - m_vecFrame[m_iFrameIndex].vOffset.x;

		

		HDC StretchDC = CreateCompatibleDC(m_pTex->GetTextureDC());
		HBITMAP StretchBit = CreateCompatibleBitmap(_dc, CLIENT_WIDTH, CLIENT_HEIGHT + (int)floorf(m_vecFrame[m_iFrameIndex].vSliceSize.y));
		DeleteObject(SelectObject(StretchDC, StretchBit));

		StretchBlt(StretchDC
			, (int)(Pos.x + m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f) - 1
			, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
			, -(int)m_vecFrame[m_iFrameIndex].vSliceSize.x
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
			, m_pTex->GetTextureDC()
			, (int)m_vecFrame[m_iFrameIndex].vLT.x
			, (int)m_vecFrame[m_iFrameIndex].vLT.y
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y, SRCCOPY);

		TransparentBlt(_dc
			, (int)(Pos.x - m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f)
			, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
			, StretchDC
			, (int)(Pos.x - m_vecFrame[m_iFrameIndex].vSliceSize.x * 0.5f)
			, (int)(Pos.y - m_vecFrame[m_iFrameIndex].vSliceSize.y * 0.5f)
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.x
			, (int)m_vecFrame[m_iFrameIndex].vSliceSize.y
			, RGB(255, 255, 255));

		DeleteObject(StretchDC);
		DeleteObject(StretchBit);
	}
	return 0;
}


int CAnimation::Update()
{
	if (m_vecFrame.size() <= 1)
		return 0;
	// 1ÃÊ  0.0018  1 
	m_fAccumulateTime += GET_DT;

	if (m_bAccelerando)
	{
		// Setting accelerando duration
		for (size_t i = 0; i < m_vecFrame.size(); ++i)
		{
			if (m_vecFrame[i].fDuration > 0.07f)
				m_vecFrame[i].fDuration -= GET_DT;
		}
	}
	

	if (m_vecFrame[m_iFrameIndex].fDuration <= m_fAccumulateTime)
	{
		++m_iFrameIndex;
		m_fAccumulateTime = 0.f;
	}

	if (m_vecFrame.size() == m_iFrameIndex)
	{
		m_bIsFinish = true;
		m_iFrameIndex = 0;
	}
	return 0;
}

int CAnimation::FlipBitmap()
{

	return 0;
}



CAnimation::~CAnimation()
{
}
