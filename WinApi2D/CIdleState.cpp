#include "framework.h"
#include "CIdleState.h"
#include "CupHead.h"
#include "CMonster.h"
#include "CAnimator.h"

CIdleState::CIdleState(STATE_MON state)
	: CState(state)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	m_fDT += fDT;
	CMonster* pMonster = GetMonster();
	
	if (m_fDT > 3.f)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::CREATE);
	}
	pMonster->GetAnimator()->Play(L"MonIdle");
}

void CIdleState::Enter()
{
	m_fDT = 0;
}

void CIdleState::Exit()
{
}
