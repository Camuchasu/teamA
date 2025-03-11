#pragma once
#include "../Task/Task.h"

class Hp : public Task
{
public:
	CImage m_img;
	Hp();
	void Update();
	void Render();
	static int m_Hp;
};