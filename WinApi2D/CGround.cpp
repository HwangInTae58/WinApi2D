#include "framework.h"
#include "CGround.h"
#include "CCollider.h"

CGround::CGround()
{
	m_iIdx = 0;
	m_iX = 0;
	m_iY = 0;
	m_group = GROUP_TILE::GROUND;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
	SetName(L"Ground");
}

CGround::~CGround()
{
}

int CGround::GetIdx()
{
	return m_iIdx;
}

int CGround::GetX()
{
	return m_iX;
}

int CGround::GetY()
{
	return m_iY;
}

void CGround::SetGroup(GROUP_TILE group)
{
	m_group = group;
}

void CGround::OnCollision(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if ((pOtherObj->GetName() == L"Player" && GetCollCount() >= 1))
	{
		CTile* pTile = (CTile*)(_pOther->GetObj());
		_pOther->GetObj()->SetFloor(true);
		fPoint fObjPos = pTile->GetCollider()->GetFinalPos();
		fPoint fObjScale = pTile->GetCollider()->GetScale();

		fPoint pos = GetCollider()->GetFinalPos();
		fPoint scale = GetCollider()->GetScale();
		fPoint CupPos = GetPos();

		float fLen = abs(fObjPos.y - pos.y);
		float fValue = (fObjScale.y / 2.f + scale.y / 2.f) - fLen;
		pos = CupPos;
		pos.y -= fValue + 1.f;
		SetPos(pos);


	}
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if ((pOtherObj->GetName() == L"Player" && GetCollCount() >= 1))
	{
		CTile* pTile = (CTile*)(_pOther->GetObj());
		_pOther->GetObj()->SetFloor(true);
		fPoint fObjPos = pTile->GetCollider()->GetFinalPos();
		fPoint fObjScale = pTile->GetCollider()->GetScale();

		fPoint pos = GetCollider()->GetFinalPos();
		fPoint scale = GetCollider()->GetScale();
		fPoint CupPos = GetPos();

		float fLen = abs(fObjPos.y - pos.y);
		float fValue = (fObjScale.y / 2.f + scale.y / 2.f) - fLen;
		pos = CupPos;
		pos.y -= fValue + 1.f;
		SetPos(pos);
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
}

GROUP_TILE CGround::GetGroup()
{
	return m_group;
}
