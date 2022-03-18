#include "framework.h"
#include "CupHead.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CAnimation.h"
#include "CGravity.h"
CupHead::CupHead()
{
	//사진 불러오기
	m_Intro = CResourceManager::getInst()->LoadD2DImage(L"Intro", L"texture\\Animation\\Intro\\Intro.png");
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Run\\Run.png");
	SetName(L"Player");
	//위치 크기 지정
	SetPos(fPoint(100.f,600.f));
	SetScale(fPoint(70.f, 100.f));

	//충돌체
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 55.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//애니메이션 생성
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"intro", m_Intro, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 28);
	GetAnimator()->CreateAnimation(L"RNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RA", m_Idle, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LA", m_Idle, fPoint(0.f,100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, false/*좌우 반전*/);

	CreateGravity();
	GetAnimator()->Play(L"RNone");
}

CupHead::~CupHead()
{
}

CupHead* CupHead::Clone()
{
	return new CupHead(*this);
}

void CupHead::update()
{
	fPoint pos = GetPos();
	pRigid = GetRigidBody();
	update_move();
	update_animation();
	//update_gravity();
	
	GetAnimator()->update();
}

void CupHead::render()
{
	component_render();
}

void CupHead::update_move()
{
	fPoint pos = GetPos();
	CRigidBody* pRigid = GetRigidBody();

	m_fVelocity = 0.f;

	if (Key(VK_LEFT))
	{
		//pRigid->AddForce(fPoint(-200.f, 0.f));
		pos.x -= m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIsLeft = true;
	}

	if (Key(VK_RIGHT))
	{
		//pRigid->AddForce(fPoint(200.f, 0.f));
		pos.x += m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIsLeft = false;
	}
	SetPos(pos);
}

void CupHead::update_animation()
{
	if (m_bIsLeft)
	{
		if (m_fVelocity > 0)
		{
			GetAnimator()->Play(L"LRun");
		}
		else
		{
			GetAnimator()->Play(L"LNone");
		}
	}
	else
	{
		if (m_fVelocity > 0)
		{
			GetAnimator()->Play(L"RRun");
		}
		else
		{
			GetAnimator()->Play(L"RNone");
		}
	}
}

void CupHead::update_gravity()
{
	GetRigidBody()->AddForce(fPoint(0.f, 500.f));
}
