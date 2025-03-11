#pragma once
#include"Task/ObjectBase.h"

class EnemyManager :public Task
{
public:
	EnemyManager();
	~EnemyManager();

	int enemyTimer;
	int FlowerTimer;
	int StarTimer;
	void Update();
};