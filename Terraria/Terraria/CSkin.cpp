#include "pch.h"
#include "CSkin.h"
#include "CResourceMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CTransform2D.h"
CSkin::CSkin(const bool _willrender)
	:CComponent(_willrender)
	, m_stSkinInfo({})
	,m_pTex(nullptr)
	,m_pOwner(nullptr)
{
}


int CSkin::SetTexture(const wstring& _str)
{
	m_pTex = CResourceMgr::GetInstance()->LoadTexture(_str,CPathMgr::GetInstance()->GetContentPath());
	return 0;
}

int CSkin::Render(const HDC _dc)const
{
	Vector3 Pos = m_pOwner->GetTransform()->GetPosition();
	TransparentBlt(_dc
		, (int)(Pos.x - m_stSkinInfo.vSliceSize.x * 0.5f)
		, (int)(Pos.y - m_stSkinInfo.vSliceSize.y * 0.5f)
		, (int)m_stSkinInfo.vSliceSize.x
		, (int)m_stSkinInfo.vSliceSize.y
		, m_pTex->GetTextureDC()
		, (int)m_stSkinInfo.vLT.x
		, (int)m_stSkinInfo.vLT.y
		, (int)m_stSkinInfo.vSliceSize.x
		, (int)m_stSkinInfo.vSliceSize.y
		, RGB(255, 255, 255));

	return 0;
}

int CSkin::Update()
{
	return 0;
}

int CSkin::FinalUpdate()
{
	return 0;
}

CSkin::~CSkin()
{
}
