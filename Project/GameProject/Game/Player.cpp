#include "Player.h"
#include <Task/ObjectBase.h>
#include "Game/Bullet.h"

#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 10.0f	// ジャンプ速度
#define GRAVITY -0.1f		// 重力

static TexAnim _idle[] = {
	{0,8},
	{1,8},
};

static TexAnim _Attack[] = {
	{6,8},
	{7,8},
};

static TexAnim _Jump[] = {
	{2,8},
	{3,8},
	{4,8},
	{5,8},
};
static TexAnim _Damage[] = {
	{8,8},
	{9,8},
};
TexAnimData Player::ANIM_DATA[] = {
	ANIMDATA(_idle),
	ANIMDATA(_Attack),
	ANIMDATA(_Jump),
	ANIMDATA(_Damage),
};



Player::Player(const CVector3D& pos)
	: ObjectBase(pos)
	, m_stateStep(0)
{
	mp_image = COPY_RESOURCE("Player", CImage);
	mp_image.ChangeAnimation(0);
	mp_image.SetSize(128, 128);
	mp_image.SetCenter(64,140);
	// プレイヤーの画像を読み込み
/*	mp_image = CImage::CreateImage
	(
		"Idle1.png",	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		32,32	// 1コマの幅と高さ
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(16,16);*/
}
Player::~Player()
{
}

void Player::Update()
{
	switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Jump:	    StateJump();	break;
	}
	m_pos.x += 1.2;
	mp_image.UpdateAnimation();

	// Y軸（高さ）の移動を座標に反映
	m_pos.y += m_moveSpeedY;
	m_moveSpeedY += GRAVITY;	// Y軸の移動速度に重力を加算
	// 地面より下にいくと
	if (m_pos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		m_pos.y = 0.0f;
		m_moveSpeedY = 0.0f;
		m_isGrounded = true;
	}

}

void Player::Render()
{
	//影を付けることができる
	ObjectBase::RenderShadow();
	mp_image.SetPos(CalcScreenPos());
	mp_image.Draw();
	
}

void Player::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

bool Player::UpdateMove()
{
	bool isMove = false;
	
	if (PUSH(CInput::eUp))
	{
		m_pos.z -= 100;
		isMove = true;
		if (m_pos.z <= -300)
		{
			m_pos.z += 100;
		}
	}
	else if (PUSH(CInput::eDown))
	{
		m_pos.z += 100;
		isMove = true;
		if (m_pos.z > 100)
		{
			m_pos.z -= 100;
		}
	}

	return isMove;
}

void Player::StateIdle()
{
	// 移動処理
	bool isMove = UpdateMove();
	mp_image.ChangeAnimation((int)EState::Idle, true);

	if (PUSH(CInput::eButton5))
	{
		ChangeState(EState::Jump);
	}
	if (PUSH(CInput::eButton2))
	{
		ChangeState(EState::Attack);
	}
	
}

void Player::StateAttack()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：攻撃アニメーションに切り替え
	case 0:
		new Bullet(CVector3D(m_pos));
		mp_image.ChangeAnimation((int)EState::Attack, false);
		m_stateStep++;
		break;
		// ステップ1：アニメーション終了待ち
	case 1:
		// 攻撃アニメーションが終了したら、待機状態へ移行
		if (mp_image.CheckAnimationEnd())
		{
			if (m_isGrounded == false) {
				ChangeState(EState::Jump);
			}
			else {
				ChangeState(EState::Idle);
			}
		}
		break;
	}
	
}

void Player::StateJump()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：ジャンプ開始
	case 0:
		// Y軸（高さ）の移動速度にジャンプを速度を設定し、
		// 接地状態を解除する
		if (EState::Attack, true)
		{
			m_moveSpeedY = JUMP_SPEED;
		}
		m_isGrounded = false;
		m_stateStep++;
		break;
		// ステップ1：ジャンプ終了
	case 1:
		if (PUSH(CInput::eButton2))
		{
			ChangeState(EState::Attack);
		}
		// 接地したら、待機状態へ移行
		if (m_isGrounded)
		{
			ChangeState(EState::Idle);
		}
		break;
	}

	// 移動処理
	bool isMove = UpdateMove();
	mp_image.ChangeAnimation((int)EState::Idle);
}


