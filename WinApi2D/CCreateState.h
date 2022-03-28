#pragma once
#include "CState.h"

class CAcorn;

class CCreateState : public CState
{
private:
	float m_fDT;

	CMonster* pMonster;
	CAcorn* pAcorn;

	bool crafting = false;
public:
	CCreateState(STATE_MON state);
	virtual ~CCreateState();

	void CreateAcorn();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

