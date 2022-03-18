#pragma once
#include "CGameObject.h"
class CGround : public CGameObject
{
private:
	
public:
	CGround();
	virtual ~CGround();

	virtual void Start();
	virtual CGround* Clone();
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	virtual void update();

};

