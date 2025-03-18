#pragma once
#include "task/Task.h"

class Load : public Task
{
public:
	CImage m_Load;
	Load();
	
	int LoadCount;
	void Update();
	void Render();
};
