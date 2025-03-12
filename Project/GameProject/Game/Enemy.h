#pragma once
#include <Task/ObjectBase.h>

class Enemy : public ObjectBase
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">スライムの種類</param>
	/// <param name="pos">初期位置</param>
	 Enemy(int type, const CVector3D& pos, CVector3D& cubeMax,CVector3D & cubeMin);
	// デストラクタ
	~Enemy();

	CImage m_img;

	// 死亡処理
	 void Death();
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

	void Collision(Task* b);
private:
	// 状態
	enum class EState
	{
		Idle,	// 待機状態
		Death,	// 死亡
	};
	void ChangeState(EState state);

	// 待機時の更新処理
	void StateIdle();
	// 死亡時の更新処理
	void StateDeath();

	EState m_state;
	int m_stateStep;

	// アニメーションの種類
	enum class EAnimType
	{
		Idle,	// 待機
		Death,	// 死亡

		Num,
	};
	int m_Enemytype;			// スライムの種類
};
extern TexAnimData enemy_anim_data[];