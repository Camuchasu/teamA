#include "Effect.h"

Effect::Effect(const char* name, const CVector3D& pos, const CVector2D size)
	:ObjectBase(pos,eType_Effect)
	//,m_vec(vec)
	,m_size(size)
{

}

Effect::~Effect()
{
}

void Effect::Update()
{
}

void Effect::Render()
{
}
