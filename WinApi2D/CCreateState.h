#pragma once
#include "CState.h"

class CAcorn;

class CCreateState : public CState
{
	friend class CGameObject;

private:
	float m_fDT;

	CMonster* pMonster;
	CAcorn* pAcorn;

	int AttackCount = 0;
	bool crafting = false;
public:
	CCreateState(STATE_MON state);
	virtual ~CCreateState();

	void CreateAcorn();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

