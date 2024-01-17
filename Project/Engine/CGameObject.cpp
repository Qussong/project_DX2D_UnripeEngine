#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
	: m_arrBasicComp{}
	, m_pRenderComp(nullptr)
{
	SetName(L"GameObject");
}

CGameObject::~CGameObject()
{
	// basicComp
	size_t size = (uint32)COMPONENT_TYPE::END;
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
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
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
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
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
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
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

}

void CGameObject::Render()
{
	if (nullptr != m_pRenderComp)
	{
		m_pRenderComp->Render();
	}
}

void CGameObject::AddComponent(CComponent* _comp)
{
	bool isAdd = false;
	CRenderComponent* renderComp = nullptr;
	renderComp = dynamic_cast<CRenderComponent*>(_comp);

	if (nullptr != renderComp)
	{
		isAdd = true;
		m_pRenderComp = renderComp;
		renderComp->SetOwner(this);
	}
	else
	{
		COMPONENT_TYPE type = _comp->GetType();

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

		if (COMPONENT_TYPE::END > type)
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
	if (nullptr != m_pRenderComp)
	{
		return dynamic_cast<CMeshRender*>(m_pRenderComp);
	}

	return nullptr;
}
