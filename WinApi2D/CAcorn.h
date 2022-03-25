#pragma once
#include "CGameObject.h"
class CAcorn : public CGameObject
{
private:
	CD2DImage* m_Acorn;
	fVec2 m_fvDir;
	float m_fSpeed = 750.f;
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

	void OnCollisionEnter(CCollider* pOther);
};

