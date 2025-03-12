#pragma once
#include "Task/ObjectBase.h"


class Bullet : public ObjectBase {

public:
	CImage m_img;

	Bullet(const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin);
	~Bullet();

	void Update();
	void Render();

};