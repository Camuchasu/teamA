#include "Title.h"
#include "Title/Load.h"
#include "Task/TaskManager.h"
#include "EnemyManager.h"
#include "Game/StarManager.h"
#include "Game/Game.h"
#include "Game/Star.h"

int Title::m_cnt(0);
Title::Title() : Task((int)ETaskPrio::Title, 0, eType_Title)
,TitleCount(0)
{
	SOUND("Title")->Play();
	//画像複製
	m_img = COPY_RESOURCE("Title", CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Title::Update()
{
	TitleCount++;
	int StarType = rand() % 2;
	if (TitleCount % (60*1) == 0) {
		CVector3D pos(Utility::Rand(0.0f, 1920.0f), Utility::Rand(0.0f, 540.0f), Utility::Rand(0.0f, 0.0f));
		new Star (StarType,
			pos, CVector3D(0, 0, 0), CVector3D(0, 0, 0));
	}
	//ボタン１でタイトル破棄
	if (m_cnt++ > 1 && PUSH(CInput::eButton5)) {
		//すべてのオブジェクトを破棄
		TaskManager::Instance()->DeleteAll();
		SOUND("Title")->Stop();
		//ロードシーンへ
		new Load();
		
	}
}

void Title::Render()
{
	m_img.Draw();
}
