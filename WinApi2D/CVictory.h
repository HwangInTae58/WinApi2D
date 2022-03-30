#pragma once
#include "CScene.h"

class CAnimator;
class CGameObject;

class CVictory : public CScene
{
	friend class CGameObject;
	friend class CAnimator;

private:
	CD2DImage* m_Victory;
	CAnimator* m_Ani;
	CGameObject* m_Obj;

public:


	CVictory();
	virtual ~CVictory();

	virtual void update();
	virtual void render();

	virtual void Enter();

	virtual void Exit();
};

