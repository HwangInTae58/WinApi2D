#include "framework.h"
#include "CGravity.h"

CGravity::CGravity()
{
	m_pOwner = nullptr;
	m_bGround = false;
}

CGravity::~CGravity()
{
}





void CGravity::SetGround(bool _bGround)
{
	m_bGround = _bGround;
}

void CGravity::update()
{
	// G�� �ð� t�� ���Ͽ� �����Ͽ� �ӵ��� ���ϸ� ������ ���� ( G * t^0 �� �����Ѵ�)

	float Vy = G * t + C1;     // ���л�� C1�� t=0�� ���� �ʱ�ӵ�



	// �ӵ�(Vy)�� �ð� t�� ���Ͽ� �����Ͽ� �Ÿ��� ���ϸ� ������ ����

	float y = 0.5 * G * (t * t) + (C1 * t) + C2;    // ���л�� C2�� �ʱ� ��ġ(�ʱ� y��)



	// ���� �Ŀ��� 0.5 ��ſ� 1/2�� ����ϸ� �ȵȴ�. �������� �������ϸ� ������ ������ ����	

	// �����ð�(1������)�� 100������ �ӵ��� �ٴ�(0,0)���� ���� ���� �߻�� ��ź�� 

	// �ٴڿ� �����ϱ� ���� ��ġ(��ǥ)�� ȭ�鿡 ǥ���غ��� ������ ��ġ�� Ȯ���Ѵ�
	C1 = 100;	 //�ʱ�ӵ� 
	C2 = 0;	 //�ʱ���ġ
	do {
		y = 0.5 * G * (t * t) + (C1 * t) + C2;     // 0.5 ��ſ� 1/2�� ����ϸ� �ȵ�
		t++;
	} while (y >= 0);
}

void CGravity::finalupdate()
{
	//��ü�� ���� �پ����� Ȯ��
	
}


