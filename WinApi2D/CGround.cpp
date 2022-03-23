#include "framework.h"
#include "CGround.h"

CGround::CGround()
{
	SetGroup(GROUP_TILE::GROUND);
	CreateCollider();
	SetName(L"Ground");
}

CGround::~CGround()
{
}

int CGround::GetIdx()
{
	return m_iIdx;
}

int CGround::GetX()
{
	return m_iX;
}

int CGround::GetY()
{
	return m_iY;
}

void CGround::SetGroup(GROUP_TILE group)
{
	m_group = group;
}

GROUP_TILE CGround::GetGroup()
{
	return m_group;
}
