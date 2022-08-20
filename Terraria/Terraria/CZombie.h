#pragma once
#include "CMover.h"
#include "CFactory2.h"

class CZombie : public CMover
{
public:
	int Setting(const float _x,const float _y);
public: // Update Logic
	virtual int FinalUpdate()								override;
	virtual int Update()									override;
	virtual int Render(const HDC _dc)						override;
public: // Collision Event
// On Collision
	virtual int OnCollision(CObject* _pOther)			override;
	// Enter Collsiion
	virtual int OnCollisionEnter(CObject* _pOther)	override;
	// Exit Collision
	virtual int OnCollisionExit(CObject* _pOther)		override;
private:
	virtual int CreateCollider()							override;
	virtual int CreateAnimator()							override;

private:// Mover Update Logic
	virtual int Update_Move()								override;
	virtual int Update_Animation()							override;
	virtual int Update_State()								override;
	virtual int Update_Gravity()							override;


private:
	bool m_bIsOnGround;
	int m_iHealth;
	Vector2 m_vecMoveDirection;
private:
	friend class CFactory2;
	CZombie();
public:
	virtual ~CZombie();

};