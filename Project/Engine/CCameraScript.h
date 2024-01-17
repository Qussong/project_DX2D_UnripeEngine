#pragma once

class CCameraScript
	: public CScript
{
public:
	CCameraScript();
	virtual ~CCameraScript();

private:
	virtual void Begin() override {};
	virtual void Tick() override;
	virtual void FinalTick() override {};
	virtual void UpdateData() override {};

};

