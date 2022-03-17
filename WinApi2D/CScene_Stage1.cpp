#include "framework.h"
#include "CScene_Stage1.h"
#include "CGameObject.h"
#include "CupHead.h"
#include "CMap.h"
#include "CBackGround.h"
CScene_Stage1::CScene_Stage1()
{
}

CScene_Stage1::~CScene_Stage1()
{
}

void CScene_Stage1::update()
{
	CScene::update();
}

void CScene_Stage1::Enter()
{
	// Ÿ�� �ε�
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Stage1";
	LoadTile(path);

	// Player �߰�
	CGameObject* pPlayer = new CupHead;
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	//���߰�
	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\Stage1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	//��׶��� �߰�
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\background.png");
	backGround->SetPos(fPoint(-100.f, -500.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);
}

void CScene_Stage1::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
