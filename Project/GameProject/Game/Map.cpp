#include "Map.h"

Map::Map()
{
    //âÊëúÇÃï°êª
   
    m_background = COPY_RESOURCE("sky.png", CImage);
    m_background.SetSize(1920, 1080);
    
}

void Map::Draw()
{
    m_background.Draw();
}

int Map::CollisionRect(const CVector2D& pos, const CRect& rect)
{
    CRect r = CRect(
        pos.x + rect.m_left,
        pos.y + rect.m_top,
        pos.x + rect.m_right,
        pos.y + rect.m_bottom);
    int t;
    t = CollisionPoint(CVector2D(r.m_left, r.m_top));
    if (t != 0) return t;
    t = CollisionPoint(CVector2D(r.m_right, r.m_top));
    if (t != 0) return t;
    t = CollisionPoint(CVector2D(r.m_left, r.m_bottom));
    if (t != 0) return t;
    t = CollisionPoint(CVector2D(r.m_right, r.m_bottom));
    if (t != 0) return t;
    return 0;
}