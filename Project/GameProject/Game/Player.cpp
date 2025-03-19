#include "Player.h"
#include <Task/ObjectBase.h>
#include "Game/Bullet.h"
#include "UI/Hp.h"
#include "Result.h"
#include "UI/score.h"
#include "task/TaskManager.h"


#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 30.0f	    // ジャンプ速度
#define GRAVITY -1.8f		// 重力

static TexAnim _idle[] = {
	{0,10},
	{1,10},
};

static TexAnim _Attack[] = {
	{8,10},
	{9,10},
};

static TexAnim _Jump[] = {
	{4,5},
	{5,5},
	{6,5},
	{7,5},
};
static TexAnim _Damage[] = {
	{12,10},
	{13,10},
};
static TexAnim _Death[] = {
	{12,10},
	{13,10},
};
TexAnimData Player::ANIM_DATA[] = {
	ANIMDATA(_idle),
	ANIMDATA(_Attack),
	ANIMDATA(_Jump),
	ANIMDATA(_Damage),
	ANIMDATA(_Death),
};


Player::Player(int speed,const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin)
	: ObjectBase(pos, eType_Player)
	, m_stateStep(0)
	,AttackCount(180)
	,GameCount(0)

{
	mp_image = COPY_RESOURCE("Player", CImage);
	img = COPY_RESOURCE("CoolTime", CImage);
	mp_image.ChangeAnimation(0);
	mp_image.SetSize(180, 180);
	mp_image.SetCenter(90,180);
	m_MaxCube = cubeMax;
	m_MinCube = cubeMin;
	
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
	if (GameCount <= (60*30)) {
		SOUND("SpeedUp")->Play(true);
		m_speed = 11;
		m_pos.x += m_speed;
	}
	if (GameCount >= (60 * 30) && GameCount < (60 * 60)) {
		m_speed = 14;
		m_pos.x += m_speed;
	}
	if (GameCount >= (60 * 60) && GameCount < (60 * 90)) {
		m_speed = 16;
		m_pos.x += m_speed;
	}
	if (GameCount >= (60 * 90) && GameCount < (60 * 120)) {
		m_speed = 18;
		m_pos.x += m_speed;
	}
	if (GameCount >= (60 * 120)) {
		m_speed = 20;
		m_pos.x += m_speed;
	}
		ObjectBase::m_scroll.x = m_pos.x - 1920 / 4;
		switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Jump:	    StateJump();	break;
	case EState::Damage:	StateDamage();	break;
	case EState::Death:	    StateDeath();	break;
	}
//	m_pos.x += speed;
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
	AttackCount--;
	GameCount++;
}

void Player::Render()
{
	//影を付けることができる
	ObjectBase::RenderShadow();
	img.SetPos(CalcScreenPos()+CVector2D(0,-180));
	//ゲージ背景（赤）
	img.SetSize(width, height);
	img.SetRect(0,64,width,128);
	img.Draw();
	//ゲージの幅を計算(緑)
	int w = width * min(1.0,(1-AttackCount / (float)MAXAttackCount));
	img.SetSize(w, height);
	if (w >= width)
	{
		img.SetRect(0, 0, width, 64);
	}
	else {
		img.SetRect(0, 128, width, 128 + 64);
		
	}
		img.Draw();
	mp_image.SetPos(CalcScreenPos());
	mp_image.Draw();
	RenderCube();
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
 	if (PUSH(CInput::eMouseL) && AttackCount <= 0)
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
		new Bullet(m_speed+30,CVector3D(m_pos.x, m_pos.y+64, m_pos.z), CVector3D(40, 40, 20), CVector3D(40, 40, 20));
		mp_image.ChangeAnimation((int)EState::Attack, false);
		SOUND("Player_Attackv")->Play();
		SOUND("Player_Attack")->Play();
		AttackCount = 180;
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
		SOUND("Player_Jump")->Play();
		// Y軸（高さ）の移動速度にジャンプを速度を設定し、
		// 接地状態を解除する
		mp_image.ChangeAnimation((int)EState::Jump, false);
		if (m_isGrounded == true)
		{
			m_moveSpeedY = JUMP_SPEED;
		}
		m_isGrounded = false;
		m_stateStep++;
		break;
		// ステップ1：ジャンプ終了
	case 1:
		if (PUSH(CInput::eMouseL) && AttackCount < 0)
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
	//bool isMove = UpdateMove();
	mp_image.ChangeAnimation((int)EState::Jump);
}

void Player::StateDamage()
{
	SOUND("Player_Damage")->Play();
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

void Player::StateDeath()
{
	SOUND("Player_Death")->Play();
	mp_image.ChangeAnimation((int)EState::Death, false);
	if (mp_image.CheckAnimationEnd());
	{
		SOUND("GameBGM")->Stop();
		TaskManager::Instance()->DeleteAll();
		new Result();
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
				if (Hp::m_Hp > 0) {
					ChangeState(EState::Damage);
				}
				if (Hp::m_Hp == 0) {
					ChangeState(EState::Death);
				}
			}
		}
	}
}
