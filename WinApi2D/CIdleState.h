#pragma once
#include "CState.h"
class CIdleState : public CState
{
private:
	float m_fDT;
public:
	CIdleState(STATE_MON state);
	virtual ~CIdleState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();


};

