#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CState.h"
#include "CCreateState.h"
#include "CAcorn.h"

CMonster::CMonster()
{
	m_pAI = nullptr;
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"MonsterIdle", L"texture\\Boss\\Cagney Carnation\\Idle\\Idle.png");
	m_Create = CResourceManager::getInst()->LoadD2DImage(L"MonsterCreate", L"texture\\Boss\\Cagney Carnation\\create\\create.png");
	m_CreateIng = CResourceManager::getInst()->LoadD2DImage(L"MonsterCreateIng", L"texture\\Boss\\Cagney Carnation\\create\\create.png");
	SetName(L"Monster");
	SetScale(fPoint(400, 500));

	CreateCollider();
	GetCollider()->SetScale(fPoint(280.f, 450.f));
	GetCollider()->SetOffsetPos(fPoint(50.f, 0.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MonIdle", m_Idle, fPoint(0, 0), fPoint(400.f, 600.f), fPoint(400.f, 0), 0.06f, 18);
	GetAnimator()->CreateAnimation(L"MonCreate", m_Create, fPoint(0, 0), fPoint(400.f, 600.f), fPoint(400.f, 0), 0.059f, 22);
	GetAnimator()->CreateAnimation(L"MonCreateIng", m_CreateIng, fPoint(7200, 0), fPoint(400.f, 600.f), fPoint(400.f, 0), 0.1f, 4);

	GetAnimator()->Play(L"MonIdle");
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;
	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 1.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CCreateState(STATE_MON::CREATE));

		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
	{
		


	}
		break;
	default:
		break;
	}

	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();

}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();

	if (m_Delay >= -4.f) {
		if (m_Delay <= 0) {
			
		}
		m_Delay -= fDT;
	}
}





const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}



void CMonster::update_animation()
{
	

}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"missile")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}

}
