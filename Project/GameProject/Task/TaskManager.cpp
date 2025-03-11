#include "TaskManager.h"
#include "Task.h"
#include "ObjectBase.h"
//TaskManagerのインスタンスの性的なメンバ変数を定義
TaskManager* TaskManager::ms_instance = nullptr;

//コンストラクタ
TaskManager::TaskManager()
{
}

//デストラクタ
TaskManager::~TaskManager()
{
	DeleteAll();
}
////TaskManagerのインスタンスを取得
TaskManager* TaskManager::Instance()
{
	//インスタンスが生成されてなければ、
	//インスタンス生成後に返す
	if (ms_instance == nullptr) 
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}
//TaskManagerのインスタンスを破棄
void TaskManager::ClearInstance()
{
}
//リストに登録されているタスクを更新
void TaskManager::Update()
{
	//削除フラグが立っているタスクを削除
	DeletekilledTasks();
	//リストの先頭から順番に更新処理を呼び出す
	for (Task* task : m_taskList)
	{
		if (task ->IsEnable()) {
			task->Update();
		}
	}
}
//リストに登録されているタスクを描画
void TaskManager::Render()
{
	//オブジェクオリスとの中身を奥行きの座標が大きい順に並べる
	m_objectList.sort
	(
		[](const Task* task0, const Task* task1)
		{
			const ObjectBase* obj0 = dynamic_cast<const ObjectBase*>(task0);
			const ObjectBase* obj1 = dynamic_cast<const ObjectBase*>(task1);
			return obj0->GetPos().z < obj1->GetPos().z;
		}
	);
	//並び変えたオブジェクトリストの先頭から大きい順に並び変える
	int sortOrder = 0;
	for (Task* obj : m_objectList) {
		obj->SetSortOrder(sortOrder);
		sortOrder++;
	}
	//リストの先頭から順番に描画処理を呼び出す
	for (Task* task : m_taskList)
	{
		task->Render();
	}
}
//タスクリストにタスクを追加
void TaskManager::Add(Task* task, bool sort)
{
	if (!sort) 
	{
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.push_back(task);
		}
	}
	auto itr = m_taskList.begin();
	auto end = m_taskList.end();
	while (itr != end)
	{
		Task* curr = *itr;
		//追加するタスクの優先度の値のほうが小さい場合は、
		//その位置にタスクを追加する
		if (task->m_prio < curr->m_prio)
		{
			m_taskList.insert(itr, task);
			return;
		}
		//追加するタスクと現在調べているタスクの優先度が同じ場合は、
		//m_sortOrder の順番でリストに追加する
		else if (task->m_prio == curr->m_prio)
		{
			if (task->m_sortOrder < curr->m_sortOrder)
			{
				m_taskList.insert(itr, task);
				return;
			}
		}
		++itr;
	}
	//リストの間に追加する場所が見つからなかったので、
	//リストの一番最後に追加
	m_taskList.push_back(task);
}

//タスクリストからタスクを取り除く
void TaskManager::Remove(Task* task, bool sort)
{
	if (!sort)
	{
		//オブジェクトのリストからも取り除く
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.remove(task);
		}
	}
	m_taskList.remove(task);
}
//全てのタスクを削除
void TaskManager::DeleteAll()
{
	//オブジェクトのリストも空にする
	m_objectList.clear();
	auto itr = m_taskList.begin();
	auto end = m_taskList.end();
	while (itr != end) 
	{
		//削除するタスクのアドレスをいったん記憶し、
		//リストから取り除いた後に、タスクを削除する
		Task* del = *itr;
		itr = m_taskList.erase(itr);
		delete del;
	}
}
//削除フラグが立っているタスクを削除
void TaskManager::DeletekilledTasks()
{
	//タスクリストの先頭から順番に調べる
	auto itr = m_taskList.begin();
	auto end = m_taskList.end();
	while (itr != end)
	{
		//削除フラグが立っていたら、削除する
		Task* task = *itr;
		if (task->IsKill())
		{
			Task* del = *itr;
			itr = m_taskList.erase(itr);
			delete del;
		}
		//削除フラグが立っていなければ、次のタスクを調べる
		else
		{
			++itr;
		}
	}
}

void TaskManager::Collision()
{
	auto it1 = m_objectList.begin();
	auto last = m_objectList.end();
	while (it1 != last) {
		auto it2 = it1;
		it2++;
		while (it2 != last) {
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			it2++;
		}
		it1++;
	}
}
