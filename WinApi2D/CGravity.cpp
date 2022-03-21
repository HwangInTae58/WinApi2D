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
	// G를 시간 t에 대하여 적분하여 속도를 구하면 다음과 같다 ( G * t^0 를 적분한다)

	float Vy = G * t + C1;     // 적분상수 C1는 t=0일 때의 초기속도



	// 속도(Vy)를 시간 t에 대하여 적분하여 거리를 구하면 다음과 같다

	float y = 0.5 * G * (t * t) + (C1 * t) + C2;    // 적분상수 C2는 초기 위치(초기 y값)



	// 위의 식에서 0.5 대신에 1/2을 사용하면 안된다. 정수끼리 나눗셈하면 정수가 나오기 때문	

	// 단위시간(1프레임)당 100미터의 속도로 바닥(0,0)에서 위를 향해 발사된 포탄이 

	// 바닥에 도달하기 까지 위치(좌표)를 화면에 표시해보고 정점의 위치를 확인한다
	C1 = 100;	 //초기속도 
	C2 = 0;	 //초기위치
	do {
		y = 0.5 * G * (t * t) + (C1 * t) + C2;     // 0.5 대신에 1/2을 사용하면 안됨
		t++;
	} while (y >= 0);
}

void CGravity::finalupdate()
{
	//물체가 땅에 붙었는지 확인
	
}


