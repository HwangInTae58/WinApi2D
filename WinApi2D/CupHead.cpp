#include "framework.h"
#include "CupHead.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"
#include "CAnimation.h"

CupHead::CupHead()
{
	m_eCurState = PLAYER_STATE::IDLE;
	m_ePreState = PLAYER_STATE::INTRO;
	m_iCurDir = 1;
	m_iPreDir = 1;
	m_blsFloor = GetFloor();
	m_iCollCount = 0;
	m_fVelocity = 0;
	m_Hight = 0;
	m_isGravity = GetGravity();
	m_isGravity = true;
	//»çÁø ºÒ·¯¿À±â
	m_Intro = CResourceManager::getInst()->LoadD2DImage(L"Intro", L"texture\\Animation\\Intro\\Intro.png");
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Run\\Run.png");
	m_shoot = CResourceManager::getInst()->LoadD2DImage(L"Shoot", L"texture\\Animation\\Shoot\\Shoot.png");
	m_duck = CResourceManager::getInst()->LoadD2DImage(L"Duck", L"texture\\Animation\\Duck\\Duck.png");
	m_jump = CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\Animation\\Jump\\Jump.png");
	SetName(L"Player");
	//À§Ä¡ Å©±â ÁöÁ¤
	SetPos(fPoint(100.f,405.f));
	SetScale(fPoint(70.f, 100.f));
	
	//Ãæµ¹Ã¼
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 65.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//¾Ö´Ï¸ÞÀÌ¼Ç »ý¼º
	CreateAnimator();
	//ÀÎÆ®·Î
	GetAnimator()->CreateAnimation(L"intro", m_Intro, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 28);
	//°¡¸¸È÷
	GetAnimator()->CreateAnimation(L"RNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RA", m_Idle, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LA", m_Idle, fPoint(0.f,100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LU", m_Idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LD", m_Idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LUD", m_Idle, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LDD", m_Idle, fPoint(0.f, 500.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5, true/*ÁÂ¿ì ¹ÝÀü*/);
	//¾þµå¸®±â
	GetAnimator()->CreateAnimation(L"RDU", m_duck, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.07f, 13, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LDU", m_duck, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.07f, 13, true/*ÁÂ¿ì ¹ÝÀü*/);
	//´Þ¸®±â
	GetAnimator()->CreateAnimation(L"LRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, false/*ÁÂ¿ì ¹ÝÀü*/);
	//»ç°Ý
	GetAnimator()->CreateAnimation(L"RSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"RDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*ÁÂ¿ì ¹ÝÀü*/);
	//Á¡ÇÁ
	GetAnimator()->CreateAnimation(L"RJM", m_jump, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.1f, 8, false/*ÁÂ¿ì ¹ÝÀü*/);
	GetAnimator()->CreateAnimation(L"LJM", m_jump, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.1f, 8, true/*ÁÂ¿ì ¹ÝÀü*/);

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
	SetGravity(true);
	update_move();
	update_animation();
	GetAnimator()->update();
	m_ePreState = m_eCurState;
}

void CupHead::render()
{
	component_render();
}


void CupHead::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Tile" && m_iCollCount > 0 )
	{
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
	}
}

void CupHead::OnCollisionEnter(CCollider* _pOther)
{
	m_iCollCount++;
	
	if (_pOther->GetObj()->GetName() == L"Tile")
	{	
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
		JumpKeyDown = false;
	}
}

void CupHead::OnCollisionExit(CCollider* _pOther)
{
	m_iCollCount--;
	if (_pOther->GetObj()->GetName() == L"Tile" && m_iCollCount <= 0)
	{
		m_isGravity = true;
		m_Gravity = 700;
		m_blsFloor = false;
	}
}

void CupHead::CreateMissile()
{
	fPoint fpMissilePos = GetPos();


	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	if (m_iCurDir == 1)
	{
		pMissile->SetDir(fVec2(1, 0));
		fpMissilePos.x += GetScale().x / 2.f;
	}
	else if (m_iCurDir == -1)
	{
		pMissile->SetDir(fVec2(-1, 0));
		fpMissilePos.x += GetScale().x / -2.f;
	}
	pMissile->SetName(L"Missile");
	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

void CupHead::update_move()
{
	fPoint pos = GetPos();
	
	if (m_isGravity == true)
	{
		m_fDir.y -= m_Gravity * fDT;
		pos.y += -m_fDir.y * fDT;
	}
	if (Key(VK_LEFT))
	{
		m_iCurDir == -1;
		m_eCurState = PLAYER_STATE::RUN;
			pos.x -= m_fSpeed * fDT;
			m_fVelocity = m_fSpeed;
	}
	if (Key(VK_RIGHT))
	{
		m_eCurState = PLAYER_STATE::RUN;
		m_iCurDir == 1;
			pos.x += m_fSpeed * fDT;
			m_fVelocity = m_fSpeed;
	}
	if (Key(VK_UP))
	{
			
	}
	if (Key(VK_DOWN))
	{
	}

	if (KeyDown('Z'))
	{
		if(m_blsFloor && !JumpKeyDown){
		m_eCurState = PLAYER_STATE::JUMP;
		JumpKeyDown = true;
		JumpForce = 900.f;
		pos.y -= JumpForce * fDT;
		}
		
	}
	if (KeyDown('X'))
	{
		m_eCurState = PLAYER_STATE::ATTACK;
		CreateMissile();
	}
	if (0.f == m_fVelocity && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	SetPos(pos);
}

void CupHead::update_animation()
{
	if (m_ePreState == m_eCurState && m_iPreDir == m_iCurDir)
	{
		return;
	}
	switch (m_eCurState)
	{
	case PLAYER_STATE::INTRO:
		break;
	case PLAYER_STATE::IDLE:
	{
		if (-1 == m_iCurDir && m_blsFloor && m_fVelocity == 0)
		{
			GetAnimator()->Play(L"LNone");
		}
		else if (1 == m_iCurDir && m_blsFloor && m_fVelocity == 0)
		{
			GetAnimator()->Play(L"RNone");
		}
	}
	break;
	case PLAYER_STATE::DOCK:
	{

	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (-1 == m_iCurDir && m_blsFloor && m_fVelocity > 0)
		{
			GetAnimator()->Play(L"LRun");
		}
		else if (1 == m_iCurDir && m_blsFloor && m_fVelocity > 0)
		{
			GetAnimator()->Play(L"RRun");
		}
		break;
	}
	case PLAYER_STATE::JUMP:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"LJM");
		}
		else if (1 == m_iCurDir)
		{
			GetAnimator()->Play(L"RJM");
		}
	}
	break;
	case PLAYER_STATE::ATTACK:
	{

	}
	break;
	case PLAYER_STATE::DEAD:
	{

	}
	break;
	}
	
	
}


