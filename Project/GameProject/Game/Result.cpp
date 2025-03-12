#include "Result.h"
#include "../task/TaskManager.h"
Result::Result() : Task((int)ETaskPrio::Result, 0, eType_Result)
{
	//‰æ‘œ•¡»
	m_img = COPY_RESOURCE("Result", CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}
	
void Result::Update()
{
	if (PUSH(CInput::eButton1)) {
		
		TaskManager::Instance()->DeleteAll();

		
	}
}

void Result::Render()
{
     m_img.Draw();
}
