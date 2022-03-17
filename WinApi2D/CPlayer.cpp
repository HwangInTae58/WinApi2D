#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_idle = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation\\Player\\Idle_Aim\\Stay.png");
	m_run = CResourceManager::getInst()->LoadD2DImage(L"Run", L"texture\\Animation\\Player\\Run\\Run.png");
	m_hit = CResourceManager::getInst()->LoadD2DImage(L"Hit", L"texture\\Animation\\Player\\Hit\\Hit.png");
	m_shoot = CResourceManager::getInst()->LoadD2DImage(L"Shoot", L"texture\\Animation\\Player\\Shoot\\Shoot.png");
	m_jump = CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\Animation\\Player\\Jump\\Jump.png");

	SetName(L"Player");
	SetScale(fPoint(0.f, 0.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(45.f, 70.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone", m_idle, fPoint(0.f, 0.f),	fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"RightNone", m_idle, fPoint(0.f, 100.f),	fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"UPNone", m_idle, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DownNone", m_idle, fPoint(0.f, 300.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"LeftMove", m_run, fPoint(0.f, 0.f),	fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 16);
	GetAnimator()->CreateAnimation(L"RightMove", m_run, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 16);
	GetAnimator()->CreateAnimation(L"RightUpMove", m_run, fPoint(0.f, 200.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 16);
	GetAnimator()->CreateAnimation(L"LeftHit", m_hit, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"RightHit", m_hit, fPoint(0.f, 100.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"StrShoot", m_shoot, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"UpJump", m_jump, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.1f, 8);
	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;	//애니메이션 움직임 보강
	pAni = GetAnimator()->FindAnimation(L"UpJump");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, 20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, 0.f);
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightMove");
		
	}		
	if (Key(VK_RIGHT) && Key(VK_UP))
	{
		GetAnimator()->Play(L"RightUpMove");
	}

	if (Key(VK_UP))	   
	{				   
		pos.y -= m_fVelocity * fDT;
		GetAnimator()->Play(L"UPNone");
	}				   
	if (Key(VK_DOWN))  
	{				   
		pos.y += m_fVelocity * fDT;
		GetAnimator()->Play(L"DownNone");
	}

	SetPos(pos);

	if (KeyDown('Z'))
	{
		CreateMissile();
		
		GetAnimator()->Play(L"StrShoot");
		
	}
	if (KeyDown('X'))
	{
		//중력을 이용한 점프 적용
		pos.y -= 20.f * fDT;
		GetAnimator()->Play(L"UpJump");

	}
	if (Key(VK_LSHIFT))
	{
		GetAnimator()->Play(L"RightHit");
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::CreateMissile()
{
 	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;  //missile 생성
	pMissile->SetPos(fpMissilePos);		//위치
	pMissile->SetDir(fVec2(1, 0));		//날라가는 방향
	
	component_render();

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}
