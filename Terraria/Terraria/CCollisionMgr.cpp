#include "pch.h"
#include "CCollisionMgr.h"
#include "CCollider.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"
#include"CBoxCollider.h"
#include"CCircleCollider.h"
#include "CObject.h"
CCollisionMgr::CCollisionMgr()
	:m_arrCheckBox{}
{

}


int CCollisionMgr::Update()
{
	// CheckBox Check Is Checking
	for (UINT iRow = 0; iRow < (UINT)OBJECT::OBJECT_END; ++iRow)
	{
		for (UINT iColum = 0; iColum < (UINT)OBJECT::OBJECT_END; ++iColum)
		{
			if (m_arrCheckBox[iRow] & (1 << iColum))
			{
				// Collision Check EachOther
				CollisionCheck((OBJECT)iRow, (OBJECT)iColum);
			}
		}
	}
	return 0;
}

int CCollisionMgr::CollisionCheck(const OBJECT _eLeft, const OBJECT _eRight)
{
	// GetCollision Group
	const vector<CObject*>& vecRight = GetObjectVec(_eLeft);
	const vector<CObject*>& vecLeft  = GetObjectVec(_eRight);

	// Collision Check Each Other
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// If don't have Collider Exeption handling
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// If don't have Collider Exeption handling
			// || Same GroupCheck then will Check Same Collider Exeption Handling
			if (nullptr == vecRight[j]->GetCollider()
				|| vecRight[j] == vecLeft[i])
				continue;
			CCollider* pLeftCollider = vecLeft[i]->GetCollider();
			CCollider* pRightCollider = vecRight[j]->GetCollider();

			// ID Search for Prev State check
			COLLIDER_ID NewID;
			NewID.Left_id = pLeftCollider->GetID();
			NewID.Right_id = pRightCollider->GetID();

			auto iter = m_mapPrevState.find(NewID.ID);
			if (iter == m_mapPrevState.end())
			{
				// If can't find then the first check Each other so Insert false prevstate
				m_mapPrevState.insert({ NewID.ID,false });
				// And refresh iterator
				iter = m_mapPrevState.find(NewID.ID);
			}
			
			// Checking Is Collision
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// Prev state was Collision
				if (true == iter->second)
				{
					vecLeft[i]->OnCollision(vecRight[j]);
					vecRight[j]->OnCollision(vecLeft[i]);
				}
				else
				{
					
					vecLeft[i]->OnCollisionEnter(vecRight[j]);
					vecRight[j]->OnCollisionEnter(vecLeft[i]);
					iter->second = true;
					// Exception Handling
					if (pLeftCollider->GetOwnerType() == OBJECT::OBJECT_ITEM && pRightCollider->GetOwnerType() == OBJECT::OBJECT_ZOMBIE)
						iter->second = false;
					else if (pLeftCollider->GetOwnerType() == OBJECT::OBJECT_ZOMBIE && pRightCollider->GetOwnerType() == OBJECT::OBJECT_ITEM)
						iter->second = false;
					/////////////////////

				}
			}
			else
			{
				// If NotCollision But was Collision
				if (true == iter->second)
				{
					vecLeft[i]->OnCollisionExit(vecRight[j]);
					vecRight[j]->OnCollisionExit(vecLeft[i]);
					iter->second = false;
				}
			}
		}
	}
	return 0;
}

bool CCollisionMgr::IsCollision(CCollider* _left, CCollider* _right)
{
	// AABB Collision Check
	if (COLLIDER::COLLIDER_RECT == _left->GetType()
		&& COLLIDER::COLLIDER_RECT == _right->GetType())
	{
		
		Vector2 vLeftPos = _left->GetPos();
		Vector2 vLeftScale = RTTI_DYNAMIC_CAST(_left,CBoxCollider)->GetScale();
		Vector2 vRightPos = _right->GetPos();
		Vector2 vRightScale = RTTI_DYNAMIC_CAST(_right, CBoxCollider)->GetScale();
		
		if ((int)abs(vLeftPos.x - vRightPos.x) < (int)(vLeftScale.x * 0.5f + vRightScale.x * 0.5f)
			&& (int)abs(vLeftPos.y - vRightPos.y) < (int)(vLeftScale.y * 0.5f + vRightScale.y * 0.5f))
		{
			if (_right->GetOwnerType() == OBJECT::OBJECT_ITEM && _left->GetOwnerType() == OBJECT::OBJECT_ZOMBIE)
				printf("Ãæµ¹!\n");
			return true;
		}
		else
			return false;
	}

	return 0;
}

const vector<CObject*> CCollisionMgr::GetObjectVec(const OBJECT  _eType)
{
	if (_eType == OBJECT::OBJECT_TILE)
		return CTileMgr::GetInstance()->GetTileGroup();
	else
		return CSceneMgr::GetInstance()->GetObjectGroup(_eType);
}

int CCollisionMgr::CheckingGroupBox(const OBJECT  _eLeft, const OBJECT  _eRight)
{
	// Smaller Use Row
	// Because We Use Only Half

	UINT iRow = (UINT)_eLeft;
	UINT iColum = (UINT)_eRight;

	if (iRow < iColum)
	{
		iRow = (UINT)_eRight;
		iColum = (UINT)_eLeft;
	}

	//If Check GroupBox On 
	if (m_arrCheckBox[iRow] & (1 << iColum))
	{
		// Release Check
		m_arrCheckBox[iRow] &= !(1 << iColum);
	}
	// If Check GroupBox Off
	else
	{
		m_arrCheckBox[iRow] |= (1 << iColum);
	}

	return 0;
}

bool CCollisionMgr::CheckingPointOnTile(const POINT _point)
{
	const vector<CObject*>vecTile = GetObjectVec(OBJECT::OBJECT_TILE);
	
	CCollider* pCollider;
	Vector2 vPos;
	Vector2 vScale;
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		pCollider = vecTile[i]->GetCollider();
		CBoxCollider* pBox = RTTI_DYNAMIC_CAST(pCollider,CBoxCollider);
		vPos = pBox->GetPos();
		vScale = pBox->GetScale();

		if (vPos.x - vScale.x * 0.5f <= _point.x && _point.x <= vPos.x + vScale.x * 0.5f
			&& vPos.y - vScale.y * 0.5f <= _point.y && _point.y <= vPos.y + vScale.y * 0.5f)
			return true;
	}
	return false;
}


CCollisionMgr::~CCollisionMgr()
{

}
