#pragma once

// For Collider Union
union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	LONGLONG ID;
	bool operator < (const COLLIDER_ID& a)const
	{	
		return false;
	}
};



class CCollisionMgr
{
public:
	int Update();
public:
	// Checking GroupBox Like Unity CheckBox
	int CheckingGroupBox(const OBJECT  _eLeft, const OBJECT _eRight);

	// Checking Just Point On Tile
	bool CheckingPointOnTile(const POINT _point);

private:
	// Checking GroupBox call this function
	int CollisionCheck(const OBJECT  _eLeft, const OBJECT  _eRight);

	// Checking Is Collision
	bool IsCollision(CCollider* _left,CCollider* _right);	

	// GetObjectGroup
	const vector<CObject*> GetObjectVec(const OBJECT _eType);
private:

	// Hash For Collider Uion prev Collision state
	map<LONGLONG, bool> m_mapPrevState;
	// CheckBox Group_End * 32 Box
	UINT m_arrCheckBox[(UINT)OBJECT::OBJECT_END];
private:
	SINGLE(CCollisionMgr);
};

