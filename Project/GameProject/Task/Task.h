#pragma once
class TaskManager;
//タスクの優先度の種類
enum {
	eType_Player,
	eType_Enemy,
	eType_Star,
	eType_Flower,
	eType_Bullet,
	eType_Field,
	eType_Score,
	eType_EnemyManager,
	eType_FlowerManager,
};
enum class ETaskPrio
{
	Field,//フィールド
	Other,
	Shadow,//影
	Object,//オブジェクト（プレイヤーとか敵とか）
	UI,
};


class Task
{
	friend TaskManager;
public:
	//コンストラクタ
	Task(int prio, int sortOrder,int type);
	//デストラクタ
	virtual ~Task();
	//有効フラグを設定
	void SetEnable(bool enable);
	//有効フラグを取得
	bool IsEnable() const;
	//表示フラグを設定
	void IsShow(bool show);
	//表示フラグを取得
	bool IsShow() const;
	//タスクを削除
	void Kill();
	//削除フラグが立っているか
	bool IsKill() const;
	//優先度を設定
	void SetPriority(int prio);
	//優先度を取得
	int GetPriority() const;
	//優先度内の順番を設定
	void SetSortOrder(int order);
	//優先度内の順番を取得
	int GetSortOrder() const;
	//更新
	virtual void Update();
	//描画
	virtual void Render();

	virtual void Collision(Task* b);
	int m_type;
private:
	bool m_isEnable;  //有効フラグ
	bool m_isShow;    //表示フラグ
	bool m_isKill;    //削除フラグ
	int m_prio;       //タスクの優先度
	int m_sortOrder;  //同じ優先度内での順番
	
};