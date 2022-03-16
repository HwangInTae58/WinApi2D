#pragma once

#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_idle;
	CD2DImage* m_hit;
	CD2DImage* m_run;
	CD2DImage* fpMissilePos;
	CD2DImage* m_shoot;
	CD2DImage* m_jump;
	CD2DImage* m_dash;
	CD2DImage* m_duck;
	float m_fVelocity = 300;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	
};

