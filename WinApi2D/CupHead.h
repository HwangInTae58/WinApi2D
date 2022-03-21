#pragma once
#include "CGameObject.h"

#define JUMP_FOCE 700
#define GRAVITY_  1500
enum class PLAYER_MOVE
{
	INTRO,
	IDLE,
	DOCK,
	RUN,
	JUMP,
	ATTACK,
	DEAD,



	SIZE,
};

class CupHead : public CGameObject
{
private:
	//벡터 사용 정리
	CD2DImage* m_Intro;
	CD2DImage* m_Idle;
	CD2DImage* m_run;
	CD2DImage* m_shoot;
	CD2DImage* m_duck;
	CD2DImage* m_jump;
	float m_fSpeed = 300;
	float m_fVelocity;

	//점프 함수
	fPoint m_fDir;
	bool JumpKeyDown = false;
	bool m_bIsLeft;	// true = Left
	bool m_bIsUP;	// true = UP
	float m_JumpPower;
	float m_fz;

public:
	CupHead();
	~CupHead();
	virtual CupHead* Clone();
	void Jump(float fDTime);
	virtual void OnCollision(CCollider* _pOther);			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);	// 재정의용 탈충돌 가상함수

	void CreateMissile();

	virtual void update();
	virtual void render();


	void update_move();
	void update_animation();


};

