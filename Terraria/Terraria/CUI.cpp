#include"pch.h"
#include"CUI.h"
#include"CTransform2D.h"
#include"Function.h"
int CUI::AddChild(CUI* _pChild)
{
	m_vecChildUI.push_back(_pChild);
	_pChild->m_pParent = this;
	return 0;
}

int CUI::Update()
{
	return 0;
}

int CUI::Render(const HDC _dc)
{




	CTransform2D* pTrans = GetTransform();
	Rectangle(_dc, (int)(pTrans->GetPosition_X() - pTrans->GetScale_Width() / 2.f)
				 , (int)(pTrans->GetPosition_Y() - pTrans->GetScale_Height() / 2.f	 )
				 , (int)(pTrans->GetPosition_X() + pTrans->GetScale_Width() / 2.f)
				 , (int)(pTrans->GetPosition_Y() + pTrans->GetScale_Height() / 2.f  ));
	Render_Child(_dc);
	return 0;
}

int CUI::FinalUpdate()
{
	if (GetParent())
	{
		CTransform2D* pTransform = GET_COMPONENT(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
		Vector3 Pos = pTransform->GetPosition();
		Pos += m_vOffsetPos;
		pTransform->SetPosition(Pos);
	}
	return 0;
}



int CUI::Update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		m_vecChildUI[i]->Update();
	return 0;
}

int CUI::Render_Child(const HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
	return 0;
}

int CUI::FinalUpdate_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate_Child();
	}
	return 0;
}

CUI::CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale,bool _bAffected)
	:CObject(_pos, _rot, _scale)
	, m_pParent(nullptr)
	, m_vOffsetPos({ 0.f,0.f,0.f })
	, m_bCamAffected(_bAffected)
{
}

CUI::CUI(const bool _bAffected)
	:m_pParent(nullptr)
	, m_vOffsetPos({ 0.f,0.f,0.f })
	, m_bCamAffected(_bAffected)
{
}

CUI::~CUI()
{
	Delete_Vec<CUI*>(m_vecChildUI);
}