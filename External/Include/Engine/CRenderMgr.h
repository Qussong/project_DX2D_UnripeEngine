#pragma once

class CStructuredBuffer;

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLETON(CRenderMgr);

private:	
	// Render
	vector<CCamera*>		m_vecCamera;	// 등록된 카메라 개수(우선순위 순으로 정렬되어 있음)

	// Debug
	list<tDebugShapeInfo>	m_listDebugShapeInfo;
	CGameObject*			m_pDebugObj;
	bool					m_bDebugCheck;	// Debug 객체 Render 여부

	// Light2D
	CStructuredBuffer*		m_pLight2DBuffer;
	vector<CLight2D*>		m_vecLight2D;

	// PostProcess
	Ptr<CTexture>			m_PostProcessTex;

public:
	// Getter
	bool			IsDebugCheck()		{ return m_bDebugCheck; }
	Ptr<CTexture>	GetPostProcessTex() { return m_PostProcessTex; }

	// Setter
	void SetDebugCheck(bool _flag) { m_bDebugCheck = _flag; }

private:
	void Binding();		// 리소스 바인딩(리소스 : 글로벌,광원)
	void Clear();		// 리소스 클리어

public:
	void		RegisterCamera(CCamera* _cam, int32 _idx);
	inline void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_listDebugShapeInfo.push_back(_info); }
	inline void RegisterLight2D(CLight2D* _lightObj) { m_vecLight2D.push_back(_lightObj); }
	void		CopyRenderTargetToPostProcessTarget();

public:
	void Init();
	void Tick();

private:
	void Render();
	void Render_Debug();
};