#pragma once
#include "CObject.h"


class CMover :
    public CObject
{
public: // Collision Event
// On Collision
	virtual int OnCollision(const CObject* _pOther)			= 0;
	// Enter Collsiion
	virtual int OnCollisionEnter(const CObject* _pOther)	= 0;
	// Exit Collision
	virtual int OnCollisionExit(const CObject* _pOther)		= 0;

protected: 

	// RayCast
	bool FootRayCast();

	// Setting Animator
	virtual int CreateAnimator() = 0;
	// Setting RigidBody Function
	int SetRigidbody(const RIGIDBODY _eType, float _f);

public: // Update Logic
	virtual int FinalUpdate()								= 0;
	virtual int Update()									= 0;
	virtual int Render(const HDC _dc)						= 0;

private: // MoverMust Have Collider 
	virtual int CreateCollider(const Vector2 _pos)			= 0;

private:// Mover Update Logic
	virtual int Update_Move()								= 0;
	virtual int Update_Animation()							= 0;
	virtual int Update_State()								= 0;
	virtual int Update_Gravity()							= 0;

protected:
	enum class MOVER_STATE { STATE_IDLE , STATE_LEFTRUN , STATE_RIGHTRUN , STATE_JUMP , STATE_END };
protected:
	CMover(const OBJECT _eType, const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
public:
	virtual ~CMover();
};

