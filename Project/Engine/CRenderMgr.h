#pragma once

class CStructuredBuffer;

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

private:	// Light2D
	CStructuredBuffer*		m_pLight2DBuffer;
	vector<CLight2D*>		m_vecLight2D;

public:
	// Getter
	bool IsDebugCheck() { return m_bDebugCheck; }
	
	// Setter
	void SetDebugCheck(bool _flag) { m_bDebugCheck = _flag; }

public:
	void RegisterCamera(CCamera* _cam, int32 _idx);
	void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_listDebugShapeInfo.push_back(_info); }
	
	void RegisterLight2D(CLight2D* _lightObj) { m_vecLight2D.push_back(_lightObj); }

public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
	void Binding();		// ���ҽ� ���ε�(���ҽ� : �۷ι�,����)
	void Clear();		// ���ҽ� Ŭ����
};