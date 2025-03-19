#pragma once
#include "../task/Task.h"
class Title : public Task {
public:
	//画像の表示
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;

	static int m_cnt;
	int TitleCount;
	Title();
	void Update();
	void Render();
};