#include "framework.h"
#include "CAcorn.h"
#include "CCollider.h"
#include "CAnimator.h"
CAcorn::CAcorn()
{
	m_fvDir = fVec2(0, 0);
	m_Acorn = CResourceManager::getInst()->LoadD2DImage(L"ACORN", L"texture\\Boss\\Cagney Carnation\\create\\Acorn.png");

	SetScale(fPoint(80.f, 80.f));
	SetName(L"arcorn");

	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 60.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Arcorn", m_Acorn, fPoint(0.f, 0.f), fPoint(60.f, 60.f), fPoint(60.f, 0.f), 0.07f, 12);
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

void CAcorn::update_animation()
{
	GetAnimator()->Play(L"Arcorn");
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

void CAcorn::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	fPoint pos = GetPos();
	if (pOtherObj->GetName() == L"Player")
	{
		fHP -= 1;
		SetDir(fPoint(0, 0));
		SetPos(pos);

		DeleteObj(this);
	}
}
