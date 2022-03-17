#include "framework.h"
#include "CupHead.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
CupHead::CupHead()
{
	//���� �ҷ�����
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation\\Idle_Aim\\Stay.png");

	SetName(L"Player");
	//��ġ ũ�� ����
	SetPos(fPoint(100.f,550.f));
	SetScale(fPoint(70.f, 100.f));

	//�浹ü
	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 55.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//�ִϸ��̼� ����
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
