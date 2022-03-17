#pragma once
#include "CGameObject.h"
class CupHead : public CGameObject
{
private:
	CD2DImage* m_Intro;
	CD2DImage* m_Idle;
	CD2DImage* m_run;
	float m_fSpeed = 300;

public:
	CupHead();
	~CupHead();
	virtual CupHead* Clone();

	virtual void update();
	virtual void render();
};

