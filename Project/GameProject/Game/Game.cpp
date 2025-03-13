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
{
	new Player(CVector3D(0.0f, 0.0f, 35.0f), CVector3D(64, 180, 20), CVector3D(64, 0, 20));
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

}

Game::~Game()
{
}

void Game::Update()
{

}

void Game::Render()
{
}
