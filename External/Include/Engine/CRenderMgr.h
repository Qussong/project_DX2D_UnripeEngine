#pragma once

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLETON(CRenderMgr);

private:
	vector<CCamera*>		m_vecCamera;	// 등록된 카메라 개수(우선순위 순으로 정렬되어 있음)

public:
	void RegisterCamera(CCamera* _cam, int32 _idx);
	
public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
};