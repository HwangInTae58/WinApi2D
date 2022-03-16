#pragma once
#include "CGameObject.h"
class CPMissile : public CGameObject
{
private:
	CD2DImage* m_missile;
	fVec2 m_fvDir;
	float m_fSpeed = 600.f;


public:
	CPMissile();
	~CPMissile();

	virtual CPMissile* Clone();

	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

