#pragma once

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLETON(CRenderMgr);

private:	// Render
	vector<CCamera*>		m_vecCamera;	// 등록된 카메라 개수(우선순위 순으로 정렬되어 있음)

private:	// Debug
	list<tDebugShapeInfo>	m_listDebugShapeInfo;
	CGameObject*			m_pDebugObj;
	bool					m_bDebugCheck;	// Debug 객체 Render 여부

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