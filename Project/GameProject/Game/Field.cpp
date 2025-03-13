#include "Field.h"
#include "../Task/ObjectBase.h"
#include "UI/Score.h"
float Field::m_msc(ObjectBase::m_scroll.x);
Field::Field(const CVector3D& pos)
    :Task((int)ETaskPrio::Field, 0,eType_Field)
{
    m_Sky = COPY_RESOURCE("Sky", CImage);
    m_Yama = COPY_RESOURCE("yama", CImage);
    m_yuka = COPY_RESOURCE("yuka", CImage);
    m_kumo = COPY_RESOURCE("kumo", CImage);
}
void Field::Update()
{

}

void Field::Render()
{
    float sc;
    m_Sky.Draw();
    
        m_msc = ObjectBase::m_scroll.x;
    m_yuka.SetRect(m_msc, 0, m_msc + 1920, 704);
    m_yuka.SetPos(0,374);
    m_yuka.Draw();
    sc = ObjectBase::m_scroll.x / 15;
    m_Yama.SetRect(sc, 0, sc + 1920, 376);
    m_Yama.Draw();
    sc = ObjectBase::m_scroll.x / 3;
    m_kumo.SetRect(sc, 0, sc + 1920, 376);
    m_kumo.Draw();
}