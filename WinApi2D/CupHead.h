#pragma once
#include "CGameObject.h"


enum class PLAYER_STATE
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

	PLAYER_STATE m_eCurState; //캐릭터 현재상태
	PLAYER_STATE m_ePreState; //캐릭터 이전상태

	int          m_iCurDir;	  //현재방향
	int          m_iPreDir;	  //이전방향

	float m_Gravity = 700;
	float m_fSpeed = 300;
	float m_fVelocity;  //가속도
	
	bool m_isGravity;
	bool m_blsFloor;
	int m_iCollCount;
	
	//점프 함수
	fPoint m_fDir;
	float JumpForce =700;
	bool JumpKeyDown = false;


public:
	CupHead();
	~CupHead();
	virtual CupHead* Clone();

	virtual void OnCollision(CCollider* _pOther);			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);	// 재정의용 탈충돌 가상함수

	void CreateMissile();


	virtual void update();
	virtual void render();

	void update_move();
	void update_animation();


};

