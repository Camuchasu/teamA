#pragma once
#include "Task/ObjectBase.h"


class Bullet : public ObjectBase {

public:
	CImage m_img;

	Bullet(const CVector3D& pos); 
	~Bullet();

	void Update();
	void Render();

};