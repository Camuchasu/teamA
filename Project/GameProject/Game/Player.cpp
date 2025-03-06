#include "Player.h"
#include <Task/ObjectBase.h>

#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 15.0f	// ジャンプ速度
#define GRAVITY -1.0f		// 重力

static TexAnim _idle[] = {
	{0,8},
	{1,8},
};

static TexAnim _Attack[] = {
	{4,8},
	{5,8},
};

static TexAnim _Jump[] = {
	{0,8},
	{1,8},
	{2,8},
	{3,8},
};
static TexAnim _Damage[] = {
	{6,8},
	{7,8},
};
TexAnimData Player::ANIM_DATA[] = {
	ANIMDATA(_idle)
};



Player::Player(const CVector3D& pos)
	: ObjectBase(pos)
	, mp_image(nullptr)
{

	// プレイヤーの画像を読み込み
	mp_image = CImage::CreateImage
	(
		"Idle.png",	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		32,32	// 1コマの幅と高さ
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(16,32);
}
Player::~Player()
{
}

void Player::Update()
{
	mp_image->UpdateAnimation();
}

void Player::Render()
{
	mp_image->SetPos(CalcScreenPos());
	mp_image->Draw();
}

