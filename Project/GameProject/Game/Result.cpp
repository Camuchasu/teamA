#include "Result.h"
#include "../task/TaskManager.h"
#include "Game.h"
#include "UI/score.h"
#include "UI/Hp.h"

Result::Result() : Task((int)ETaskPrio::Result, 0, eType_Result)
,m_Result_text("C:\\Windows\\Fonts\\msgothic.ttc", 80)
{

	//画像複製
	m_img = COPY_RESOURCE("Result", CImage);
	m_scr = COPY_RESOURCE("Score", CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}
	
void Result::Update()
{

	if (PUSH(CInput::eButton5)) {
		TaskManager::Instance()->DeleteAll();
		new Game();
		Score::s_score = 0;
		Hp::m_Hp = 3;
	}
}

void Result::Render()
{
	m_img.Draw();
	int Resultscore = Score::s_score;
	for (int i = 0; i < 8; i++, Resultscore /= 10) {
		int r = Resultscore % 10;
		m_scr.SetRect(100 * r, 0, 100 * r + 100, 128);
		m_scr.SetSize(64, 64);
		m_scr.SetPos(1150 - 64 * i, 1080/2);
		m_scr.Draw();
	}
	m_Result_text.Draw(700, 1080/2-100, 0, 0, 0, "獲得スコア！！");
}
