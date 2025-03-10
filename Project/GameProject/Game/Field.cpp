#include "Field.h"
#include "../Task/ObjectBase.h"
Field::Field()
{
	m_Sky = COPY_RESOURCE("Sky", CImage);
	m_yama = COPY_RESOURCE("yama", CImage);
	//m_foreground = COPY_RESOURCE("ForeGround", CImage);
	//ínñ ÇÃçÇÇ≥
	m_ground_y = 540;
}
void Field::Draw()
{
	float sc;
	m_Sky.Draw();
	//sc = ObjectBase::m_scroll.x / 4;
	//m_yama.SetRect(sc, 0, sc + 1280, 720);
	m_yama.SetRect(0,0,1280, 720);
	m_yama.Draw();
	//sc = ObjectBase::m_scroll.x;
	//m_foreground.SetRect(sc, 0, sc + 1280, 720);
	//m_foreground.SetRect(0, 0, 0 + 1280, 720);
	//m_foreground.Draw();

}