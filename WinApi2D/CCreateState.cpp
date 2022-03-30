#include "framework.h"
#include "CCreateState.h"
#include "CGameObject.h"
#include "CAcorn.h"
#include "CupHead.h"
#include "CMonster.h"
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
	acorn = new CAcorn;
	acorn2 = new CAcorn;
	acorn3 = new CAcorn;
	fPoint acornPos = pMonster->GetPos();
	fPoint acornPos2 = pMonster->GetPos();
	fPoint acornPos3 = pMonster->GetPos();

	acornPos.y -= pMonster->GetScale().y / 4.f;
	acornPos.x -= pMonster->GetScale().x / 3.5f;
	crafting = true;
	acorn->SetPos(acornPos);
	acorn->SetDir(fPoint(-7,1));
	
	CreateObj(acorn, GROUP_GAMEOBJ::MISSILE_MONSTER);


	acornPos2.y -= pMonster->GetScale().y / 12.f;
	acornPos2.x -= pMonster->GetScale().x / 3.5f;
	acorn2->SetPos(acornPos2);
	acorn2->SetDir(fPoint(-7, 1));
	CreateObj(acorn2, GROUP_GAMEOBJ::MISSILE_MONSTER);

	

	acornPos3.y -= pMonster->GetScale().y / 10000.f;
	acornPos3.x -= pMonster->GetScale().x / 3.5f;
	acorn3->SetPos(acornPos3);
	acorn3->SetDir(fPoint(-7, 1));
	CreateObj(acorn3, GROUP_GAMEOBJ::MISSILE_MONSTER);
	
}


void CCreateState::update()
{
	if (crafting)
	{
		m_AttfDT += fDT;
	}
	if (m_AttfDT >= 0.3f) {
		acorn->SetSpeed(650.f);
	}
	if (m_AttfDT >= 0.8f) {
		acorn2->SetSpeed(650.f);
	}
	if (m_AttfDT >= 1.3f) {
		acorn3->SetSpeed(650.f);
	}

	m_fDT += fDT;
	pMonster = GetMonster();
	//Creat 애니메이션 출력하고
	pMonster->GetAnimator()->Play(L"MonCreate");
	
	if (m_fDT >= 1.3f)
	{
		pMonster->GetAnimator()->Play(L"MonCreateIng");
		if(AttackCount == 0)
		{
			crafting = true;
			CreateAcorn();
			AttackCount++;
		}
		if (m_fDT >= 5.f) {
			crafting = false;
			m_AttfDT = 0;
			AttackCount = 0;
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
