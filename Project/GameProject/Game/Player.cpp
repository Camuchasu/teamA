#include "Player.h"
#include <Task/ObjectBase.h>
#include "Game/Bullet.h"
#include "UI/Hp.h"

#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 7.0f	// ジャンプ速度
#define GRAVITY -0.1f		// 重力

static TexAnim _idle[] = {
	{0,10},
	{1,10},
};

static TexAnim _Attack[] = {
	{8,10},
	{9,10},
};

static TexAnim _Jump[] = {
	{4,10},
	{5,10},
	{6,10},
	{7,10},
};
static TexAnim _Damage[] = {
	{12,10},
	{13,10},
};
TexAnimData Player::ANIM_DATA[] = {
	ANIMDATA(_idle),
	ANIMDATA(_Attack),
	ANIMDATA(_Jump),
	ANIMDATA(_Damage),
};


Player::Player(const CVector3D& pos, CVector3D& Cube)
	: ObjectBase(pos, eType_Player)
	, m_stateStep(0)

{
	m_Cube = Cube;
	mp_image = COPY_RESOURCE("Player", CImage);
	mp_image.ChangeAnimation(0);
	mp_image.SetSize(180, 180);
	mp_image.SetCenter(90,180);
	
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
	ObjectBase::m_scroll.x = m_pos.x - 1920/4;
	switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Jump:	    StateJump();	break;
	case EState::Damage:	StateDamage();	break;
	}
	m_pos.x += 10;
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

void Player::Collison()
{
	
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
		m_pos.z -= 174;
		isMove = true;
		if (m_pos.z < -313)
		{
			m_pos.z += 174;
		}

	}
	else if (PUSH(CInput::eDown))
	{
		m_pos.z += 174;
		isMove = true;
		if (m_pos.z > 209)
		{
			m_pos.z -= 174;
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
	if (PUSH(CInput::eMouseL))
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
		new Bullet(CVector3D(m_pos.x, m_pos.y+64, m_pos.z),CVector3D(100,100,100));
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
		if (m_isGrounded == true)
		{
			m_moveSpeedY = JUMP_SPEED;
		}
		m_isGrounded = false;
		m_stateStep++;
		break;
		// ステップ1：ジャンプ終了
	case 1:
		if (PUSH(CInput::eMouseL))
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

void Player::StateDamage()
{
	mp_image.ChangeAnimation((int)EState::Damage,false);
	if (mp_image.CheckAnimationEnd())
	{
		if (m_isGrounded == false) {
			ChangeState(EState::Jump);
		}
		else {
			ChangeState(EState::Idle);
		}
	}
}

void Player::Collision(Task* b)
{
	switch (b->m_type)
	case eType_Enemy: {
		if (m_state != EState::Damage) {
			if (ObjectBase::CollisionCube(this, dynamic_cast<ObjectBase*>(b)))
			{
				Hp::DownHp();
				ChangeState(EState::Damage);
			}
		}
	}
}
