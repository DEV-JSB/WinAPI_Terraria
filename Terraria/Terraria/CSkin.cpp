#include "pch.h"
#include "CSkin.h"
#include "CResourceMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCamera.h"
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
	SetSkinInfoTexture();
	return 0;
}

int CSkin::SetSkinInfoTexture()
{
	BITMAP BitInfo = m_pTex->GetBitInfo();
	// Basic is Cut Start LT : 0,0
	m_stSkinInfo.vLT = Vector2({ 0.f,0.f });
	m_stSkinInfo.vSliceSize = Vector2({ (float)BitInfo.bmWidth,(float)BitInfo.bmHeight });
	return 0;
}

int CSkin::RenderLocalSpace(const HDC _dc) const
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

int CSkin::Render(const HDC _dc)const
{
	Vector3 Pos = m_pOwner->GetTransform()->GetPosition();
	Vector2 vDiff = CCamera::GetInstance()->GetDifference();
	Pos.x += vDiff.x;
	Pos.y += vDiff.y;
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
