#include "framework.h"
#include "CTraceState.h"
#include "CupHead.h"
#include "CMonster.h"
#include "CAnimator.h"

CTraceState::CTraceState(STATE_MON state)
	: CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CupHead* pPlayer = CupHead::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	pMonster->SetPos(pos);
	pMonster->GetAnimator()->Play(L"MonsterTrace");
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
