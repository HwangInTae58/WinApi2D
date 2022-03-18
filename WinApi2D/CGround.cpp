#include "framework.h"
#include "CGround.h"
#include "CGravity.h"
#include "CTile.h"
#include "CCollider.h"

CGround::CGround()
{
    CreateCollider();
}

CGround::~CGround()
{
}

void CGround::Start()
{
    CreateCollider();
    GetCollider()->SetScale(fPoint(GetScale()));
}



CGround* CGround::Clone()
{
    return nullptr;
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player")
    {
        pOtherObj->GetGravity()->SetGround(true);

        fPoint vObjPos = _pOther->GetFinalPos();
        fPoint vObjScale = _pOther->GetScale();

        fPoint vPos = GetCollider()->GetFinalPos();
        fPoint vScale = GetCollider()->GetScale();


        float fLen = abs(vObjPos.y - vPos.y);
        float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

        vObjPos = pOtherObj->GetPos();
        vObjPos.y -= fValue;
        pOtherObj->SetPos(vObjPos);
    }
}

void CGround::OnCollision(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player")
    {
        pOtherObj->GetGravity()->SetGround(true);

        fPoint vObjPos = _pOther->GetFinalPos();
        fPoint vObjScale = _pOther->GetScale();

        fPoint vPos = GetCollider()->GetFinalPos();
        fPoint vScale = GetCollider()->GetScale();


        float fLen = abs(vObjPos.y - vPos.y);
        float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

        vObjPos = pOtherObj->GetPos();
        vObjPos.y -= fValue;
        pOtherObj->SetPos(vObjPos);
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

void CGround::update()
{
    
}
