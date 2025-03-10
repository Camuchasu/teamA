#include "Field.h"
#include "../Task/ObjectBase.h"
Field::Field(const CVector3D& pos)
    :Task((int)ETaskPrio::Field, 0)
{
    m_Sky = COPY_RESOURCE("Sky", CImage);
    m_Yama = COPY_RESOURCE("yama", CImage);
}
void Field::Update()
{

}

void Field::Render()
{
    float sc;
    m_Sky.Draw();

    sc = ObjectBase::m_scroll.x / 3;
    m_Yama.SetRect(sc, 0, sc + 720, 203);
    m_Yama.Draw();
    m_Yama.SetSize(720 * 3, 203 * 3);
    m_Yama.SetPos(0, 450);
}