#include "pch.h"
#include "CInventoryUI.h"
#include "CItemPocketUI.h"
#include "CFactory2.h"
#include "CTransform2D.h"
#include "CItem.h"
#include "CInputMgr.h"
#include "CPlayer.h"

CInventoryUI::CInventoryUI()
	:CUI(UI_TYPE::UI_INVENTORY,false)
	, m_bHidden(true)
{
	Setting();
}
int CInventoryUI::Update()
{
	if (CInputMgr::GetInstance()->GetKeyState(KEY::KEY_ESC) == INPUTSTATE::INPUTSTATE_TAP)
	{
		m_bHidden = !m_bHidden;
	}
	PocketUI_Update();
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

int CInventoryUI::SetParentUITransform()
{
	return 0;
}

int CInventoryUI::PocketUI_Update()
{
	MonitorPlayerInventory();
	for (auto iter = m_mapPocket.begin(); iter != m_mapPocket.end(); ++iter)
		(*iter).second->Update();

	int iPlayerSelectIndex = m_pOwner->GetFocusingIndex();
	if (iPlayerSelectIndex != (int)EQUIP_INVENTORY::EQUIP_INVENTORY_END)
	{
		CItemPocketUI* pPocket = FindSelectPocket();
		// Prev SelectPocket state Change
		if (pPocket != nullptr && pPocket != m_mapPocket[(int)iPlayerSelectIndex])
		{
			pPocket->m_bIsPlayerSelect = false;
			m_mapPocket[(int)iPlayerSelectIndex]->m_bIsPlayerSelect = true;
		}
		else if (pPocket != nullptr && pPocket == m_mapPocket[(int)iPlayerSelectIndex])
		{
			return 0;
		}
		else
			m_mapPocket[(int)iPlayerSelectIndex]->m_bIsPlayerSelect = true;
	}
	return 0;
}
CItemPocketUI* CInventoryUI::FindSelectPocket()
{
	for (auto iter = m_mapPocket.begin(); iter != m_mapPocket.end(); ++iter)
	{
		if (true == (*iter).second->m_bIsPlayerSelect)
			return (*iter).second;
	}
	return nullptr;
}

int CInventoryUI::MonitorPlayerInventory()
{
	const vector<CItem*> vecItem = m_pOwner->GetPlayerItem();

	for (size_t i = 0; i < vecItem.size(); ++i)
	{
		if (vecItem[i] != nullptr)
		{
			const wstring strTexture = vecItem[i]->GetTextureName();
			m_mapPocket[i]->SetItemTexture(strTexture);
		}
	}
	


	return 0;
}




int CInventoryUI::Setting()
{
	CUI::m_eUI_Type = UI_TYPE::UI_INVENTORY;

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
	Delete_Map(m_mapPocket);
}
