#pragma once
#include"CObject.h"
#include"CFactory.h"

class CPlayer : public CObject
{


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
	// Update Logic 
	int Update_Move();
	int Update_Animation();
	int Update_State();
	int Update_Gravity();

	int CreateCollider(const Vector2 _pos);
private:
	enum class PLAYER_STATE { STATE_IDLE, STATE_LEFTRUN, STATE_RIGHTRUN, STATE_END };
private:
	bool m_bIsOnGround;
	PLAYER_STATE m_eWillState;
	PLAYER_STATE m_eState;
private:
	HIDE_CONSTRUCTOR(CPlayer);
public:
	virtual ~CPlayer();
};

