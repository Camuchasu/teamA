#pragma once
#include "../Task/Task.h"

class Score : public Task 
{
public:
	CImage m_img;
public:
	Score();
	void Draw();

};