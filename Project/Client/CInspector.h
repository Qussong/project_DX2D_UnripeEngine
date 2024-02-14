#pragma once

class CGameObject;
class CAsset;
class CComponentUI;

class CInspector
	: public CUI
{
	using Super = CUI;

public:
	CInspector();
	virtual ~CInspector();

private:
	CGameObject*	m_pTargetObj;
	Ptr<CAsset>		m_pTargetAsset;

	CComponentUI*	m_arrCompUI[(UINT)COMPONENT_TYPE::RENDER_END];

public:
	void SetTargetObject(CGameObject* _obj);
	void SetTargetAsset(Ptr<CAsset> _asset);

public:
	virtual void Tick() override {}
	virtual void Render_Update() override;
};

