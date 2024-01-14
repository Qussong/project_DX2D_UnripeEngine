#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
	: m_arrBasicComp{}
	, m_pRenderComp(nullptr)
{
}

CGameObject::~CGameObject()
{
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

		if (type < COMPONENT_TYPE::END)
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