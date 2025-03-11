#include "StarManager.h"
#include "Star.h"

StarManager::StarManager()
	:Task((int)ETaskPrio::Other, 0, eType_StarManager)
	, StarTimer(60 * 3)
{
}

StarManager::~StarManager()
{
}

void StarManager::Update()
{
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
