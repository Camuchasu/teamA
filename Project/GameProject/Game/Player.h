#pragma once
#include "Task/ObjectBase.h"


class Player : public ObjectBase
{
public:
	// コンストラクタ
	Player(const CVector3D& pos);
	// デストラクタ
	~Player();

	// 更新処理
	void Update();// override;
	// 描画処理
	void Render();// override;

private:
	// 状態
	
	// アニメーションの種類
	enum class EAnimType
	{
		Idle,	// 待機
		Attack,	// 攻撃
		Jump,
		Damage,

		Num,
	};
	static TexAnimData ANIM_DATA[];
	CImage* mp_image;	// プレイヤーの画像
};