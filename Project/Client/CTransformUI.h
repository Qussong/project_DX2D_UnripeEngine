#pragma once

class CTransformUI
	: public CComponentUI
{
	using Super = CComponentUI;

public:
	CTransformUI();
	virtual ~CTransformUI();

public:
	virtual void Tick() override {}
	virtual void SetWindowOption() override {}	// UIâ �ɼ� ����
	virtual void Render_Update() override;		// UIâ ���� ����
};

