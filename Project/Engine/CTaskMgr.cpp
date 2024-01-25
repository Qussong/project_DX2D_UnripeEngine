#include "pch.h"
#include "CTaskMgr.h"

CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::AddObject(size_t _idx)
{
	CGameObject* pObj = (CGameObject*)m_vecTask[_idx].iParam1;
	LAYER_TYPE	eLayerType = (LAYER_TYPE)m_vecTask[_idx].iParam2;

	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
	pCurLevel->AddObject(pObj, eLayerType);
}

void CTaskMgr::SubObject(size_t _idx)
{
	CGameObject* pTarget = (CGameObject*)m_vecTask[_idx].iParam1;

	// 타겟 객체와 밑에 달린 자식들까지 모두 Dead 상태로 만들어줌
	list<CGameObject*> queue;
	queue.push_back(pTarget);
	while (!queue.empty())
	{
		CGameObject* pObj = queue.front();
		queue.pop_front();

		pObj->SetDead(true);

		vector<CGameObject*> children = pObj->GetChild();
		for (size_t i = 0; i < children.size(); ++i)
		{
			queue.push_back(children[i]);
		}
	}
}

void CTaskMgr::Tick()
{
	size_t taskCnt = m_vecTask.size();

	for (size_t i = 0; i < taskCnt; ++i)
	{
		switch (m_vecTask[i].eType)
		{
		case TASK_TYPE::ADD_OBJET:
			AddObject(i);
			break;
		case TASK_TYPE::SUB_OBJECT:
			SubObject(i);
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
