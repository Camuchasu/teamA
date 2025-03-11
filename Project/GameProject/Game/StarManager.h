#pragma once
#include"Task/ObjectBase.h"

class StarManager :public Task
{
public:
	StarManager();
	~StarManager();

	int StarTimer;
	void Update();
};