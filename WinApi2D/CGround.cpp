#include "framework.h"
#include "CGround.h"
#include "CTile.h"
#include "CCollider.h"
#include "CGravity.h"

CGround::CGround()
{
	CreateCollider();
	GetCollider()->SetScale(fPoint(GetScale()));
	
}

CGround::~CGround()
{
}

void CGround::Start()
{
	GetCollider()->SetScale(fPoint(GetScale()));
}


void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		fPoint fObjPos = _pOther->GetFinalPos();
		fPoint fObjScale = _pOther->GetScale();

		fPoint fPos = GetCollider()->GetFinalPos();
		fPoint fScale = GetCollider()->GetScale();

		float fLen = abs(fObjPos.y - fPos.y);
		float fValue = (fObjScale.y / 2.f + fScale.y / 2.f) - fLen;

		fObjPos = pOtherObj->GetPos();
		fObjPos.y -= fValue;
		pOtherObj->SetPos(fObjPos);
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		fPoint fObjPos = _pOther->GetFinalPos();
		fPoint fObjScale = _pOther->GetScale();

		fPoint fPos = GetCollider()->GetFinalPos();
		fPoint fScale = GetCollider()->GetScale();

		float fLen = abs(fObjPos.y - fPos.y);
		float fValue = (fObjScale.y / 2.f + fScale.y / 2.f) - fLen;

		fObjPos = pOtherObj->GetPos();
		fObjPos.y -= fValue;
		pOtherObj->SetPos(fObjPos);
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}
