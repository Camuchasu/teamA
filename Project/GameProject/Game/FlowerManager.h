#pragma once
#include"Task/ObjectBase.h"

class FlowerManager :public Task
{
public:
	FlowerManager();
	~FlowerManager();

	int FlowerTimer;
	void Update();
};