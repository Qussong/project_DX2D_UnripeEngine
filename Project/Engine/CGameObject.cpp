#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
	: m_arrBasicComp{}
	, m_pRenderComp(nullptr)
	, m_pParent(nullptr)
{
	SetName(L"GameObject");
}

CGameObject::~CGameObject()
{
	// basicComp
	size_t size = (uint32)COMPONENT_TYPE::BASIC_END;
	for (size_t i = 0; i < size; i++)
	{
		if (nullptr != m_arrBasicComp[i])
		{
			delete m_arrBasicComp[i];
			m_arrBasicComp[i] = nullptr;
		}
	}

	// renderComp
	if (nullptr != m_pRenderComp)
	{
		delete m_pRenderComp;
		m_pRenderComp = nullptr;
	}

	// script
	size = m_vecScript.size();
	for (size_t i = 0; i < size; i++)
	{
		delete m_vecScript[i];
		m_vecScript[i] = nullptr;
	}

	// child
	size = m_vecChild.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete m_vecChild[i];
		m_vecChild[i] = nullptr;
	}
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::BASIC_END); ++i)
	{
		if (nullptr != m_arrBasicComp[i])
		{
			m_arrBasicComp[i]->Begin();
		}
	}

	if (nullptr != m_pRenderComp)
	{
		m_pRenderComp->Begin();
	}
	
	for (CScript* script : m_vecScript)
	{
		script->Begin();
	}

	for (CGameObject* child : m_vecChild)
	{
		child->Begin();
	}
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::BASIC_END); ++i)
	{
		if (nullptr != m_arrBasicComp[i])
		{
			m_arrBasicComp[i]->Tick();
		}
	}

	if (nullptr != m_pRenderComp)
	{
		m_pRenderComp->Tick();
	}

	for (CScript* script : m_vecScript)
	{
		script->Tick();
	}

	for (CGameObject* child : m_vecChild)
	{
		child->Tick();
	}
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::BASIC_END); ++i)
	{
		if (nullptr != m_arrBasicComp[i])
		{
			m_arrBasicComp[i]->FinalTick();
		}
	}

	if (nullptr != m_pRenderComp)
	{
		m_pRenderComp->FinalTick();
	}

	for (CScript* script : m_vecScript)
	{
		script->FinalTick();
	}

	for (CGameObject* child : m_vecChild)
	{
		child->FinalTick();
	}

}

void CGameObject::Render()
{
	if (nullptr != m_pRenderComp)
	{
		m_pRenderComp->Render();
	}

	//for (CGameObject* child : m_vecChild)
	//{
	//	child->Render();
	//}
}

void CGameObject::AddComponent(CComponent* _comp)
{
	bool isAdd = false;	// Comp 정상 추가여부 확인
	CRenderComponent* renderComp = dynamic_cast<CRenderComponent*>(_comp);	// RendeComp 인지 확인

	// RenderComp
	if (nullptr != renderComp)
	{
		isAdd = true;
		m_pRenderComp = renderComp;
		renderComp->SetOwner(this);
	}
	// BasicComp or Script
	else
	{
		COMPONENT_TYPE type = _comp->GetType();

		// Script
		if (COMPONENT_TYPE::SCRIPT == type)
		{
			CScript* script = dynamic_cast<CScript*>(_comp);

			// _comp 가 실제로 Script 클래스인경우
			if (nullptr != script)
			{
				isAdd = true;
				script->SetOwner(this);
				m_vecScript.push_back(script);
			}
		}

		// BasicComp
		if (COMPONENT_TYPE::NONE < type 
			&& type < COMPONENT_TYPE::BASIC_END)
		{
			isAdd = true;
			m_arrBasicComp[(uint32)type] = _comp;
			_comp->SetOwner(this);
		}
	}

	if (!isAdd)
	{
		MessageBoxA(nullptr, "Add Component Failed", "Component Error", MB_OK);
	}
}

CMeshRender* CGameObject::MeshRender()
{
	return dynamic_cast<CMeshRender*>(m_pRenderComp);
}

void CGameObject::Independent()
{
	vector<CGameObject*> brothers = m_pParent->m_vecChild;
	vector<CGameObject*>::iterator iter = brothers.begin();

	for (; iter != brothers.end(); ++iter)
	{
		if (*iter == this)
		{
			m_pParent->m_vecChild.erase(iter);	// 부모 객체의 자식 목록에서 해당 객체 제거
			m_pParent = nullptr;				// 현재 객체의 부모객체 제거
			return;
		}
	}

	// 반복문을 완료하고 아래까지 내려오면 해당 객체가 부모객체의 자식객체로 등록되지 않은것
	MessageBoxA(nullptr, "GameObject Independet failed", "GameObject Error", MB_OK);
	_exit(EXIT_FAILURE);
}

void CGameObject::AddChild(CGameObject* _child)
{
	// 부모객체가 존재하는 경우 부모객체와의 연결을 끊어줌
	if (nullptr != _child->m_pParent)
	{
		_child->Independent();
		_child->m_pParent = nullptr;
	}
	
	// 부모객체 새로 지정
	_child->m_pParent = this;
	m_vecChild.push_back(_child);
}