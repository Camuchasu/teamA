#pragma once
#include "../Task/Task.h"

class Score : public Task 
{
public:
	CImage m_img;
public:
	Score();
	void Render();
	void AddScore(int ad);
	static int s_score;
};