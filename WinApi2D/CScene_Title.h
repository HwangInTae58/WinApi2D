#pragma once
#include "CScene.h"


class CScene_Title : public CScene
{
private:
	CD2DImage* m_titlelogo;
	
public:
	CScene_Title();
	virtual ~CScene_Title();



	virtual void Enter();	// �ش� ���� ���Խ� ȣ��
	virtual void Exit();	// �ش� ���� Ż��� ȣ��
};

