#include "framework.h"
#include "CPMissile.h"

CPMissile::CPMissile()
{
}

CPMissile::~CPMissile()
{
}

CPMissile* CPMissile::Clone()
{
	return nullptr;
}

void CPMissile::update()
{
}

void CPMissile::render()
{
}

void CPMissile::SetDir(fVec2 vec)
{
}

void CPMissile::SetDir(float theta)
{
}

void CPMissile::OnCollisionEnter(CCollider* pOther)
{
}
