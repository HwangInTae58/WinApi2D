#pragma once
#include "CGameObject.h"

class CMissile : public CGameObject
{
private:
	CD2DImage* m_missile;
	CD2DImage* m_midead;
	fVec2 m_fvDir;

	bool m_bDead = false;

	float m_fSpeed = 800.f;
	float fHP = 1;

	float m_Delay = 0;

public:
	CMissile();
	~CMissile();
	virtual CMissile* Clone();

	virtual void update();
	virtual void render();
	void update_move();
	void update_animation();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

