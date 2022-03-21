#pragma once
#include "CGameObject.h"
#include "CTile.h"
class CGround : public CTile
{
private:
	CTile* m_Ground;
public:
	CGround();
	virtual ~CGround();

	virtual void Start();
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


};

