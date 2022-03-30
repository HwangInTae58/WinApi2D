#include "framework.h"
#include "CDead.h"

CDead::CDead()
{
}

CDead::~CDead()
{
}

void CDead::update()
{
	CScene::update();
}

void CDead::Enter()
{
	
}

void CDead::Exit()
{
	DeleteAll();
}
