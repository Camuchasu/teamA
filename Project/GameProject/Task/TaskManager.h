#pragma once


class Task;
class ObjectBase;
//タスクを管理するクラス
class TaskManager
{
public:
	//TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	//TaskManagerのインスタンスを破棄
	static void ClearInstance();
	//リストに登録されているタスクを更新
	void Update();
	//リストに登録されているタスクを描画
	void Render();
	//コンストラクタ
	TaskManager();
	//デストラクタ
	~TaskManager();

	//タスクリストにタスクを追加
	void Add(Task* task,bool sort = false);
	//タスクリストからタスクを取り除く
		void Remove(Task* task, bool sort = false);
	//全てのタスクを削除
		void DeleteAll();
	//削除フラグが立っているタスクを削除
		void DeletekilledTasks();
		void Collision();
private:
	//TaskManagerのインスタンス
	static TaskManager* ms_instance;
	//生成済みのタスクのリスト
	std::list<Task*>m_taskList;
	std::list<Task*>m_objectList;
};