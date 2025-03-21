#pragma once
#include "../Task/Task.h"

class Result : public Task {
public:
	CImage m_img;
	CImage m_scr;
	//コントラスタ
	Result();
	void Update();
	void Render();
	//文字表示オブジェクト
	CFont m_Result_text;
};