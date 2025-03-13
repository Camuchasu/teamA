#include "Result.h"
#include "../task/TaskManager.h"
#include "Game.h"
#include "UI/score.h"
#include "UI/Hp.h"

Result::Result() : Task((int)ETaskPrio::Result, 0, eType_Result)
{
	//‰æ‘œ•¡»
	m_img = COPY_RESOURCE("Result", CImage);
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
}
