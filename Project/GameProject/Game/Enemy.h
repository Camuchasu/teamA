#pragma once
#include "../Base/Base.h"

class Enemy : public Base {

private:
    //状態
    enum {
        eState_Idle,
        eState_Attack,
        eState_Damage,
        eState_Down,
    };
    int m_state;        //状態
    CImage m_img;       //画像
    bool	m_flip;     //反転
    bool m_is_ground;   //着地フラグ
    //攻撃番号
    int m_attack_no;
    //ダメージ番号
    int m_damage_no;
    //ヒットポイント
    int m_hp;
    void StateIdle();
    void StateAttack();
    void StateDamage();
    void StateDown();
public:
    Enemy(const CVector2D& p, bool flip);
    void Update();
    void Draw();
    void Collision(Base* b);
};