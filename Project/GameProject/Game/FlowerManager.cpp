#include "FlowerManager.h"
#include "Game/Flower.h"

FlowerManager::FlowerManager()
	:Task((int)ETaskPrio::Other, 0, eType_FlowerManager)
	, FlowerTimer(60 * 3)
{

}

FlowerManager::~FlowerManager()
{
}

void FlowerManager::Update()
{
	FlowerTimer--;
	if (time >= 0) {
		if (FlowerTimer < 0) {
			int FlowerType = rand() % 2;
			int Line = rand() % 4;


			new Flower(FlowerType,
				CVector3D(1920.0f + ObjectBase::m_scroll.x,0.0f, 34 + Line * 174.0f - 348), CVector3D(20, 20, 20));

			FlowerTimer = 60 * 1.5;
		}
	}
}
