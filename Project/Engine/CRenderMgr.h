#pragma once

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLETON(CRenderMgr);

private:	// Render
	vector<CCamera*>		m_vecCamera;	// ��ϵ� ī�޶� ����(�켱���� ������ ���ĵǾ� ����)

private:	// Debug
	list<tDebugShapeInfo>	m_listDebugShapeInfo;
	CGameObject*			m_pDebugObj;

public:
	void RegisterCamera(CCamera* _cam, int32 _idx);

public:
	void AddDebugShapeInfo(const tDebugShapeInfo& _info)
	{
		m_listDebugShapeInfo.push_back(_info);
	}
	
public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
};