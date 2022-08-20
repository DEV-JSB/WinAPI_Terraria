#pragma once
#include "CMover.h"
#include "CFactory2.h"

class CZombie : public CMover
{
public: // Update Logic
	virtual int FinalUpdate()								override;
	virtual int Update()									override;
	virtual int Render(const HDC _dc)						override;
public: // Collision Event
// On Collision
	virtual int OnCollision(const CObject* _pOther)			override;
	// Enter Collsiion
	virtual int OnCollisionEnter(const CObject* _pOther)	override;
	// Exit Collision
	virtual int OnCollisionExit(const CObject* _pOther)		override;
private:
	virtual int CreateCollider()							override;
	virtual int CreateAnimator()							override;

private:// Mover Update Logic
	virtual int Update_Move()								override;
	virtual int Update_Animation()							override;
	virtual int Update_State()								override;
	virtual int Update_Gravity()							override;
private:
	friend class CFactory2;
	CZombie(const Vector3 _pos,const Vector3 _rot ,const Vector2 _scale);
public:
	virtual ~CZombie();

};