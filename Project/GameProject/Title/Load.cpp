#include "Load.h"
#include "Game/Game.h"
#include "Task/TaskManager.h"

Load::Load()
	:Task(0,eType_Load,0)
	,LoadCount(60)
{
	m_Load = COPY_RESOURCE("Load", CImage);
}

void Load::Update()
{
	if (LoadCount == 0)
	{
		TaskManager::Instance()->DeleteAll();
		new Game();
	}
	LoadCount--;
}

void Load::Render()
{
	m_Load.Draw();
}
