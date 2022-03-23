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

	GROUP_TILE GetGroup();
};

