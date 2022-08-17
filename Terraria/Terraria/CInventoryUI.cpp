#include "pch.h"
#include "CInventoryUI.h"
#include "CItemPocketUI.h"
#include "CFactory2.h"
#include "CTransform2D.h"
#include "CItem.h"
#include "CInputMgr.h"
#include "CPlayer.h"

int CInventoryUI::Update()
{
	if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_ESC) == INPUTSTATE::INPUTSTATE_TAP)
	{
		printf("ESC!\n");
		m_bHidden = !m_bHidden;
	}
	return 0;
}

int CInventoryUI::Render(const HDC _dc)
{
	if (m_bHidden)
	{
		auto iter = m_mapPocket.begin();
		for (int i = 0; i < INVEN_ROW; ++i, ++iter)
			(*iter).second->Render(_dc);
	}
	else
	{
		for (auto iter = m_mapPocket.begin(); iter != m_mapPocket.end(); ++iter)
			(*iter).second->Render(_dc);
	}
	return 0;
}

int CInventoryUI::FinalUpdate()
{
	return 0;
}

int CInventoryUI::MonitorPlayerInventory()
{
	const vector<CItem*> vecItem = m_pOwner->GetPlayerItem();

	for (size_t i = 0; i < vecItem.size(); ++i)
	{
		const wstring strTexture = vecItem[i]->GetTextureName();
		m_mapPocket[i]->SetItemTexture(strTexture);
	}
	
	
	return 0;
}

CInventoryUI::CInventoryUI()
	:CUI(false)
	,m_bHidden(true)
{
	Setting();
	
	
}

int CInventoryUI::Setting()
{
	int PocketIndex = 0;
	for (int y = 0; y < INVEN_COLUM ; ++y)
	{
		for (int x = 0; x < INVEN_ROW ; ++x)
		{
			CItemPocketUI* pPocket = new CItemPocketUI;
			pPocket->Setting(x, y);
			pPocket->SetParent(this);
			pPocket->SetIndex(PocketIndex++);
			m_mapPocket.insert({ pPocket->GetIndex(),pPocket });
		}
	}

	SettingTransform();

	return 0;
}

int CInventoryUI::SettingTransform()
{
	Vector2 m_vPos1;
	Vector2 m_vPos2;
	m_vPos1.x = m_mapPocket[0]->GetTransform()->GetPosition_X() - m_mapPocket[0]->GetTransform()->GetScale_Width() * 0.5f;
	m_vPos1.y = m_mapPocket[0]->GetTransform()->GetPosition_Y() - m_mapPocket[0]->GetTransform()->GetScale_Height() * 0.5f;
	m_vPos2.x = m_mapPocket[8]->GetTransform()->GetPosition_X() + m_mapPocket[8]->GetTransform()->GetScale_Width() * 0.5f;
	m_vPos2.y = m_mapPocket[8]->GetTransform()->GetPosition_Y() + m_mapPocket[8]->GetTransform()->GetScale_Height() * 0.5f;


	CObject::CreateTransform(Vector3({ (m_vPos1.x + m_vPos2.x) * 0.5f , (m_vPos1.y + m_vPos2.y) * 0.5f ,0.f })
		, Vector3({})
		, Vector2({ m_vPos2.x - m_vPos1.x,m_vPos2.y - m_vPos1.y }));
	return 0;
}

CInventoryUI::~CInventoryUI()
{
}
