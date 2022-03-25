#include "framework.h"
#include "CAcorn.h"
#include "CCollider.h"
#include "CAnimator.h"
CAcorn::CAcorn()
{
}

CAcorn::~CAcorn()
{
}

CAcorn* CAcorn::Clone()
{
	return nullptr;
}

void CAcorn::update()
{
}

void CAcorn::render()
{
}

void CAcorn::update_move()
{
}

void CAcorn::update_animation()
{
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
