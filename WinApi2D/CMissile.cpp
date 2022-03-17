#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	SetScale(fPoint(25.f, 25.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	//TODO : 업데이트에 1프레임마다 바뀌게 할려고 했는데 뭔 이상한 버그걸림
	fPoint pos = GetPos();

	pos.x += m_fVelocity * m_fvDir.x * fDT;
	pos.y += m_fVelocity * m_fvDir.y * fDT;

	SetPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX*2.f
		|| pos.y < 0 || pos.y > WINSIZEY*2.f)
		DeleteObj(this);
}

void CMissile::render()
{
	
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	m_missile = CResourceManager::getInst()->LoadD2DImage(L"Missile", L"texture\\Animation\\Missile\\missile\\missile.png");
	CreateAnimator();
	//TODO : 뭐야 미사일 애니메이션 주세요,,,,,
	GetAnimator()->CreateAnimation(L"missile", m_missile, fPoint(0.f, 0.f), fPoint(100.f, 30.f), fPoint(100.f, 0.f), 0.1f, 8);
	GetAnimator()->Play(L"missile");
	component_render();
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
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
