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
	CAcorn* acorn2 = new CAcorn;
	CAcorn* acorn3 = new CAcorn;
	fPoint acornPos = pMonster->GetPos();
	fPoint acornPos2 = pMonster->GetPos();
	fPoint acornPos3 = pMonster->GetPos();

	acornPos.y -= pMonster->GetScale().y / 4.f;
	acornPos.x -= pMonster->GetScale().x / 3.5f;
	crafting = true;
	acorn->SetPos(acornPos);
	acorn->SetDir(fVec2(-4, 1));
	CreateObj(acorn, GROUP_GAMEOBJ::MISSILE_MONSTER);

	acornPos2.y -= pMonster->GetScale().y / 12.f;
	acornPos2.x -= pMonster->GetScale().x / 3.5f;
	acorn2->SetPos(acornPos2);
	acorn2->SetDir(fVec2(-4, 1));
	CreateObj(acorn2, GROUP_GAMEOBJ::MISSILE_MONSTER);
	
	acornPos3.y -= pMonster->GetScale().y / 10000.f;
	acornPos3.x -= pMonster->GetScale().x / 3.5f;
	acorn3->SetPos(acornPos3);
	acorn3->SetDir(fVec2(-3, 1));
	CreateObj(acorn3, GROUP_GAMEOBJ::MISSILE_MONSTER);
	
}


void CCreateState::update()
{
	m_fDT += fDT;
	pMonster = GetMonster();
	//Creat �ִϸ��̼� ����ϰ�
	pMonster->GetAnimator()->Play(L"MonCreate");
	
	if (m_fDT >= 1.3f)
	{
		pMonster->GetAnimator()->Play(L"MonCreateIng");
		if(AttackCount == 0)
		{

			CreateAcorn();
			AttackCount++;
		}
		if (m_fDT >= 3.f) {
			crafting = false;
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
