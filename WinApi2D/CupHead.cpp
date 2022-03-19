#include "framework.h"
#include "CupHead.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CupHead::CupHead()
{
	//���� �ҷ�����
	m_Intro = CResourceManager::getInst()->LoadD2DImage(L"Intro", L"texture\\Animation\\Intro\\Intro.png");
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Run\\Run.png");
	m_shoot = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Shoot\\Shoot.png");
	SetName(L"Player");
	//��ġ ũ�� ����
	SetPos(fPoint(100.f,600.f));
	SetScale(fPoint(70.f, 100.f));

	//�浹ü
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 55.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//�ִϸ��̼� ����
	CreateAnimator();
	//��Ʈ��
	GetAnimator()->CreateAnimation(L"intro", m_Intro, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 28);
	//������
	GetAnimator()->CreateAnimation(L"RNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RA", m_Idle, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LA", m_Idle, fPoint(0.f,100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*�¿� ����*/);
	//�޸���
	GetAnimator()->CreateAnimation(L"LRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, false/*�¿� ����*/);
	//���
	GetAnimator()->CreateAnimation(L"RSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"RDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*�¿� ����*/);
	GetAnimator()->CreateAnimation(L"LDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*�¿� ����*/);

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
	update_move();
	update_animation();
	
	GetAnimator()->update();
}

void CupHead::render()
{
	component_render();
}
void CupHead::Jump()
{
	float y = GetPos().y;
	float gravity = 0.0f;     // �߷´�����
	int direction = 0;       // 0:��������, 1:������, 2:�ٿ���
	// ������
	const float jump_speed = 0.2f;  // �����ӵ�
	const float jump_accell = 0.01f; // ��������
	const float y_base = 0.5f;      // ĳ���Ͱ� ���ִ� ������
	y += gravity;
	if (gravity <= 0.0f)
	{
		direction = 2;
	}
	else
	{
		gravity -= jump_accell;
	}

}

void CupHead::OnCollision(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		fPoint Pos = GetPos();
		if (Pos.y < pOtherObj->GetPos().y)
		{
			PLAYER_MOVE::IDLE;
		}
	}
}

void CupHead::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	if (m_bIs == 2)
	{
		pMissile->SetDir(fVec2(1, 0));
	}
	else if (m_bIs == 1)
	{
		pMissile->SetDir(fVec2(-1, 0));
	}
	pMissile->SetName(L"Missile");
	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}
	
void CupHead::update_move()
{
	fPoint pos = GetPos();

	m_fVelocity = 0.f;

	if (Key(VK_LEFT))
	{
		PLAYER_MOVE::RUN;
		pos.x -= m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIs = 1;
	}

	if (Key(VK_RIGHT))
	{
		PLAYER_MOVE::RUN;
		pos.x += m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIs = 2;
	}

	if (KeyDown('Z'))
	{
		PLAYER_MOVE::JUMP;
		Jump();
		m_fVelocity = m_fSpeed;
	}
	if (KeyDown('X'))
	{
		CreateMissile();
	}
	SetPos(pos);
}

void CupHead::update_animation()
{
	if (m_bIs == 1)
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


