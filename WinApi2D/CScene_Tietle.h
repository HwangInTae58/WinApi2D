#pragma once
#include "CScene.h"

class CScene_Tietle : public CScene
{
private:
	CD2DImage* m_tietle;

public:
	CScene_Tietle();
	virtual ~CScene_Tietle();


	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

