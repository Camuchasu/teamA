#pragma once
#include "../Task/Task.h"

class Score : public Task 
{
public:
	CImage m_img;
	int m_score;
	Score();
	void Render();
	static void AddScore(int ad);
	static void DownScore(int sage);
	static int s_score;
	
};