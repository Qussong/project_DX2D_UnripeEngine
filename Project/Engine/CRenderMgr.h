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
	bool					m_bDebugCheck;	// Debug ��ü Render ����

public:
	void RegisterCamera(CCamera* _cam, int32 _idx);
	void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_listDebugShapeInfo.push_back(_info); }
	
	void SetDebugCheck(bool _flag) { m_bDebugCheck = _flag; }
	bool IsDebugCheck() { return m_bDebugCheck; }
	
public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
};