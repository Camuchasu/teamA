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
	
}