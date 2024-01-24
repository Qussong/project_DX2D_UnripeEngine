#include "pch.h"
#include "func.h"

void GamePlayStatic::SpawnGameObject(CGameObject* _target, LAYER_TYPE _layerType)
{
	tTask task = {};
	task.eType = TASK_TYPE::ADD_OBJET;
	task.iParam1 = (DWORD_PTR)_target; 
	task.iParam2 = (DWORD_PTR)_layerType;

	M_TASK->AddTask(task);

	// UINT_PTR :
	// - 32bit : unsigned int
	// - 64bit : unsigned __int64

	// DWORD_PTR : 
	//	- 32bit : unsigned long
	//	- 64bit : unsigned __int64
}

void GamePlayStatic::DestroyGameObject(CGameObject* _target)
{

}
