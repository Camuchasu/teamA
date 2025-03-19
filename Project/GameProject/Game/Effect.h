#pragma once
#include "task/ObjectBase.h"

class Effect : ObjectBase
{
public:
	Effect(const char* name, const CVector3D& pos, const CVector2D size);
	~Effect();
	static TexAnimData Effect_anim_data[];
	CImage m_img;
	CVector3D m_vec;
	CVector3D m_size;
	float alpfa;//“§–¾“x
	float scale;//‘å‚«‚³
	void Update();
	void Render();
	
};
