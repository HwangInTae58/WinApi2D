#include "framework.h"
#include "CGravity.h"

CGravity::CGravity()
{
}

CGravity::~CGravity()
{
}

fPoint CGravity::gravity()
{

    return fPoint();
}

CGravity* CGravity::Clone()
{
    return nullptr;
}

void CGravity::SetGround(bool _b)
{
    m_bGround = _b;
}

void CGravity::finalupdate()
{
}

void CGravity::update()
{
}

void CGravity::render()
{
}
