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
	//TODO : 여기 생성이 안되니까 몬스터 클래스에서 생성을 시도
	fPoint acornPos = pMonster->GetPos();

	CAcorn* acorn = new CAcorn;
	acorn->SetPos(acornPos);
	if (crafting == true)
	{
		acorn->SetDir(fVec2(-1, 0));
		acornPos.x += pMonster->GetScale().x / 2.f;
	}
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
		if (m_fDT >= 5.f) {
			crafting = true;
			CreateAcorn();
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
