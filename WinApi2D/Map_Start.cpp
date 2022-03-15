#include "framework.h"
#include "Map_Start.h"
#include "CD2DImage.h"

Map_Start::Map_Start()
{
    pimg = CResourceManager::getInst()->LoadD2DImage(L"Stage1", L"texture\\map\\Stage1.png");
    SetPos(fPoint(0, 0));
    SetScale(fPoint(pimg->GetWidth() * 1.4f, pimg->GetHeight() * 1.5f));
}

Map_Start::~Map_Start()
{

}

Map_Start* Map_Start::Clone()
{
    return nullptr;
}

void Map_Start::update()
{
    
}

void Map_Start::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    pos = CCameraManager::getInst()->GetRenderPos(pos);

    CRenderManager::getInst()->RenderImage(
        pimg,
        pos.x,
        pos.y,
        pos.x + scale.x,
        pos.y + scale.y
    );
}
