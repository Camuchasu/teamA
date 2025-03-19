#include "EnemyManager.h"
#include "Game/Enemy.h"
#include "Game/StarManager.h"
#include "Game/Star.h"
#include "Game/flower.h"
#include "Game/Field.h"


EnemyManager::EnemyManager()
	:Task((int)ETaskPrio::Other, 0, eType_EnemyManager)
	, enemyTimer(60 * 0.7)
	, FlowerTimer(60 * 3.5)
	, StarTimer(60 * 5)
	, EnemyLine(0)
	
	
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	
	if (time >= 0) {
		enemyTimer--;
		if (enemyTimer < 0) {
			//カスタムによってプログラムを変えていく（２列決めたり、花も一緒にしたりなど）
			int Enemyapper[30][4] = {
			{ 1,1,0,3 },//0
			{ 3,0,1,1 },//1
			{ 1,1,1,1 },//2
			{ 1,2,1,2 },//3
			{ 2,2,2,2 },//4
			{ 0,0,0,3 },//5
			{ 3,1,3,1 },//6
			{ 3,3,3,3 },//7
			{ 2,0,1,0 },//8
			{ 2,1,2,1 },//9
			{ 2,2,3,3 },//10
			{ 1,0,3,2 },//11
			{ 1,2,1,0 },//12
			{ 0,2,0,1 },//13
			{ 1,2,2,0 },//14
			{ 3,1,3,1 },//15
			{ 1,3,0,3 },//16
			{ 3,2,1,0 },//17
			{ 0,3,0,1 },//18
			{ 1,2,1,1 },//19
			{ 3,0,1,0 },//20
			{ 0,2,1,0 },//21
			{ 0,3,2,1 },//22
			{ 3,2,1,0 },//23
			{ 2,2,2,3 },//24
			{ 3,2,0,0 },//25
			{ 1,1,0,1 },//26
			{ 3,0,1,2 },//27
			{ 3,0,2,1 },//28
			{ 1,2,0,1 },//29
			};
			
			EnemyLine = rand() % 4;//列
			
			int EnemyGroup = rand() % 10;//Enemyapperの配列の位置決め　//行
			for (EnemyLine = 0; EnemyLine < 4; EnemyLine++)
			{
				int EnemyType = rand() % 2;//空中のカラスか地上のカラスか
				if (Enemyapper[EnemyGroup][EnemyLine] == 1) {

					new Enemy(EnemyType,
						CVector3D(1920.0f + ObjectBase::m_scroll.x,
							EnemyType * 200.0f, 34 + EnemyLine * 174.0f - 348),
						CVector3D(64, 120, 20), CVector3D(64, 0, 20));

				}
				if (Enemyapper[EnemyGroup][EnemyLine] == 2) {
					new Flower(0,
						CVector3D(1920.0f + ObjectBase::m_scroll.x,
							0, 34 + EnemyLine * 174.0f - 348),
						CVector3D(64, 120, 20), CVector3D(64, 0, 20));
				}
				if (Enemyapper[EnemyGroup][EnemyLine] == 3) {
					new Star(0,
						CVector3D(1920.0f + ObjectBase::m_scroll.x,
							0, 34 + EnemyLine * 174.0f - 348),
						CVector3D(64, 120, 20), CVector3D(64, 0, 20));
				}
			}


			enemyTimer = 60 * 3;
		}
		/*FlowerTimer--;
		if (time >= 0) {
			if (FlowerTimer < 0) {
				int Flowerapper[4] = { 0,0,0,0 };              //レーンの初期値
				int FlowerType = rand() % 2;
					int n = 1+rand() % 4;                      //変数を決める
						for (int i = 0; i < n; i++) {          //nの数だけループを繰り返す
							FlowerLine = rand() % 4;           //抽選
						while(Flowerapper[FlowerLine] != 0)    //レーン（抽選されたFlowerLine）が0以外であれば
						{
							FlowerLine = rand() % 4;           //再抽選
						}
							new Flower(FlowerType,
								CVector3D(1920.0f + ObjectBase::m_scroll.x, 0.0f, FlowerLine * 174.0f - 348),
								CVector3D(40, 80, 20), CVector3D(40, 0, 20));
							Flowerapper[FlowerLine] += 1;      //表示が重ならないようにするために１を代入する
						}
					
				FlowerTimer = 60 * 3;
			}
		}*/
		/*StarTimer--;
		if (time >= 0) {
			if (StarTimer < 0) {
				int StarType = rand() % 2;
				    StarLine = rand() % 4;
				while (StarLine == FlowerLine || StarLine == EnemyLine) {
					   StarLine = rand() % 4;
				}


				new Star(StarType,
					CVector3D(1920.0f + ObjectBase::m_scroll.x, 0.0f, 34 + StarLine * 174.0f - 348), CVector3D(50, 100, 20), CVector3D(50, 0, 20));

				StarTimer = 60 * 3;
			}
		}*/
	}
}
