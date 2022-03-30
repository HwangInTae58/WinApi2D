#pragma once
#include "CScene.h"
class CDead : public CScene
{
public:
	CDead();
	virtual ~CDead();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

