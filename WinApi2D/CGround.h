#pragma once
#include "CTile.h"
class CGround : public CTile
{
private:
	int m_iX;
	int m_iY;
	int m_iIdx;			// 텍스쳐 인덱스

	GROUP_TILE m_group;

public:
	CGround();
	~CGround();

	virtual int GetIdx();
	virtual int GetX();
	virtual int GetY();
	virtual void SetGroup(GROUP_TILE group);

	virtual void OnCollision(CCollider* _pOther);			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);	// 재정의용 탈충돌 가상함수

	GROUP_TILE GetGroup();
};

