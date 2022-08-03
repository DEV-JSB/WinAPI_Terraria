#include "pch.h"
#include "CAnimation.h"
#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include"CTexture.h"
#include"CPathMgr.h"


int CAnimation::SaveFile()const
{
	if (L"" == m_strName)
		return 0;
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	wstring strFilePath2 = CPathMgr::GetInstance()->GetContentPath();

	strFilePath  += L"Animation\\" + m_strName;
	strFilePath2 += L"Animation\\" + m_strOwner;

	FILE* pFile = nullptr;
	FILE* pFile2 = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb"); 
	_wfopen_s(&pFile2, strFilePath2.c_str(), L"wb");

	assert(pFile);
	assert(pFile2);

	fwrite(&m_strName, sizeof(wstring), 1, pFile2);

	for (size_t i = 0; i < m_vecFrame.size(); ++i)
	{
		// struct Save Test
		fwrite(&m_vecFrame[i], sizeof(stAnimFrame), 1, pFile);
	}

	fclose(pFile);
	fclose(pFile2);
	return 0;
}

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
