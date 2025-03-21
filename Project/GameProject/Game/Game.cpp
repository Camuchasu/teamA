#include "Game.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "EnemyManager.h"
#include "Task/ObjectBase.h"
#include "Game/Star.h"
#include "Game/StarManager.h"
#include "Game/Flower.h"
#include "Game/FlowerManager.h"
#include "Game/Field.h"
#include "UI/Score.h"
#include "UI/Hp.h"
#include "Title/Title.h"
#include "Game/Result.h"
Game::Game() : Task((int)ETaskPrio::Game, 0, eType_Game)
, m_Game_text("C:\\Windows\\Fonts\\msgothic.ttc", 40)
, GameCount(0)
{
	SpeedUp = COPY_RESOURCE("SpeedUp", CImage);
	m_Enemyhyouzi = COPY_RESOURCE("Enemyhyouzi", CImage);
	m_Enemyhyouzi2 = COPY_RESOURCE("Enemyhyouzi2", CImage);
	m_Starhyouzi = COPY_RESOURCE("Starhyouzi", CImage);
	m_Flowerhyouzi = COPY_RESOURCE("Flowerhyouzi", CImage);
	SOUND("GameBGM")->Play(true);
	
	new Player(10,CVector3D(0.0f, 0.0f, 35.0f), CVector3D(64, 180, 20), CVector3D(64, 0, 20));
	// カラスを生成
	/*new Enemy(0,
		CVector3D(0.0f, 0.0f, 0.0f), CVector3D(30, 30, 30));*/
	//星を生成
	//new Star(0, CVector3D(0.0, 0.0f, 0.0f), CVector3D(64, 120, 20), CVector3D(64, 0, 20));
	//花を生成
	//new Flower(0, CVector3D(700, 0.0f, 0.0f), CVector3D(20, 20, 20));
	//フィールドの生成
	new Field(CVector3D(1280, 720, 136));
	new Score();
	new StarManager();
	new Hp();
	new EnemyManager();
	new FlowerManager();
	//リザルトシーン
	//new Result();
	m_Starhyouzi.ChangeAnimation(0);
	m_Enemyhyouzi.ChangeAnimation(0);
	m_Enemyhyouzi2.ChangeAnimation(0);
	m_Flowerhyouzi.ChangeAnimation(0);
}

Game::~Game()
{
}

void Game::Update()
{

	m_Starhyouzi.UpdateAnimation();
	m_Enemyhyouzi.UpdateAnimation();
	m_Enemyhyouzi2.UpdateAnimation();
	m_Flowerhyouzi.UpdateAnimation();
}

void Game::Render()
{
	SpeedUp.SetSize(500, 500);
	SpeedUp.SetPos(550, 575);


	m_Enemyhyouzi.SetSize(80, 80);
	m_Enemyhyouzi.SetPos(550, 75);
	m_Enemyhyouzi.Draw();

	m_Enemyhyouzi2.SetSize(80, 80);
	m_Enemyhyouzi2.SetPos(700, 25);
	m_Enemyhyouzi2.Draw();

	m_Starhyouzi.SetSize(80,80);
	m_Starhyouzi.SetPos(850, 75);
	m_Starhyouzi.Draw();

	m_Flowerhyouzi.SetSize(80,80);
	m_Flowerhyouzi.SetPos(1000, 75);
	m_Flowerhyouzi.Draw();
	//文字表示
	m_Game_text.Draw(550, 200, 0, 0, 0, "+100");
	m_Game_text.Draw(700, 200, 0, 0, 0, "+200");
	m_Game_text.Draw(850, 200, 0, 0, 0, "+100");
	m_Game_text.Draw(1000, 200, 0, 0, 0, "-200");
}
