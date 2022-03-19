#include "framework.h"
#include "CGround.h"
#include "CTile.h"
#include "CCollider.h"

CGround::CGround()
{

}

CGround::~CGround()
{
}

void CGround::Start()
{
 
}



CGround* CGround::Clone()
{
    return new CGround(*this);
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{

}

void CGround::OnCollision(CCollider* _pOther)
{

}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CGameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		//pOtherObj->GetGravity()->SetGround(false);
	}
}

void CGround::update()
{
    
}
