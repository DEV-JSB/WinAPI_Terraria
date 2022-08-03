#include "pch.h"
#include"CTransform2D.h"
#include "CAnimationUI.h"
#include"CAnimation.h"

int CAnimationUI::PlayAnimationSample(const HDC _dc)
{
	if (0 == m_vecAnimationSample.size())
		return 0;
	for (size_t i = 0; i < m_vecAnimationSample.size(); ++i)
	{
		if( 0 != m_vecAnimationSample[i]->GetFrameCount() )
			m_vecAnimationSample[i]->SampleRender(_dc, m_vSamplePos);
	}
	return 0;
}



int CAnimationUI::Update()
{
	if (0 == m_vecAnimationSample.size())
		return 0;
	for (size_t i = 0; i < m_vecAnimationSample.size(); ++i)
	{
		if(0 != m_vecAnimationSample[i]->GetFrameCount())
			m_vecAnimationSample[i]->Update();
	}
	return 0;
}

int CAnimationUI::Render(const HDC _dc)
{
	CUI::Render(_dc);

	// Draw Pivot Line
	CTransform2D* pTrans = CUI::GetTransform();
	MoveToEx(_dc
			, (int)(pTrans->GetPosition_X() - pTrans->GetScale_Width() * 0.5f)
			, (int)pTrans->GetPosition_Y()
			, NULL);
	LineTo(_dc
		, (int)(pTrans->GetPosition_X() + pTrans->GetScale_Width() * 0.5f)
		, (int)pTrans->GetPosition_Y());

	MoveToEx(_dc
		, (int)pTrans->GetPosition_X()
		, (int)(pTrans->GetPosition_Y() - pTrans->GetScale_Height() * 0.5f)
		, NULL);
	LineTo(_dc
		, (int)pTrans->GetPosition_X()
		, (int)(pTrans->GetPosition_Y() + pTrans->GetScale_Height() * 0.5f));
	
	if (0 != m_vecAnimationSample.size())
		PlayAnimationSample(_dc);
	return 0;
}

int CAnimationUI::FinalUpdate()
{
	CUI::FinalUpdate();
	return 0;
}

int CAnimationUI::MouseButtonClicked()
{
	return 0;
}

CAnimationUI::CAnimationUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected)
	:CUI(_pos,_rot,_scale,_bAffected)
	,m_iAnimationIndex(0)
{
	CTransform2D* pTrans = CUI::GetTransform();
	m_vSamplePos.x = pTrans->GetPosition_X();
	m_vSamplePos.y = pTrans->GetPosition_Y();
	m_eType = UI_TYPE::UI_ANIMTAION;
}

CAnimationUI::~CAnimationUI()
{
}
