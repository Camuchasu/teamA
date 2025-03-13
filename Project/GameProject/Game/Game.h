#pragma once
#include "../Task/Task.h"

class Game : public Task
{
public:
	Game();
	~Game();
	void Update();
	void Render();
};