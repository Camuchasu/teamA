#pragma once
#include "Task.h"
// 全てのオブジェクトのベースクラス
class ObjectBase:public Task
{
public:
	// コンストラクタ
	ObjectBase(int Type);
	ObjectBase(const CVector3D& pos,int Type);

	// デストラクタ
	virtual ~ObjectBase();

	// 座標を取得
	const CVector3D& GetPos() const;
	// 座標を設定
	void SetPos(const CVector3D& pos);
	//スクロール値
	static CVector2D m_scroll;
	/// <summary>
	/// 3次元座標からスクリーン座標（2D）に変換
	/// </summary>
	/// <param name="grounded">trueならば、高さは考慮せず地面の位置を返す</param>
	/// <returns>スクリーン座標</returns>
	CVector2D CalcScreenPos(bool grounded = false) const;
	CVector2D CalcScreenPos(const CVector3D& pos, bool grounded = false) const;

	// 更新
	virtual void Update();
	// 描画
	virtual void Render();

	// 影描画
	virtual void RenderShadow();
	static bool CollisionCube(ObjectBase*b1,ObjectBase*b2);
	void RenderCube();
protected://継承しているとこだけ限定で使っていいよね
	CVector3D m_pos;		// オブジェクトの座標
	CVector3D m_Max;
	CVector3D m_Min;
	CVector3D m_Cube;
	bool m_isGrounded;		// 地面に接地してあるかどうか
	CImage* mp_shadowImg;	// 影の画像
};