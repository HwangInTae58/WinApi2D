#pragma once
#include "CGameObject.h"
class CMissile : public CGameObject
{
private:
	CD2DImage* m_missile;
	fVec2 m_fvDir;
	float m_fSpeed = 800.f;
	bool m_bIsLeft;

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

