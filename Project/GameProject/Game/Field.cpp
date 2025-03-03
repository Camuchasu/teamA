#include "Field.h"

Field::Field() :Base(eType_Field)
{
    m_sky = COPY_RESOURCE("Sky", CImage);
    m_town = COPY_RESOURCE("Town", CImage);
    m_foreground = COPY_RESOURCE("ForeGround", CImage);
    m_ground_y = 540;
    m_line_list.push_back({ {0,540},{500,540} });
    m_line_list.push_back({ {500,540},{1000,400} });
    m_line_list.push_back({ {1000,400},{1500,540} });
    m_line_list.push_back({ {1500,540},{9999,540} });
}
void Field::Draw()
{
    m_sky.Draw();
    CVector2D sc(m_scroll/4);
    m_town.SetRect(sc.x, sc.y, sc.x + 1280, sc.y+ 720);
    m_town.Draw();
    sc = m_scroll;
    m_foreground.SetRect(sc.x, sc.y , sc.x + 1280, sc.y + 720);
    m_foreground.Draw();
}

float Field::GetGroundY(int x)
{
    for (auto& l : m_line_list) {
        if (l.s.x <= x && l.e.x >= x) {
            //このライン上にキャラクターがいる
            //s→eへのベクトル
            CVector2D v = l.e - l.s;
            //s→eライン上で、x地点の内分率
            float t = (x - l.s.x) / v.x;
            //s→eライン上でのx地点と同じ位置
            CVector2D p = l.s + v * t;
            return p.y;

        }
    }
    return 1000.0f;
}



