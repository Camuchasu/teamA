#include "EnemyManager.h"
#include "Game/Enemy.h"
#include "Game/StarManager.h"
#include "Game/Star.h"
#include "Game/flower.h"
#include "Game/Field.h"


EnemyManager::EnemyManager()
	:Task((int)ETaskPrio::Other, 0, eType_EnemyManager)
	, enemyTimer(60 * 3)
	, FlowerTimer(60 * 3)
	, StarTimer(60 * 3)
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
			int EnemyType = rand() % 2;
		        EnemyLine = rand() % 4;;


			new Enemy(EnemyType,
				CVector3D(1920.0f + ObjectBase::m_scroll.x, EnemyType*200.0f, 34+EnemyLine*174.0f-348), CVector3D(64, 120, 20), CVector3D(64, 0, 20));

			enemyTimer = 60 * 3;
		}
		FlowerTimer--;
		if (time >= 0) {
			if (FlowerTimer < 0) {
				int FlowerType = rand() % 2;
				    FlowerLine = rand() % 4;
					while (EnemyLine == FlowerLine)
					{
						FlowerLine = rand() % 4;
				     }

				new Flower(FlowerType,
					CVector3D(1920.0f + ObjectBase::m_scroll.x, 0.0f, 34 + FlowerLine * 174.0f - 348), CVector3D(40, 80, 20), CVector3D(40, 0, 20));

				FlowerTimer = 60 * 3;
			}
		}
		StarTimer--;
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
		}
	}
}
