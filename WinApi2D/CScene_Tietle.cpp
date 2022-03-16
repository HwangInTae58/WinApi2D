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
	//�̰��� ��ŸƮ ��ư
	//�����ư �����
	if (KeyDown(VK_RETURN))
	{
		ChangeScn(GROUP_SCENE::START); //�� �ٲٱ�
		Exit();
	}
}

void CScene_Tietle::Enter()
{
	//TODO : ���� �ų����鼭 ��׶��尡 ��������
	CCameraManager::getInst()->FadeIn(1.f);		//���� �����
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
