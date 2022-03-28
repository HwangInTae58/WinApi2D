#include "framework.h"
#include "CupHead.h"
#include "CMissile.h"
#include "CExMissile.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"
#include "CAnimation.h"

CupHead* CupHead::instance = nullptr;

CupHead::CupHead()
{
	m_eCurState = PLAYER_STATE::IDLE;
	m_ePreState = PLAYER_STATE::IDLE;
	m_iCurDir = true;
	m_iPreDir = true;
	m_blsFloor = GetFloor();
	m_iCollCount = 0;
	m_fVelocity = 0;
	m_isGravity = GetGravity();
	m_isGravity = true;
	//사진 불러오기
	m_Intro = CResourceManager::getInst()->LoadD2DImage(L"Intro", L"texture\\Animation\\Intro\\Intro.png");
	m_Idle = CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Run\\Run.png");
	m_shoot = CResourceManager::getInst()->LoadD2DImage(L"Shoot", L"texture\\Animation\\Shoot\\Shoot.png");
	m_EXshoot = CResourceManager::getInst()->LoadD2DImage(L"EXShoot", L"texture\\Animation\\Special Attck\\Ground\\EXatc.png");
	m_duck = CResourceManager::getInst()->LoadD2DImage(L"Duck", L"texture\\Animation\\Duck\\Duck.png");
	m_jump = CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\Animation\\Jump\\Jump.png");
	m_HIT = CResourceManager::getInst()->LoadD2DImage(L"Hit", L"texture\\Animation\\Hit\\Hit.png");
	SetName(L"Player");
	//위치 크기 지정
	SetPos(fPoint(100.f,580.f));
	SetScale(fPoint(80.f, 120.f));
	
	//충돌체
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 75.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//애니메이션 생성
	CreateAnimator();
	//인트로
	//GetAnimator()->CreateAnimation(L"intro", m_Intro, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 28);
	//가만히
	GetAnimator()->CreateAnimation(L"RNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.09f, 5, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LNone", m_Idle, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.09f, 5, true/*좌우 반전*/);
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
	//엎드리기
	GetAnimator()->CreateAnimation(L"RDU", m_duck, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.07f, 13, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LDU", m_duck, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.07f, 13, true/*좌우 반전*/);
	//달리기
	GetAnimator()->CreateAnimation(L"LRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RRun", m_run, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LSRun", m_run, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RSRun", m_run, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 16, false/*좌우 반전*/);
	//HIT
	GetAnimator()->CreateAnimation(L"HIT", m_HIT, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.07f, 6, false/*좌우 반전*/);
	//사격
	GetAnimator()->CreateAnimation(L"RSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LSS", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LUS", m_shoot, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LDS", m_shoot, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LDUS", m_shoot, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"RDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LDDS", m_shoot, fPoint(0.f, 400.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 3, true/*좌우 반전*/);
	//EX
	GetAnimator()->CreateAnimation(L"RESS", m_EXshoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 15, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LESS", m_EXshoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 15, true/*좌우 반전*/);
	//점프
	GetAnimator()->CreateAnimation(L"RJM", m_jump, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.05f, 8, false/*좌우 반전*/);
	GetAnimator()->CreateAnimation(L"LJM", m_jump, fPoint(0.f, 0.f), fPoint(70.f, 60.f), fPoint(70.f, 0.f), 0.05f, 8, true/*좌우 반전*/);

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
	if (m_Hit)
	{
		m_eCurState = PLAYER_STATE::HIT;
	}

	if (m_Attack)
	{
		if (m_DelayTime >= 0.23f) {
			m_eCurState = PLAYER_STATE::IDLE;
			m_Attack = false;
			m_DelayTime = 0.f;
		}
		m_DelayTime += fDT;
	}
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
	fPoint vPos = GetPos();
	if (_pOther->GetObj()->GetName() == L"Tile" && m_iCollCount > 0)
	{
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
		if (vPos.y < _pOther->GetFinalPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
	SetPos(vPos);
}

void CupHead::OnCollisionEnter(CCollider* _pOther)
{
	m_iCollCount++;
	fPoint Pos = GetPos();
	if (_pOther->GetObj()->GetName() == L"Tile")
	{	
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
		if (Pos.y < _pOther->GetFinalPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
	if (_pOther->GetObj()->GetName() == L"Monster")
	{
		m_fDir.x = 3000.f;
		Pos.x -= m_fDir.x * fDT;
	}
	SetPos(Pos);
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
	if (m_iCurDir == true)
	{
		pMissile->SetDir(fVec2(1, 0));
		fpMissilePos.x += GetScale().x / 2.f;
	}
	else if (m_iCurDir == false)
	{
		pMissile->SetDir(fVec2(-1, 0));
		fpMissilePos.x += GetScale().x / -2.f;
	}
	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

void CupHead::CreateEX()
{
	fPoint fpEXMissilePos = GetPos();
	CExMissile* pEXMissile = new CExMissile;
	pEXMissile->SetPos(fpEXMissilePos);
	if (m_iCurDir == 1)
	{
		pEXMissile->SetDir(fVec2(1, 0));
		fpEXMissilePos.x += GetScale().x / 2.f;

	}
	else if (m_iCurDir == 2)
	{
		pEXMissile->SetDir(fVec2(-1, 0));
		fpEXMissilePos.x += GetScale().x / -2.f;
	}
	pEXMissile->SetName(L"EX");
	CreateObj(pEXMissile, GROUP_GAMEOBJ::EXMISSILE_PLAYER);
}



void CupHead::update_move()
{
	fPoint pos = GetPos();
	
	
	m_Hit = false;
	m_fVelocity = 0.f;
	//딜레이
	
	//중력
	if(m_blsFloor == true){
	JumpKeyDown = false;
	}
	if (!m_blsFloor)
	{
		m_fDir.y -= m_Gravity * fDT;
		pos.y += -m_fDir.y   * fDT;
	}



	if (Key(VK_LEFT))
	{
		m_iCurDir = false;
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
		
		pos.x -= m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
	}
	if (Key(VK_RIGHT))
	{
		m_iCurDir = true;
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
			pos.x += m_fSpeed * fDT;
			m_fVelocity = m_fSpeed;
	}
	if (KeyDown('Z'))
	{
		if(!JumpKeyDown){
		m_eCurState = PLAYER_STATE::JUMP;
		JumpKeyDown = true;
		JumpForce = 450.f;
		m_fDir.y = JumpForce;
		pos.y -= m_fDir.y * fDT;
		}
	}
	if (Key('X') && !m_Attack)
	{
		m_eCurState = PLAYER_STATE::ATTACK;
		m_Attack = true;
		
		CreateMissile();
	}
	if (KeyDown('V'))
	{
		//TODO : 나오는 속도 조절, 몬스터를 몇번 맞추었을때 쓸 수 있게 바꿔야함
		m_EXAttack = true;
		m_eCurState = PLAYER_STATE::EXATTACK;
			//CreateEX();
	}
	if (0.f == m_fVelocity && PLAYER_STATE::JUMP != m_eCurState && PLAYER_STATE::ATTACK != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	SetPos(pos);
}

void CupHead::update_animation()
{
	switch (m_eCurState)
	{
	case PLAYER_STATE::HIT:
	{
		if (m_Hit)
		{
			GetAnimator()->Play(L"HIT");
		}
	}
	break;
	case PLAYER_STATE::IDLE:
	{
		if (false == m_iCurDir && m_blsFloor && !m_Attack)
		{
			GetAnimator()->Play(L"LNone");
		}
		if (true == m_iCurDir && m_blsFloor && !m_Attack)
		{
			GetAnimator()->Play(L"RNone");
		}
	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (false == m_iCurDir && m_blsFloor && m_fVelocity > 0)
		{
			GetAnimator()->Play(L"LRun");
		}

		if (true == m_iCurDir && m_blsFloor && m_fVelocity > 0)
		{
			GetAnimator()->Play(L"RRun");
		}
		break;
	}
	case PLAYER_STATE::JUMP:
	{
		if (false == m_iCurDir && JumpKeyDown)
		{
			GetAnimator()->Play(L"LJM");
			if (m_blsFloor) {
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}
		else if (true == m_iCurDir && JumpKeyDown)
		{
			GetAnimator()->Play(L"RJM");
			if (m_blsFloor) {
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}

	}
	break;
	case PLAYER_STATE::ATTACK:
	{
		if (false == m_iCurDir && m_blsFloor)
		{
			GetAnimator()->Play(L"LSS");
		}
		else if (true == m_iCurDir && m_blsFloor)
		{
			GetAnimator()->Play(L"RSS");
		}
	}
	break;
	case PLAYER_STATE::DEAD:
	{

	}
	break;
	}
}
	


void CupHead::RegisterPlayer()
{
	instance = this;
}

CupHead* CupHead::GetPlayer()
{
	return instance;
}


