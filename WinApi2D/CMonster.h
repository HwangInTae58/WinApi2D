#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct tMonInfo
{
	int fHP;
	int fRecogRange;
	int fAttRange;
	int fAtt;
};
enum class MON_TYPE
{
		NORMAL,
		RANGE,

		SIZE,
};
class CMonster : public CGameObject
{
private:
	CD2DImage* m_Idle;
	CD2DImage* m_Create;

	tMonInfo m_tInfo;
	AI* m_pAI;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	
	const tMonInfo& GetMonInfo();

	
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);

	virtual void OnCollisionEnter(CCollider* pOther);
};

