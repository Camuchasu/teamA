
#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
    Base::Add(new Field());
    Base::Add(new Player(CVector2D(0, 540), false));
    Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
    Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
    Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
    Base::Add(new Goal(CVector2D(2048, 540)));
}
Game::~Game()
{
}
void Game::Update()
{
        //ゴールが無ければゲーム終了
        if (!Base::FindObject(eType_Goal)) {
            //全てのオブジェクトを破棄
            Base::KillAll();
            //タイトルシーンへ
            Base::Add(new Title());
        }

    	//プレイヤー死亡　ボタン１でゲームシーン終了
    	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
    	    //全てのオブジェクトを破棄
    		Base::KillAll();
            //タイトルシーンへ
            Base::Add(new Title());
   	    }
}



