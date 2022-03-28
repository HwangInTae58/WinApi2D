#pragma once
#include "CGameObject.h"
class CAcorn : public CGameObject
{
private:
	CD2DImage* m_Acorn;
	CD2DImage* m_AcornFire;
	fVec2 m_fvDir;
	float m_fSpeed = 0.f;
	float fHP = 1;

	float m_Delay = 0;

public:
	CAcorn();
	~CAcorn();
	virtual CAcorn* Clone();

	virtual void update();
	virtual void render();


	void update_animation();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollision(CCollider* pOther);
};

