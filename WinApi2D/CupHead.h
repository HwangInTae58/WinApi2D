#pragma once
#include "CGameObject.h"

enum class PLAYER_MOVE
{
	INTRO,
	IDLE,
	RUN,
	JUMP,
	ATTACK,
	DEAD,



	SIZE,
};


class CRigidBody;
class CupHead : public CGameObject
{
private:
	CRigidBody* pRigid;
	CD2DImage* m_Intro;
	CD2DImage* m_Idle;
	CD2DImage* m_run;
	float m_fSpeed = 300;
	bool m_bIsLeft;
	float m_fVelocity;

public:
	CupHead();
	~CupHead();
	virtual CupHead* Clone();

	virtual void update();
	virtual void render();
	void update_move();
	void update_animation();
	void update_gravity();
};

