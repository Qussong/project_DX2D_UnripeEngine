#pragma once

class CLayer
	: public CEntity
{
	using Super = CEntity;

public:
	CLayer();
	virtual ~CLayer();

private:
	vector<CGameObject*> m_vecParent;

private:
	void AddObject(CGameObject* _obj) { m_vecParent.push_back(_obj); }

private:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();

	friend CLevel;
};

