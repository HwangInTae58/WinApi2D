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
	m_ePreState = PLAYER_STATE::INTRO;
	m_iCurDir = 1;
	m_iPreDir = 1;
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
	SetName(L"Player");
	//위치 크기 지정
	SetPos(fPoint(100.f,595.f));
	SetScale(fPoint(70.f, 100.f));
	
	//충돌체
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 65.f));
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
	if (m_Delay >= -4.f) {
		if (m_Delay <= 0) {
			m_Attack = false;
		}
		m_Delay -= fDT;
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
	fPoint pos = GetPos();
	if (_pOther->GetObj()->GetName() == L"Tile" && m_iCollCount > 0 )
	{
		fPoint otherPos = _pOther->GetFinalPos();
		pos.y -= otherPos.y + pos.y;
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
	}
}

void CupHead::OnCollisionEnter(CCollider* _pOther)
{
	m_iCollCount++;
	fPoint vPos = GetPos();
	if (_pOther->GetObj()->GetName() == L"Tile")
	{	
		m_isGravity = false;
		m_Gravity = 0.f;
		m_blsFloor = true;
		if (vPos.y < _pOther->GetFinalPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		
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
	else if (m_iCurDir == 2)
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

void CupHead::Hit()
{
}

void CupHead::update_move()
{
	fPoint pos = GetPos();
	m_Attack = false;
	m_fVelocity = 0.f;
	//딜레이
	
	//중력
	if(m_blsFloor == true){
	JumpKeyDown = false;
	}
	if (m_isGravity == true)
	{
		m_fDir.y -= m_Gravity * fDT;
		pos.y += -m_fDir.y   * fDT;
	}

	if (Key(VK_LEFT))
	{
		m_iCurDir = 2;
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
		
		pos.x -= m_fSpeed * fDT;
		m_fVelocity = m_fSpeed;
	}
	if (Key(VK_RIGHT))
	{
		m_iCurDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
		
			pos.x += m_fSpeed * fDT;
			m_fVelocity = m_fSpeed;
	}
	if (Key(VK_UP))
	{
	
	}
	if (Key(VK_DOWN))
	{
		m_eCurState = PLAYER_STATE::DOCK;
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
	if (Key('X') && m_Delay <= 0)
	{
		
		m_Attack = true;
		m_Delay = 0.15f;
		m_eCurState = PLAYER_STATE::ATTACK;
		GetAnimator()->FindAnimation(L"RSS")->SetFrame(0);
		GetAnimator()->FindAnimation(L"LSS")->SetFrame(0);
		CreateMissile();
	}
	if (KeyDown('V'))
	{
		//TODO : 나오는 속도 조절, 몬스터를 몇번 맞추었을때 쓸 수 있게 바꿔야함
		m_EXAttack = true;
		
		m_eCurState = PLAYER_STATE::EXATTACK;
		GetAnimator()->FindAnimation(L"RESS")->SetFrame(0);
		GetAnimator()->FindAnimation(L"LESS")->SetFrame(0);
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
		if (2 == m_iCurDir && m_blsFloor )
		{
			GetAnimator()->Play(L"LNone");
			
		}
		if (1 == m_iCurDir && m_blsFloor)
		{
			GetAnimator()->Play(L"RNone");
		}
		
		
	}
	break;
	case PLAYER_STATE::DOCK:
	{
		if (2 == m_iCurDir && m_blsFloor && m_fVelocity <= 0 && !JumpKeyDown)
		{
			GetAnimator()->Play(L"LDU");
		}
		if (1 == m_iCurDir && m_blsFloor && m_fVelocity <= 0 && !JumpKeyDown)
		{
			GetAnimator()->Play(L"RDU");
		}
	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (2 == m_iCurDir && m_blsFloor && m_fVelocity > 0 && !JumpKeyDown)
		{
			if (m_Attack) {
				GetAnimator()->Play(L"LSRun"); 
			}
			GetAnimator()->Play(L"LRun");
		}
		
		if (1 == m_iCurDir && m_blsFloor && m_fVelocity > 0 && !JumpKeyDown)
		{
			if (m_Attack) {
				GetAnimator()->Play(L"RSRun");
			}
			GetAnimator()->Play(L"RRun");
		}
		break;
	}
	case PLAYER_STATE::JUMP:
	{
		if (2 == m_iCurDir  && JumpKeyDown)
		{
			GetAnimator()->Play(L"LJM");
			if (1 == m_iCurDir && JumpKeyDown && !m_blsFloor)
			{
				// TODO : 여기 점프중 방향키 바뀔때 이미지 바꾸기 
				GetAnimator()->Play(L"RJM");
			}
			if (m_blsFloor) {
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}
		if (1 == m_iCurDir  && JumpKeyDown)
		{
			GetAnimator()->Play(L"RJM");
			if (2 == m_iCurDir && JumpKeyDown && !m_blsFloor)
			{
				GetAnimator()->Play(L"LJM");
			}
			if (m_blsFloor) {
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}
		
	}
	break;
	case PLAYER_STATE::ATTACK:
	{
		if (2 == m_iCurDir && m_blsFloor && m_Attack)
		{
			GetAnimator()->Play(L"LSS");
		}
		else if (1 == m_iCurDir && m_blsFloor && m_Attack)
		{
		
			GetAnimator()->Play(L"RSS");
		}
	}
	break;
	case PLAYER_STATE::EXATTACK:
	{
		if (2 == m_iCurDir && m_blsFloor && m_EXAttack)
		{
			GetAnimator()->Play(L"LESS");
		}
		else if (1 == m_iCurDir && m_blsFloor && m_EXAttack)
		{
			GetAnimator()->Play(L"RESS");
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


