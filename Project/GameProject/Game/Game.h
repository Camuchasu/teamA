#pragma once
#include "../Task/Task.h"

class Game : public Task
{
public:
	CImage m_Enemyhyouzi;
	CImage m_Enemyhyouzi2;
	CImage m_Starhyouzi;
	CImage m_Flowerhyouzi;
	 CFont m_Game_text;
	Game();
	~Game();
	void Update();
	void Render();
};