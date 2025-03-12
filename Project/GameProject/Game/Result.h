#pragma once
#include "../Task/Task.h"

class Result : public Task {
public:
	CImage m_img;
	//コントラスタ
	Result();
	void Update();
	void Render();

};