#include "EnemyManager.h"
#include "Game/Enemy.h"
#include "Game/StarManager.h"
#include "Game/FlowerManager.h"
#include "Game/Flower.h"
#include "Game/StarManager.h"
#include "Game/Star.h"


EnemyManager::EnemyManager()
	:Task((int)ETaskPrio::Other, 0, eType_EnemyManager)
	, enemyTimer(60 * 3)
	, FlowerTimer(60 * 3)
	, StarTimer(60 * 3)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	enemyTimer--;
	if (time >= 0) {
		if (enemyTimer < 0) {
			int EnemyType = rand() % 2;
			int Line = rand() % 4;


			new Enemy(EnemyType,
				CVector3D(1920.0f + ObjectBase::m_scroll.x, EnemyType*200.0f, 34+Line*174.0f-348), CVector3D(20, 20, 20));

			enemyTimer = 60 * 1.5;
		}
		FlowerTimer--;
		if (time >= 0) {
			if (FlowerTimer < 0) {
				int FlowerType = rand() % 2;
				int Line = rand() % 4;


				new Flower(FlowerType,
					CVector3D(1920.0f + ObjectBase::m_scroll.x, 0.0f, 34 + Line * 174.0f - 348), CVector3D(20, 20, 20));

				FlowerTimer = 60 * 1.5;
			}
		}
		StarTimer--;
		if (time >= 0) {
			if (StarTimer < 0) {
				int FlowerType = rand() % 2;
				int Line = rand() % 4;


				new Star(FlowerType,
					CVector3D(1920.0f + ObjectBase::m_scroll.x, 0.0f, 34 + Line * 174.0f - 348), CVector3D(20, 20, 20));

				StarTimer = 60 * 0.75;
			}
		}
	}
}
