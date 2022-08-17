#pragma once
#include"CFactory.h"
#include"CMover.h"

class CItem;

class CPlayer : public CMover
{

public: // Inventory Function
	int AcquireItem(CItem* _pItem) { m_vecInventory.push_back(_pItem); return 0; }
	const vector<CItem*> GetPlayerItem() { return m_vecInventory; }
public: // Collision Event
	// On Collision
	virtual int OnCollision(const CObject* _pOther)			override;
	// Enter Collsiion
	virtual int OnCollisionEnter(const CObject* _pOther)	override;
	// Exit Collision
	virtual int OnCollisionExit(const CObject* _pOther)		override;
public:
	virtual int FinalUpdate() override;
	virtual int Update() override;
	virtual int Render(const HDC _dc) override;

private:

	virtual int CreateAnimator() override;

private:

	// Update Logic 
	virtual int Update_Move()								override;
	virtual int Update_Animation()							override;
	virtual int Update_State()								override;
	virtual int Update_Gravity()							override;

	int CreateCollider(const Vector2 _pos)					override;
private:
	enum class PLAYER_STATE { STATE_IDLE, STATE_LEFTRUN, STATE_RIGHTRUN, STATE_END };
private: // Member
	// Inventory
	vector<CItem*> m_vecInventory;

	// For State
	bool m_bIsOnGround;
	MOVER_STATE m_eWillState;
	MOVER_STATE m_eState;
private:
	HIDE_CONSTRUCTOR(CPlayer);
public:
	virtual ~CPlayer();
};

