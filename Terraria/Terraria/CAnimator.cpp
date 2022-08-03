#include "pch.h"
#include "CAnimator.h"
#include"CPathMgr.h"

int CAnimator::LoadAnimation(const wstring& _listfilename)
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += L"Animation\\" + _listfilename;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	wstring str = L"";

	while (feof(pFile) == 0)
	{
		fread(&str, sizeof(wstring), 1, pFile);
	}

	fclose(pFile);

	return 0;
}
