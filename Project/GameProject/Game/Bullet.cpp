#include "Bullet.h"

Bullet::Bullet(const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin)
	: ObjectBase(pos,eType_Bullet)
{
	m_img = COPY_RESOURCE("Bullet", CImage);
	m_img.ChangeAnimation(0);
	m_img.SetSize(64, 64);
	m_img.SetCenter(32,32);
	m_MaxCube = cubeMax;
	m_MinCube = cubeMin;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_img.UpdateAnimation();
	const int move_speed = 20;
	m_pos.x += move_speed;
}

void Bullet::Render()
{
	m_img.SetPos(CalcScreenPos());
	m_img.Draw();
	//‰e‚ð•t‚¯‚é‚±‚Æ‚ª‚Å‚«‚é
	ObjectBase::RenderShadow();
	RenderCube();
}
