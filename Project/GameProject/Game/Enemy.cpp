#include "Enemy.h"
#include "../UI/score.h"

#define CHIP_SIZE 256		// 1コマのサイズ
#define CENTER_POS CVector2D(128.0f, 184.0f)	// 中心座標

// カラスのアニメーションデータ
TexAnimData enemy_anim_data[] =
{
	{
		new TexAnim[2]
		{
			{ 0, 6}, { 1, 6},
			
		},
		2
	},
	{
		new TexAnim[5]
		{
			{5, 6}, {6, 6}, {7, 6},
			{8, 6}, {9, 6},
		},
		5
	},
};

// コンストラクタ
Enemy::Enemy(int Enemytype, const CVector3D& pos, CVector3D& Cube)
	: ObjectBase(pos,eType_Enemy)
	, m_Enemytype(Enemytype)
	
{
	//メンバ変数を使う
	 m_Cube = Cube;
	// カラスの画像を読み込み
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.ChangeAnimation(0);
	m_img.SetSize(120, 120);
	m_img.SetCenter(60,120);
}

Enemy::~Enemy()
{
}
// 死亡処理
void Enemy::Death()
{
	// 死亡状態へ移行
	ChangeState(EState::Death);
}

// 現在の状態を切り替え
void Enemy::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 待機時の更新処理
void Enemy::StateIdle()
{
	//移動量
	const float move_speed = 0;
	//移動フラグ
	bool move_flag = false;
	//移動量を設定
	m_pos.x += -move_speed;
	
	move_flag = true;
	// 待機アニメーションを再生
	m_img.ChangeAnimation((int)EAnimType::Idle);
}

// 死亡時の更新処理
void Enemy::StateDeath()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：死亡アニメーションを再生
	case 0:
		m_img.ChangeAnimation((int)EAnimType::Death, false);
		m_stateStep++;
		break;
		// ステップ1：アニメーション終了待ち
	case 1:
		// アニメーションが終了したら、削除
		if (m_img.CheckAnimationEnd())
		{
			//削除フラグを立てる
			Kill();
		}
		break;
	}
}

// 更新処理
void Enemy::Update()
{
	
	// 状態に合わせて、更新処理を切り替える
	switch (m_state)
	{
	case EState::Idle:	StateIdle();	break;
	case EState::Death:	StateDeath();	break;
	}

	m_img.UpdateAnimation();
	
}

// 描画処理
void Enemy::Render()
{
	//影を付けることができる
	ObjectBase::RenderShadow();
	//位置設定
	m_img.SetPos(CalcScreenPos());
	m_img.Draw();
}
void Enemy::Collision(Task* b)
{
	switch (b->m_type)
	{
	case eType_Player: {
		if (m_state != EState::Death) {
			if (ObjectBase::CollisionCube(this, dynamic_cast<ObjectBase*>(b)))
			{
				ChangeState(EState::Death);
				if (m_Enemytype == 0) {
					Score::AddScore(100);
				}
				else {
					Score::AddScore(200);
				}
			}
		}
	}break;
		//玉に当たれば
	case eType_Bullet: {
		if (m_state != EState::Death) {
			if (ObjectBase::CollisionCube(this, dynamic_cast<ObjectBase*>(b)))
			{
				b->Kill();
				ChangeState(EState::Death);
				if (m_Enemytype == 0) {
					Score::AddScore(100);
				}
				else {
					Score::AddScore(200);
				}
			}
		}
	}break;
	}
}
