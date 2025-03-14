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
		Death,

		Num,
	}; 

	CImage mp_image;
	CImage m_img;
	CImage m_Cool;
	// コンストラクタ
	Player(int speed,const CVector3D& pos, CVector3D& cubeMax, CVector3D& cubeMin);
	// デストラクタ
	~Player();

	// 更新処理
	void Update();// override;
	// 描画処理
	void Render();// override;
	
	void Collison();
	
	static TexAnimData ANIM_DATA[];

	EState m_state;
	int m_stateStep;
	int AttackCount;
	int GameCount;
	int m_speed;
	//ゲージ用画像
	CImage img;
	//ゲージの幅
	int width = 60;
	//ゲージの高さ
	int height = 16;
	
	//最大クールタイム
	int MAXAttackCount = 180;
private:
	void ChangeState(EState state);
	// 移動処理の更新
	bool UpdateMove();

	// 待機時の更新処理
	void StateIdle();
	void StateAttack();
	void StateJump();
	void StateDamage();
	void StateDeath();

	void Collision(Task* b);

	
	
	float m_moveSpeedY;	// Y軸（高さ）の移動速度
	//CImage* mp_image;	// プレイヤーの画像

};