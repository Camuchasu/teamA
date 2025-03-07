#include "Star.h"


#define CHIP_SIZE 256		// 1コマのサイズ
#define CENTER_POS CVector2D(128.0f, 184.0f)	// 中心座標

// 星のアニメーションデータ
TexAnimData Star_anim_data[] =
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
Star::Star(int type, const CVector3D& pos)
	: ObjectBase(pos)
	, m_type(type)
{
	//m_hp = 200;

	// カラスの画像を読み込み
	std::string imagePath;
	if (m_type == 0) imagePath = "Image/Star.png";
	m_img = COPY_RESOURCE("Star", CImage);
	m_img.ChangeAnimation(0);
	m_img.SetSize(100, 100);
	m_img.SetCenter(50, 100);
}

Star::~Star()
{
}

// 現在の状態を切り替え
void Star::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 待機時の更新処理
void Star::StateIdle()
{
	// 待機アニメーションを再生
	m_img.ChangeAnimation((int)EAnimType::Idle);
}

// 死亡時の更新処理
/*void Star::StateDeath()
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
}*/

// 更新処理
void Star::Update()
{

	// 状態に合わせて、更新処理を切り替える
	switch (m_state)
	{
	case EState::Idle:	StateIdle();	break;
	//case EState::Death:	StateDeath();	break;
	}

	// イメージに座標を設定して、アニメーションを更新
	m_img.UpdateAnimation();
}

// 描画処理
void Star::Render()
{
	//影を付けることができる
	ObjectBase::RenderShadow();
	//位置設定
	m_img.SetPos(CalcScreenPos());
	m_img.Draw();
	
}
