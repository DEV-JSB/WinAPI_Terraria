#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTransform2D.h"
#include "CPathMgr.h"
#include "CResourceMgr.h"
#include "CCamera.h"


CAnimator::CAnimator(const bool _willRender)
	:CComponent(_willRender)
	,m_pOwner(nullptr)
	, m_bXflip(false)
{
}




int CAnimator::LoadAnimation(const wstring& _filename,const wstring& _texture, const bool _bAccelerando)
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += L"Animation\\" + _filename;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	CAnimation* pAnimation = CFactory<CAnimation>::Create();
	// Animation Texture Setting
	pAnimation->SetTexture(CResourceMgr::GetInstance()->FindTexture(_texture));
	pAnimation->SetAnimationName(_filename);
	// if a == 0 Don't Set Animation
	bool IsTrash;
	stAnimFrame stFrame;

	pAnimation->SetAccelerando(_bAccelerando);

	while (feof(pFile) == 0)
	{
		IsTrash = fread(&stFrame, sizeof(stAnimFrame), 1, pFile);
		if (IsTrash)
		{
			pAnimation->SetAniFrame(stFrame);
		}
	}

	// Save Animator
	m_mapAnimation.insert({ _filename,pAnimation });

	fclose(pFile);
	
	return 0;
}

const int CAnimator::GetCurrentPlayIndex(const wstring& _strname)
{
	return m_mapAnimation[_strname]->GetCurrentPlayIndex();
}

int CAnimator::GetCurrentAnimationCount(const wstring& _strname)
{
	return m_mapAnimation[_strname]->GetFrameCount();
}

const vector<stAnimFrame> CAnimator::GetAnimationFrameInfo(const wstring& _strname)
{
	return m_mapAnimation[_strname]->GetFrameInfo();
}

bool CAnimator::IsEndAnimation(const wstring& _strAniname)
{
	return m_mapAnimation[_strAniname]->IsFinish();
}

int CAnimator::CurPlayAnimationReset()
{
	for (size_t i = 0; i < m_vecCurAnimation.size(); ++i)
	{
		m_vecCurAnimation[i]->ResetFrame();
	}
	return 0;
}

int CAnimator::SetFilp(const bool _bFlip)
{
	m_bXflip = _bFlip;
	return 0;
}

int CAnimator::SetAnimationDurationRegular(const wstring& _strAniname, const float _fDuration)
{
	m_mapAnimation[_strAniname]->ResetFrame();
	m_mapAnimation[_strAniname]->SetDurationRegular(_fDuration);
	return 0;
}

int CAnimator::SettingPlayAnimation(const vector<wstring>& _vecName)
{
	for (size_t i = 0; i < _vecName.size(); ++i)
	{
		m_vecCurAnimation.push_back((*m_mapAnimation.find(_vecName[i])).second);
	}
	return 0;
}

int CAnimator::SubstitutePlayAnimation(const wstring& _deleteAni, const wstring& _substitute)
{
	// If Delete Success then Push BackAnimation
	if (CutCurFrame(_deleteAni))
	{
		CAnimation* pAni = (*m_mapAnimation.find(_substitute)).second;
		
		pAni->ResetFrame();
		m_vecCurAnimation.push_back(pAni);
	}
	return 0;
}

int CAnimator::Render(const HDC _dc)const
{
	CTransform2D* pTrans = m_pOwner->GetTransform();
	Vector3 vRenderPos = pTrans->GetPosition();
	Vector2 vDiff = CCamera::GetInstance()->GetDifference();
	vRenderPos.x += vDiff.x;
	vRenderPos.y += vDiff.y;
	for (size_t i = 0; i < m_vecCurAnimation.size(); ++i)
	{
		m_vecCurAnimation[i]->Render(_dc, Vector2({ vRenderPos.x,vRenderPos.y }), m_bXflip);
	}
	return 0;
}

int CAnimator::Update()
{
	for (size_t i = 0; i < m_vecCurAnimation.size(); ++i)
	{
		m_vecCurAnimation[i]->Update();
	}
	return 0;
}

int CAnimator::FinalUpdate()
{

	return 0;
}

bool CAnimator::CutCurFrame(const wstring& _filename)
{
	for (auto iter = m_vecCurAnimation.begin(); iter != m_vecCurAnimation.end(); ++iter)
	{
		if ((*iter) == (*m_mapAnimation.find(_filename)).second)
		{
			m_vecCurAnimation.erase(iter);
			return true;
		}
	}
	return false;
}




CAnimator::~CAnimator()
{
	for (auto iter = m_mapAnimation.begin(); iter != m_mapAnimation.end(); ++iter)
	{
		if (nullptr != (*iter).second)
			delete (*iter).second;
	}
	m_mapAnimation.clear();
	m_vecCurAnimation.clear();
}
