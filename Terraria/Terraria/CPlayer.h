#pragma once
#include"CFactory.h"
#include"CMover.h"

class CItem;
class CAnimator;

class CPlayer : public CMover
{
public:
	int GetHealth()const { return m_iHealth; }
public: // Inventory Function
	int AcquireItem(CItem* _pItem);
	const vector<CItem*> GetPlayerItem() const { return m_vecInventory; }
	int GetFocusingIndex()const { return (int)m_eFocusInventoryIdx; }
public: // Collision Event
	// On Collision
	virtual int OnCollision(CObject* _pOther)			override;
	// Enter Collsiion
	virtual int OnCollisionEnter(CObject* _pOther)		override;
	// Exit Collision
	virtual int OnCollisionExit(CObject* _pOther)		override;
public:
	virtual int FinalUpdate() override;
	virtual int Update() override;
	virtual int Render(const HDC _dc) override;
private:
	virtual int CreateAnimator() override;
private:// Mover Update Logic 
	virtual int Update_Move()								override;
	virtual int Update_Animation()							override;
	virtual int Update_State()								override;
	virtual int Update_Gravity()							override;
private:
	virtual int CreateCollider()							override;
private:
	int Update_Arm(CAnimator* _pAnimator);
	int Update_Leg(CAnimator* _pAnimator);
	int Update_Inventory();
	int Update_ItemFlip(const bool _b);
private:
	enum class PLAYER_STATE { STATE_IDLE, STATE_LEFTRUN, STATE_RIGHTRUN, STATE_END };
private: // Member
	// Health
	int m_iHealth;
	// Inventory
	vector<CItem*> m_vecInventory;
	// EquipWeapon
	CItem* m_pEquipItem;
	// FocusInventoryType
	EQUIP_INVENTORY m_eFocusInventoryIdx;

	// For Using State
	bool m_bToolUsingState;

	// For State
	bool m_bIsOnGround;
	MOVER_STATE m_eWillState;
	MOVER_STATE m_eState;
private:
	HIDE_CONSTRUCTOR(CPlayer);
public:
	virtual ~CPlayer();
};

