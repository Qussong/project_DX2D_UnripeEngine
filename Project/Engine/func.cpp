#include "pch.h"
#include "func.h"

void GamePlayStatic::SpawnGameObject(CGameObject* _target, LAYER_TYPE _layerType)
{
	// UINT_PTR :
	// - 32bit : unsigned int
	// - 64bit : unsigned __int64

	// DWORD_PTR : 
	//	- 32bit : unsigned long
	//	- 64bit : unsigned __int64

	tTask task = {};
	task.eType = TASK_TYPE::ADD_OBJET;
	task.iParam1 = (DWORD_PTR)_target; 
	task.iParam2 = (DWORD_PTR)_layerType;

	M_TASK->AddTask(task);
}

void GamePlayStatic::DestroyGameObject(CGameObject* _target)
{
	tTask task = {};
	task.eType = TASK_TYPE::SUB_OBJECT;
	task.iParam1 = (DWORD_PTR)_target;
	task.iParam2 = (DWORD_PTR)NULL;

	M_TASK->AddTask(task);
}

template<typename T>
void Lazy::DelVector(vector<T>&_vec)
{
	size_t length = _vec.size();
	for (size_t i = 0; i < length; i++)
	{
		if (nullptr == _vec[i])
			return;
		delete _vec[i];
	}
}