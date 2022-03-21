#pragma once
#include "CGameObject.h"

class CGameObject;

class CGravity
{
	friend class CGameObject;

private:
	CGameObject* m_pOwner;
	bool     m_bGround;
	float G = -9.8F;    // 중력가속도(아래로 작용하므로 음수,  스크린인 경우에는 양수이어야 함)
	float t = 0.0F;      // 시작 시점부터 현재까지 누적된 시간(초)
	float C1 = 0.0F;    // 초기속도를 나타내는 상수
	float C2 = 0.0F;    // 초기위치를 나타내는 상수


public:
	CGravity();
	~CGravity();
	//fPoint gravity(fPoint _Other);

	void SetGround(bool _b);
	virtual void update();
	virtual void finalupdate();
};

