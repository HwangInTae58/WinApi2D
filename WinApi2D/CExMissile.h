#pragma once
#include "CGameObject.h"

class CExMissile : public CGameObject
{
private:
	CD2DImage* m_ExMissile;
	fVec2 m_fvDir;
	float m_fSpeed = 800.f;

public:
	CExMissile();
	virtual ~CExMissile();

	virtual CExMissile* Clone();

	virtual void update();
	virtual void render();
	void update_move();
	void update_animation();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

