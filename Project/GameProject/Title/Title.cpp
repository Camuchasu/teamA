#include "Title.h"
#include "Task/TaskManager.h"
#include "Game/Game.h"
int Title::m_cnt(0);
Title::Title() : Task((int)ETaskPrio::Title, 0, eType_Title)
{
	//画像複製
	m_img = COPY_RESOURCE("Title", CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Title::Update()
{
	//ボタン１でタイトル破棄
	if (m_cnt++ > 1 && PUSH(CInput::eButton5)) {
		//すべてのオブジェクトを破棄
		TaskManager::Instance()->DeleteAll();
		
		//ゲームシーンへ
		new Game();
		
	}
}

void Title::Render()
{
	m_img.Draw();
}
