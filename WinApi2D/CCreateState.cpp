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
	//TODO : ���� ������ �ȵǴϱ� ���� Ŭ�������� ������ �õ�
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
	//Creat �ִϸ��̼� ����ϰ�
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
