#include "framework.h"
#include "CupHead.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
CupHead::CupHead()
{
	//사진 불러오기
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation\\Idle_Aim\\Stay.png");

	SetName(L"Player");
	//위치 크기 지정
	SetPos(fPoint(100.f,550.f));
	SetScale(fPoint(70.f, 100.f));

	//충돌체
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 55.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//애니메이션 생성
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"None", m_pImg, fPoint(0.f, 0.f), fPoint(70.f, 100.f), fPoint(70.f, 0.f), 0.12f, 5);
	GetAnimator()->Play(L"None");
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

	GetAnimator()->update();
}

void CupHead::render()
{
	component_render();
}
