#include "Field.h"

Field::Field()
{
	m_Sky = COPY_RESOURCE("Sky", CImage);
	m_town = COPY_RESOURCE("Town", CImage);
	m_foreground = COPY_RESOURCE("ForeGround", CImage);
	//ínñ ÇÃçÇÇ≥
	m_ground_y = 540;
}
void Field::Draw()
{
	float sc;
	m_Sky.Draw();
	sc = m_scroll.x / 4;
	m_town.SetRect(sc, 0, sc + 1280, 720);
	m_town.Draw();
	sc = m_scroll.x;
	m_foreground.SetRect(sc, 0, sc + 1280, 720);
	m_foreground.Draw();

}