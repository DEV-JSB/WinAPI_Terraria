#include"pch.h"
#include"CUI.h"
#include"CTransform2D.h"
#include"Function.h"


CUI::CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected)
	:CObject(OBJECT::OBJECT_UI,_pos, _rot, _scale)
	, m_pParent(nullptr)
	, m_vOffsetPos({ 0.f,0.f,0.f })
	, m_bCamAffected(_bAffected)
	, m_eUI_Type(UI_TYPE::UI_PARENT)
	, m_bIsFocus(false)
{
}

CUI::CUI(const bool _bAffected)
	:CObject()
	, m_pParent(nullptr)
	, m_vOffsetPos({ 0.f,0.f,0.f })
	, m_bCamAffected(_bAffected)
	, m_eUI_Type(UI_TYPE::UI_PARENT)
	, m_bIsFocus(false)
{
}

int CUI::AddChild(CUI* _pChild)
{
	UI_TYPE type = _pChild->GetUIType();
	m_vecChildUI[(int)type].push_back(_pChild);
	_pChild->m_pParent = this;
	return 0;
}

int CUI::Update()
{
	Update_Child();
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
		// Follow Parent UI
		CTransform2D* pTransform = GET_COMPONENT(CTransform2D, m_mapComponent, COMPONENT::COMPONENT_TRANSFORM2D);
		Vector3 Pos = pTransform->GetPosition();
		Pos += m_vOffsetPos;
		pTransform->SetPosition(Pos);
	}
	return 0;
}


int CUI::Release()
{
	for(int i = 0 ; i<(int)UI_TYPE::UI_END;++i)
		Delete_Vec<CUI*>(m_vecChildUI[i]);
	return 0;
}



int CUI::Update_Child()
{
	for (int i = 0; i < (int)UI_TYPE::UI_END; ++i)
	{
		for(UINT j = 0 ; j < m_vecChildUI[i].size();++j)
			m_vecChildUI[i][j]->Update();
	}
	return 0;
}

int CUI::Render_Child(const HDC _dc)
{
	for (int i = 0; i < (int)UI_TYPE::UI_END; ++i)
	{
		for (UINT j = 0; j < m_vecChildUI[i].size(); ++j)
			m_vecChildUI[i][j]->Render(_dc);
	}
	return 0;
}

int CUI::FinalUpdate_Child()
{
	for (int i = 0; i < (int)UI_TYPE::UI_END; ++i)
	{
		for (UINT j = 0; j < m_vecChildUI[i].size(); ++j)
			m_vecChildUI[i][j]->FinalUpdate();
	}
	return 0;
}


CUI::~CUI()
{
	Release();
}