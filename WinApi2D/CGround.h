#pragma once
#include "CTile.h"
class CGround : public CTile
{
private:
	int m_iX;
	int m_iY;
	int m_iIdx;			// �ؽ��� �ε���

	GROUP_TILE m_group;

public:
	CGround();
	~CGround();

	virtual int GetIdx();
	virtual int GetX();
	virtual int GetY();
	virtual void SetGroup(GROUP_TILE group);

	virtual void OnCollision(CCollider* _pOther);			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther);	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther);	// �����ǿ� Ż�浹 �����Լ�

	GROUP_TILE GetGroup();
};

