#include "Hp.h"
int Hp::m_Hp(3);
Hp::Hp() : Task((int)ETaskPrio::UI, 0, eType_Hp)
{
	m_img = COPY_RESOURCE("Hp", CImage);
}

void Hp::Update()
{

}

void Hp::Render()
{
	m_img.SetSize(125, 125);
	
	for (int i = 0; i < m_Hp; i++) {
	
		m_img.SetPos(0+115*i, 64);
		m_img.Draw();
	}
}

void Hp::DownHp()
{
	m_Hp -= 1;
}
