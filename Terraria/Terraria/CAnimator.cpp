#include "pch.h"
#include "CAnimator.h"
#include"CAnimation.h"
#include"CPathMgr.h"
#include"CResourceMgr.h"
#include<iostream>
int CAnimator::LoadAnimation(const wstring& _filename,const wstring& _texture)
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

	while (feof(pFile) == 0)
	{
		IsTrash = fread(&stFrame, sizeof(stAnimFrame), 1, pFile);
		if (IsTrash)
			pAnimation->SetAniFrame(stFrame);
	}

	// Save Animator
	m_mapAnimation.insert({ _filename,pAnimation });

	fclose(pFile);
	
	return 0;
}

CAnimator::CAnimator()
{
}

CAnimator::~CAnimator()
{
}
