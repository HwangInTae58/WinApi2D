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
	//Creat �ִϸ��̼� ����ϰ�
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
	// �ִϸ��̼� �߰��� ���丮 3���� �վȿ� 3�� ����ϰ�
	// �÷��̾� ��ġ�� �˰� �ű�� ���������� ������
	// �ִϸ��̼��� ������ Idle���·� ���
	
	
}

void CCreateState::Enter()
{
	m_fDT = 0;
}

void CCreateState::Exit()
{
}
