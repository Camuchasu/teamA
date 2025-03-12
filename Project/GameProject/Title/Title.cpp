#include "Title.h"
int Title::m_cnt(0);
Title::Title() : Task((int)ETaskPrio::Title, 0, eType_Title)
{
}

void Title::Update()
{
	//ボタン１でタイトル破棄
	if (m_cnt++ > 60 && PUSH(CInput::eButton1)) {
		//すべてのオブジェクトを破棄
		Task::Kill();
		//ゲームシーンへ

		//Base::Add(new Game());
	}
}

void Title::Render()
{
}
