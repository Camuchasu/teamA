#include "Score.h"
Score::Score() : Task(0,0,eType_Score) {
	m_img.Load("Image/Score.png");

}
void Score::Draw()
{
	int score = 3000;
	for (int i = 0; i < 8; i++, score /= 10) {
		int s = score % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(200 - 16 * i, 32);
		m_img.Draw();
	}
}