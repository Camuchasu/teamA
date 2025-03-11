#include "EnemyManager.h"
#include "Game/Enemy.h"

EnemyManager::EnemyManager()
	:Task((int)ETaskPrio::Other, 0, eType_EnemyManager)
	, enemyTimer(60 * 3)
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

			enemyTimer = 60 * 0.5;
		}
	}
}
