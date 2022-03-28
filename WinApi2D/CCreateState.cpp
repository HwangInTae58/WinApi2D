#include "framework.h"
#include "CCreateState.h"
#include "CGameObject.h"
#include "CMonster.h"
#include "CAcorn.h"
#include "CAnimator.h"

CCreateState::CCreateState(STATE_MON state)
	: CState(state)
{
}

CCreateState::~CCreateState()
{
}

void CCreateState::CreateAcorn()
{
	pMonster = GetMonster();
	CAcorn* acorn = new CAcorn;

	fPoint acornPos = pMonster->GetPos();

	acorn->SetPos(acornPos);

	acorn->SetDir(fVec2(-1, 0));
	acornPos.x -= pMonster->GetScale().x / 2.f;
	CreateObj(acorn, GROUP_GAMEOBJ::MISSILE_MONSTER);
}


void CCreateState::update()
{
	crafting = false;
	m_fDT += fDT;
	pMonster = GetMonster();
	//Creat 애니메이션 출력하고
	pMonster->GetAnimator()->Play(L"MonCreate");
	
	if (m_fDT >= 1.3f)
	{
		pMonster->GetAnimator()->Play(L"MonCreateIng");
		if (AttackCount == 0)
	
		CreateAcorn();
		if (m_fDT >= 5.f) {
			crafting = true;
			
			ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
		}
	}
	// 애니메이션 중간에 도토리 3개를 손안에 3개 출력하고
	// 플레이어 위치를 알고 거기로 일직선으로 나가게
	// 애니메이션이 끝나면 Idle상태로 출력
	
	
}

void CCreateState::Enter()
{
	m_fDT = 0;
}

void CCreateState::Exit()
{
}
