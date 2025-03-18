#pragma once
#include "../Task/Task.h"

class Game : public Task
{
public:
	 CFont m_Game_text;
	Game();
	~Game();
	void Update();
	void Render();
};