#include "framework.h"
#include "CExMissile.h"
#include "CCollider.h"
#include "CAnimator.h"

CExMissile::CExMissile()
{
	m_fvDir = fVec2(0, 0);

	m_ExMissile = CResourceManager::getInst()->LoadD2DImage(L"EXMissile", L"texture\\Animation\\Missile\\EX\\EX.png");
	SetScale(fPoint(150.f, 100.f));
	SetName(L"Ex");

	CreateCollider();
	GetCollider()->SetScale(fPoint(100.f, 70.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"REX", m_ExMissile, fPoint(0.f, 0.f), fPoint(180.f, 100.f), fPoint(180.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"LEX", m_ExMissile, fPoint(0.f, 0.f), fPoint(180.f, 100.f), fPoint(180.f, 0.f), 0.07f, 8, true);
}

CExMissile::~CExMissile()
{
}

CExMissile* CExMissile::Clone()
{
	return new CExMissile(*this);
}

void CExMissile::update()
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

void CExMissile::render()
{
	component_render();
}

void CExMissile::update_move()
{
	
}

void CExMissile::update_animation()
{
	if (m_fvDir.x == 1)
	{
		GetAnimator()->Play(L"REX");
	}
	else
	{
		GetAnimator()->Play(L"LEX");
	}
}

void CExMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CExMissile::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CExMissile::OnCollisionEnter(CCollider* pOther)
{
}
