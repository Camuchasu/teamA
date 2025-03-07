#pragma once
#include <Task/ObjectBase.h>

class Star : public ObjectBase
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">スライムの種類</param>
	/// <param name="pos">初期位置</param>
	Star(int type, const CVector3D& pos);
	// デストラクタ
	~Star();

	CImage m_img;

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

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
	
	EState m_state;
	int m_stateStep;

	// アニメーションの種類
	enum class EAnimType
	{
		Idle,	// 待機
		Death,	// 死亡

		Num,
	};
	int m_type;			// スライムの種類
};
extern TexAnimData Star_anim_data[];