#pragma once
#include"CObject.h"
#include"CFactory.h"

class CPlayer : public CObject
{

public:
	virtual int FinalUpdate() override;
	virtual int Update() override;
	virtual int Render(const HDC _dc) override;

private:
	int Update_Move();
	int Update_Animation();
	int Update_State();
private:
	enum class PLAYER_STATE { STATE_IDLE, STATE_LEFTRUN, STATE_RIGHTRUN, STATE_END };
private:
	PLAYER_STATE m_eWillState;
	PLAYER_STATE m_eState;
private:
	HIDE_CONSTRUCTOR(CPlayer);
public:
	virtual ~CPlayer();
};

