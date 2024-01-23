#include "pch.h"
#include "CTaskMgr.h"

CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::Tick()
{
	size_t taskCnt = m_vecTask.size();

	for (size_t i = 0; i < taskCnt; ++i)
	{
		switch (m_vecTask[i].eType)
		{
		case TASK_TYPE::CREATE_OBJET:
		{
			CGameObject* pObj = (CGameObject*)m_vecTask[i].iParam1;
			LAYER_TYPE	eLayerType = (LAYER_TYPE)m_vecTask[i].iParam2;

			CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
			pCurLevel->AddObject(pObj, eLayerType);
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:
		{

		}
			break;
		case TASK_TYPE::ADD_CHILD:
		{

		}
			break;
		case TASK_TYPE::DISCONNECT_PARENT:
		{

		}
			break;
		case TASK_TYPE::LEVEL_CHANGE:
		{

		}
			break;
		default:
		{

		}
			break;
		}
	}

	// Task 완료후 비움
	m_vecTask.clear();
}
