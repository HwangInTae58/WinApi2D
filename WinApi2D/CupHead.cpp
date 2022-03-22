#include "framework.h"
#include "CupHead.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CupHead::CupHead()
{
	m_bIsLeft = false;
	m_blsFloor = false;


	//»çÁø ºÒ·¯¿À±â
	m_Intro = CResourceManager::getInst()->LoadD2DImage(L"Intro", L"texture\\Animation\\Intro\\Intro.png");
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Run\\Run.png");
	m_shoot = CResourceManager::getInst()->LoadD2DImage(L"Shoot", L"texture\\Animation\\Shoot\\Shoot.png");
	m_duck = CResourceManager::getInst()->LoadD2DImage(L"Duck", L"texture\\Animation\\Duck\\Duck.png");
	m_jump = CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\Animation\\Jump\\Jump.png");
	SetName(L"Player");
	//À§Ä¡ Å©±â ÁöÁ¤
	SetPos(fPoint(100.f,595.f));
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
	fPoint pos = GetPos();
	
	update_move();
	update_animation();

	GetAnimator()->update();
	
}

void CupHead::render()
{
	component_render();
}
void CupHead::Jump(float fDTime)
{
	fPoint pos = GetPos();
	fDTime = fDT;
	pos.y = 50.f * fDTime;
	
}

void CupHead::OnCollision(CCollider* _pOther)
{
}

void CupHead::OnCollisionEnter(CCollider* _pOther)
{
	GROUP_TILE::GROUND;
	CGameObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		fPoint Pos = GetPos();
		if (Pos.y < pOtherObj->GetPos().y)
		{
			Pos.y = pOtherObj->GetPos().y;
			PLAYER_MOVE::IDLE;
		}
		m_blsFloor = true;
	}
}

void CupHead::OnCollisionExit(CCollider* _pOther)
{
}

void CupHead::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	if (m_bIsLeft == false)
	{
		pMissile->SetDir(fVec2(1, 0));
		fpMissilePos.x += GetScale().x / 2.f;
	}
	else if (m_bIsLeft == true)
	{
		pMissile->SetDir(fVec2(-1, 0));
		fpMissilePos.x += GetScale().x / -2.f;
	}
	else if (m_bIsUP == true)
	{
		pMissile->SetDir(fVec2(0,-1));
	}
	else if (m_bIsUP == false)
	{
		pMissile->SetDir(fVec2(0, 1));
	}

	pMissile->SetName(L"Missile");
	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

	
void CupHead::update_move()
{
	fPoint pos = GetPos();
	if (m_blsFloor == false)
	{
		m_fDir.y -= 700.f * fDT;
		pos.y += -m_fDir.y * fDT;
	}
	

	if (Key(VK_LEFT))
	{
		PLAYER_MOVE::RUN;
		pos.x -= m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIsLeft = true;
	}
	else if (Key('C') || Key(VK_LEFT))
	{
		PLAYER_MOVE::IDLE;

	}

	if (Key(VK_RIGHT))
	{
		PLAYER_MOVE::RUN;
		pos.x += m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIsLeft = false;
	}
	if (Key(VK_UP))
	{
		PLAYER_MOVE::IDLE;

		m_bIsUP = true;
	}
	if (Key(VK_DOWN))
	{
		PLAYER_MOVE::DOCK;
		pos.y += m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
		m_bIsUP = false;
		
	}

	if (KeyDown('Z'))
	{

		PLAYER_MOVE::JUMP;
		JumpKeyDown = true;
		Jump(fDT);
		
	}
	if (KeyDown('X'))
	{
		CreateMissile();
	}

	SetPos(pos);
}

void CupHead::update_animation()
{
	if (m_bIsLeft == true)
	{
		if (m_fVelocity > 0)
		{
			GetAnimator()->Play(L"LRun");
			
		}
		else if (m_fVelocity == 0)
		{
			GetAnimator()->Play(L"LNone");
		
		}
		else if (m_bIsUP == true)
		{
			GetAnimator()->Play(L"LU");
		}
	}
	else if(m_bIsLeft == false)
	{
		if (m_fVelocity > 0)
		{
			GetAnimator()->Play(L"RRun");
		}
		else if(m_fVelocity == 0)
		{
			GetAnimator()->Play(L"RNone");
		}
		else if (m_bIsUP == false)
		{

			GetAnimator()->Play(L"RDU");
		}
	}
	
	

}


