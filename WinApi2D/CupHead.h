#pragma once
#include "CGameObject.h"

struct tPInfo
{
	float fHP;
};
enum class PLAYER_STATE
{
	INTRO,
	IDLE,
	DOCK,
	RUN,
	JUMP,
	ATTACK,
	EXATTACK,
	DEAD,



	SIZE,
};

class CupHead : public CGameObject
{
private:

	static CupHead* instance;

	//���� ��� ����
	CD2DImage* m_Intro;
	CD2DImage* m_Idle;
	CD2DImage* m_run;
	CD2DImage* m_shoot;
	CD2DImage* m_EXshoot;
	CD2DImage* m_duck;
	CD2DImage* m_jump;

	PLAYER_STATE m_eCurState; //ĳ���� �������
	PLAYER_STATE m_ePreState; //ĳ���� ��������

	int          m_iCurDir;	  //�������
	int          m_iPreDir;	  //��������

	float m_Gravity = 700;
	float m_fSpeed = 300;
	float m_fVelocity;  //���ӵ�
	
	bool m_Attack = false;
	bool m_EXAttack = false;

	float m_Delay = 0;
	float m_DelayTime = 0;

	bool m_isGravity;
	bool m_blsFloor;
	int m_iCollCount;
	
	//���� �Լ�
	fPoint m_fDir;
	float JumpForce =700;
	bool JumpKeyDown = false;


public:
	
	CupHead();
	~CupHead();
	virtual CupHead* Clone();

	virtual void OnCollision(CCollider* _pOther);			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther);	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther);	// �����ǿ� Ż�浹 �����Լ�

	void CreateMissile();
	void CreateEX();

	void Hit();

	virtual void update();
	virtual void render();

	void update_move();
	void update_animation();

	void RegisterPlayer();
	static CupHead* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)
};

