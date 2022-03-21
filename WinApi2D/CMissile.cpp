#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimator.h"

CMissile::CMissile()
{
	
	m_fvDir = fVec2(0, 0);
	m_missile = CResourceManager::getInst()->LoadD2DImage(L"Missile", L"texture\\Animation\\Missile\\missile\\missile.png");
	SetScale(fPoint(60.f, 40.f));
	SetName(L"missile");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));


	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Rmissile1", m_missile, fPoint(0.f, 0.f), fPoint(100.f, 30.f), fPoint(100.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"Lmissile1", m_missile, fPoint(0.f, 0.f), fPoint(100.f, 30.f), fPoint(100.f, 0.f), 0.07f, 8, true);

	
}

CMissile::~CMissile()
{
}

CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

void CMissile::update()
{
	
	fPoint pos = GetPos();
	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX * 2
		|| pos.y < 0 || pos.y > WINSIZEY * 2)

	update_move();
	update_animation();
	GetAnimator()->update();

}

void CMissile::render()
{
	component_render();
}

void CMissile::update_move()
{

}

void CMissile::update_animation()
{
	if (m_bIsLeft == false)
	{
		GetAnimator()->Play(L"Rmissile1");
	}
	else
	{
		GetAnimator()->Play(L"Lmissile1");
	}
}



void CMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CMissile::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::OnCollisionEnter(CCollider* pOther)
{
}
