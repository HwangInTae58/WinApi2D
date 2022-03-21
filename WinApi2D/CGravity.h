#pragma once
#include "CGameObject.h"

class CGameObject;

class CGravity
{
	friend class CGameObject;

private:
	CGameObject* m_pOwner;
	bool     m_bGround;
	float G = -9.8F;    // �߷°��ӵ�(�Ʒ��� �ۿ��ϹǷ� ����,  ��ũ���� ��쿡�� ����̾�� ��)
	float t = 0.0F;      // ���� �������� ������� ������ �ð�(��)
	float C1 = 0.0F;    // �ʱ�ӵ��� ��Ÿ���� ���
	float C2 = 0.0F;    // �ʱ���ġ�� ��Ÿ���� ���


public:
	CGravity();
	~CGravity();
	//fPoint gravity(fPoint _Other);

	void SetGround(bool _b);
	virtual void update();
	virtual void finalupdate();
};

