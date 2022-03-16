#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL); //�� �ٲٱ�
		
	}

	if (KeyDown('U'))
	{
		CSoundManager::getInst()->AddSound(L"bgm", L"sound\\drumloop.wav", true);
		CSoundManager::getInst()->Play(L"bgm");
	}

	if (KeyDown('I'))
	{
		CSoundManager::getInst()->Stop(L"bgm");
	}
}

void CScene_Start::Enter()
{
	// Ÿ�� �ε�
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\test2";
	LoadTile(path);

	// Player �߰�
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(500, 500));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	// Monster �߰�
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(1100, 350));
	pMonster->SetCenterPos(pMonster->GetPos());
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\Staegy1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\background_start.png");
	backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);

	// Camera Look ����
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
	
	
	CCameraManager::getInst()->FadeIn(1.f);		//���� �����
}

void CScene_Start::Exit()
{
	
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
