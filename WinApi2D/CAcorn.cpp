#include "framework.h"
#include "CAcorn.h"
#include "CupHead.h"
#include "CCollider.h"
#include "CAnimator.h"
CAcorn::CAcorn()
{
	m_fvDir = fVec2(0, 0);
	m_Acorn = CResourceManager::getInst()->LoadD2DImage(L"ACORN", L"texture\\Boss\\Cagney Carnation\\create\\Acorn.png");
	m_AcornFire = CResourceManager::getInst()->LoadD2DImage(L"ACORN", L"texture\\Boss\\Cagney Carnation\\create\\Acorn.png");
	SetScale(fPoint(60.f, 60.f));
	SetName(L"AArcorn");

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Arcorn", m_Acorn, fPoint(0.f, 0.f), fPoint(60.f, 60.f), fPoint(60.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"Arcornfire", m_AcornFire, fPoint(480.f, 0.f), fPoint(60.f, 60.f), fPoint(60.f, 0.f), 0.06f, 4);
}

CAcorn::~CAcorn()
{
}

CAcorn* CAcorn::Clone()
{
	return new CAcorn(*this);
}

void CAcorn::update()
{
	fPoint pos = GetPos();
	

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;



	SetPos(pos);
	if (pos.x < 0 || pos.x > WINSIZEX
		|| pos.y < 0 || pos.y > WINSIZEY) {
		DeleteObj(this);
	}

	
	update_animation();
	GetAnimator()->update();
}

void CAcorn::render()
{
	component_render();
}

void CAcorn::SetSpeed(float other)
{
	m_fSpeed = other;
}

void CAcorn::update_animation()
{
	GetAnimator()->Play(L"Arcorn");
	if (m_fSpeed > 0.f)
	{
		GetAnimator()->Play(L"Arcornfire");
	}
}

void CAcorn::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CAcorn::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CAcorn::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	fPoint pos = GetPos();
	if (pOtherObj->GetName() == L"Player")
	{
		DeleteObj(this);
	}
}
