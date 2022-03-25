#pragma once
#include "CState.h"
class CCreateState : public CState
{
private:
	float m_fDT;

	CMonster* pMonster;
public:
	CCreateState(STATE_MON state);
	virtual ~CCreateState();

	void CreateAcorn();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

