#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"

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


CCollisionMgr::~CCollisionMgr()
{

}
