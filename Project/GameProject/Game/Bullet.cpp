#include "Bullet.h"

Bullet::Bullet(int speed,const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin)
	: ObjectBase(pos,eType_Bullet)
{
	m_img = COPY_RESOURCE("Bullet", CImage);
	m_img.ChangeAnimation(0);
	m_img.SetSize(64, 64);
	m_img.SetCenter(32,32);
	m_MaxCube = cubeMax;
	m_MinCube = cubeMin;
	m_speed = speed;//スピードを設定する
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_img.UpdateAnimation();
	m_pos.x += m_speed;
}

void Bullet::Render()
{
	m_img.SetPos(CalcScreenPos());
	m_img.Draw();
	//影を付けることができる
	ObjectBase::RenderShadow();
	RenderCube();
}
