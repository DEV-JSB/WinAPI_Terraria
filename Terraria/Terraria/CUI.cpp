#include"pch.h"
#include"CUI.h"
#include"CTransform2D.h"

int CUI::Update()
{
	return 0;
}

int CUI::Render(HDC _dc)
{
	CTransform2D* pTrans = GetTransform();
	Rectangle(_dc, (int)(pTrans->GetPosition_X() - pTrans->GetScale_Hegiht() / 2.f)
				 , (int)(pTrans->GetPosition_Y() - pTrans->GetPosition_Y() / 2.f	 )
				 , (int)(pTrans->GetPosition_X() + pTrans->GetScale_Hegiht() / 2.f)
				 , (int)(pTrans->GetPosition_Y() + pTrans->GetPosition_Y() / 2.f  ));
	
	return 0;
}

CUI::CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale)
	:CObject(_pos,_rot,_scale)
{
}

CUI::CUI()
{
}

CUI::~CUI()
{
}