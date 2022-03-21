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
	return new CGravity(*this);
}

void CGravity::SetGround(bool _b)
{
}

void CGravity::update()
{
	fPoint pos = GetPos();

}


