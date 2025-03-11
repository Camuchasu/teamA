#pragma once
#include "Task/ObjectBase.h"


class Player : public ObjectBase
{
public:
	// アニメーションの種類
	enum class EState
	{
		Idle,	// 待機
		Attack,	// 攻撃
		Jump,
		Damage,

		Num,
	}; 

	CImage mp_image;
	// コンストラクタ
	Player(const CVector3D& pos,CVector3D& Cube);
	// デストラクタ
	~Player();

	// 更新処理
	void Update();// override;
	// 描画処理
	void Render();// override;

	static TexAnimData ANIM_DATA[];

	EState m_state;
	int m_stateStep;


private:
	void ChangeState(EState state);
	// 移動処理の更新
	bool UpdateMove();

	// 待機時の更新処理
	void StateIdle();
	void StateAttack();
	void StateJump();
	
	float m_moveSpeedY;	// Y軸（高さ）の移動速度
	//CImage* mp_image;	// プレイヤーの画像

};