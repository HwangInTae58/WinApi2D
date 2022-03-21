#pragma once
#include "CGameObject.h"

class CGameObject;

class CGravity : public CGameObject
{
	friend class CGameObject;

private:
	CGameObject* m_pOwner;
	bool     m_bGround;

	
public:
	CGravity();
	~CGravity();
	fPoint gravity();
	virtual CGravity* Clone();

	void SetGround(bool _b);
	virtual void update();
};

