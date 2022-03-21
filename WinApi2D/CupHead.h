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
	CD2DImage* m_shoot;
	float m_fSpeed = 300;
	float m_fForce;

	int m_bIs;	// 1 Left, 2Right , 3 Up, 4 Down
	float m_fVelocity;

public:
	CupHead();
	~CupHead();
	virtual CupHead* Clone();
	void Jump();
	virtual void OnCollision(CCollider* _pOther);

	void CreateMissile();
	void CreateGravity();

	virtual void update();
	virtual void render();


	void update_move();
	void update_animation();


};

