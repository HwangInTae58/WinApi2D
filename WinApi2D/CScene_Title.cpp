#include "framework.h"
#include "CScene_Title.h"
#include "CImageObject.h"
#include "CImageButton.h"
#include "CAnimator.h"
#include "CAnimation.h"

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void ClickStartButton(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::STAGE_01);
}

void ClickExitButton(DWORD_PTR, DWORD_PTR)
{
	PostQuitMessage(0);
}

void ClickToolButton(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TOOL);
}

void CScene_Title::Enter()
{
	// TODO :
	// 1. 배경 출력
	CImageObject* backgroundObject = new CImageObject;
	backgroundObject->Load(L"BackImage", L"texture\\title_background.png");
	backgroundObject->SetPos(fPoint(0.f, 0.f));
	backgroundObject->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(backgroundObject, GROUP_GAMEOBJ::BACKGROUND);

	// 2. 로고 출력용 오브젝트 제작
	/*m_titlelogo = CResourceManager::getInst()->LoadD2DImage(L"Title", L"texture\\Title.png");
	CAnimator* titleani = new CAnimator;
	titleani->CreateAnimation(L"TitleLogo", m_titlelogo, fPoint(0.f, 0.f), fPoint(1090.f, 610.f), fPoint(1090.f, 0.f), 0.1f, 34);
	titleani->Play(L"TitleLogo");*/


	// 3. 시작 버튼
	CImageButton* startButton = new CImageButton;
	startButton->Load(L"Button", L"texture\\title_button.png");
	startButton->SetText(L"시작 하기");
	startButton->SetPos(fPoint(WINSIZEX / 2.f - 100.f, 450.f));
	startButton->SetScale(fPoint(200.f, 50.f));
	startButton->SetClickedCallBack(ClickStartButton, 0, 0);
	AddObject(startButton, GROUP_GAMEOBJ::UI);

	// 4. Tool 버튼
	CImageButton* toolButton = new CImageButton;
	toolButton->Load(L"Button", L"texture\\title_button.png");
	toolButton->SetText(L"TOOL");
	toolButton->SetPos(fPoint(WINSIZEX / 2.f - 100.f, 550.f));
	toolButton->SetScale(fPoint(200.f, 50.f));
	toolButton->SetClickedCallBack(ClickToolButton, 0, 0);
	AddObject(toolButton, GROUP_GAMEOBJ::UI);

	// 4. 종료 버튼
	CImageButton* exitButton = new CImageButton;
	exitButton->Load(L"Button", L"texture\\title_button.png");
	exitButton->SetText(L"종료");
	exitButton->SetPos(fPoint(WINSIZEX / 2.f - 100.f, 650.f));
	exitButton->SetScale(fPoint(200.f, 50.f));
	exitButton->SetClickedCallBack(ClickExitButton, 0, 0);
	AddObject(exitButton, GROUP_GAMEOBJ::UI);

	
}

void CScene_Title::Exit()
{
}
