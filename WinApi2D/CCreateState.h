#pragma once
#include "CState.h"

class CAcorn;
class CupHead;

class CCreateState : public CState
{
	friend class CGameObject;

private:
	float m_fDT;

	CupHead* TarGet;
	CMonster* pMonster;
	CAcorn* pAcorn;

	CAcorn* acorn;
	CAcorn* acorn2;
	CAcorn* acorn3;

	int AttackCount = 0;
	float m_AttfDT;

	bool crafting = false;
public:
	CCreateState(STATE_MON state);
	virtual ~CCreateState();

	void CreateAcorn();

	

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

