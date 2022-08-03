#include "pch.h"
#include "CAnimator.h"
#include"CPathMgr.h"
#include<iostream>
int CAnimator::LoadAnimation(const wstring& _listfilename)
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += (L"Animation\\PlayerHead");

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	stAnimFrame stFrame;

	while (feof(pFile) == 0)
	{
		fread(&stFrame, sizeof(stAnimFrame), 1, pFile);
	}

	fclose(pFile);

	return 0;
}
