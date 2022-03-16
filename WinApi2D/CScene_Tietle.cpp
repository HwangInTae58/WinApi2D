#include "framework.h"
#include "CGameObject.h"
#include "CScene_Tietle.h"
#include "CBackGround.h"
#include "CAnimator.h"
#include "CAnimation.h"

CScene_Tietle::CScene_Tietle()
{
}

CScene_Tietle::~CScene_Tietle()
{
}

void CScene_Tietle::update()
{
	//이곳에 스타트 버튼
	//종료버튼 만들기
	if (KeyDown(VK_RETURN))
	{
		ChangeScn(GROUP_SCENE::START); //씬 바꾸기
		Exit();
	}
}

void CScene_Tietle::Enter()
{
	//TODO : 여기 신나가면서 백그라운드가 안지워짐
	CCameraManager::getInst()->FadeIn(1.f);		//점점 밝아짐
	CBackGround* TietlebackGround = new CBackGround;
	TietlebackGround->Load(L"BackGround_Start", L"texture\\background\\Background\\title_background.png");
	TietlebackGround->SetPos(fPoint(0.f, 0.f));
	TietlebackGround->SetScale(fPoint(TietlebackGround->GetScale().x / 4, TietlebackGround->GetScale().y / 4));
	AddObject(TietlebackGround, GROUP_GAMEOBJ::TITLEBACKGROUND);


}

void CScene_Tietle::Exit()
{
	DeleteAll();
}
