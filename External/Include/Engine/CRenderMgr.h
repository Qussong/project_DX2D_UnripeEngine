#pragma once

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLETON(CRenderMgr);

private:
	vector<CCamera*>		m_vecCamera;	// ��ϵ� ī�޶� ����(�켱���� ������ ���ĵǾ� ����)

public:
	void RegisterCamera(CCamera* _cam, int32 _idx);
	
public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
};