#pragma once




class CCollisionMgr
{
public:
	int Update();
public:
	// Checking GroupBox Like Unity CheckBox
	int CheckingGroupBox(const OBJECT  _eLeft, const OBJECT  _eRight);
private:
	// Checking GroupBox call this function
	int CollisionCheck(const OBJECT  _eLeft, const OBJECT  _eRight);

	// GetObjectGroup
	const vector<CObject*> GetObjectVec(const OBJECT _eType);
private:
	// For Collider Union
	union COLLIDER_ID
	{
		struct
		{
			UINT Left_id;
			UINT Right_id;
		};
		LONGLONG ID;
	};


	// Hash For Collider Uion prev Collision state
	map<COLLIDER_ID, bool> m_hashmapPrevState;

	// CheckBox Group_End * 32 Box
	UINT m_arrCheckBox[(UINT)OBJECT::OBJECT_END];
private:
	SINGLE(CCollisionMgr);
};

