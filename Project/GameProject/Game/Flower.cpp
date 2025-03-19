#include "Flower.h"
#include "../UI/score.h"


#define CHIP_SIZE 256		// 1コマのサイズ
#define CENTER_POS CVector2D(65.0f, 96.0f)	// 中心座標
//char Flower
// 花のアニメーションデータ
    static TexAnim _Idle[] = {
	{0,8},
	{1,8},
};

static TexAnim _Death[] = {
	{2,8},
	{3,8},
};
TexAnimData Flower::ANIM_DATA[] = {
	ANIMDATA(_Idle),
	ANIMDATA(_Death),
};
// コンストラクタ
Flower::Flower(int type, const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin)
	: ObjectBase(pos, eType_Flower)
{

	// 花の画像を読み込み
	m_img = COPY_RESOURCE("Flower", CImage);
	m_img.ChangeAnimation(0);
	m_img.SetSize(80, 80);
	m_img.SetCenter(40, 80);
	m_MaxCube = cubeMax;
	m_MinCube = cubeMin;
}

Flower::~Flower()
{
}
// 死亡処理
void Flower::Death()
{
	// 死亡状態へ移行
	ChangeState(EState::Death);
}

// 現在の状態を切り替え
void Flower::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 待機時の更新処理
void Flower::StateIdle()
{
	// 待機アニメーションを再生
	m_img.ChangeAnimation((int)EAnimType::Idle);
}

// 死亡時の更新処理
void Flower::StateDeath()
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
			SOUND("Flower")->Play();
			//削除フラグを立てる
			Kill();
			
				Score::DownScore(200);
			
			
		}
		break;
	}
}

// 更新処理
void Flower::Update()
{

	// 状態に合わせて、更新処理を切り替える
	switch (m_state)
	{
	case EState::Idle:	StateIdle();	break;
	case EState::Death:	StateDeath();	break;
	}

	// イメージに座標を設定して、アニメーションを更新
	m_img.UpdateAnimation();
}

// 描画処理
void Flower::Render()
{
	//影を付けることができる
	ObjectBase::RenderShadow();
	//位置設定
	m_img.SetPos(CalcScreenPos());
	m_img.Draw();
	RenderCube();
}

void Flower::Collision(Task* b)
{
	switch (b->m_type)
	{
	case eType_Player: {
		if (ObjectBase::CollisionCube(this, dynamic_cast<ObjectBase*>(b)))
		{
			ChangeState(EState::Death);
		}
	}
	case eType_Bullet: {
		if (ObjectBase::CollisionCube(this, dynamic_cast<ObjectBase*>(b)))
		{
			//b->Kill();
			ChangeState(EState::Death);
		}
	}
	}
}
