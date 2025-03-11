#pragma once
#include"Task/ObjectBase.h"

class EnemyManager :public Task
{
public:
	EnemyManager();
	~EnemyManager();

	int enemyTimer;
	void Update();
};