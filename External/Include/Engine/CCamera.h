#pragma once

class CCamera
	:public CComponent
{
	using Super = CComponent;

public:
	CCamera();
	virtual ~CCamera();

private:
	PROJ_TYPE	m_eProjType;	// 투영타입

	// 원근투영 Perspective
	float		m_fFOV;			// 시야각 (Filed Of View)
	
	// 직교투영 Orthographic
	float		m_fScale;		// 직교투영 배율

	// 공용	Common
	Vec2		m_v2Resolution;	// 해상도
	float		m_fAspectRatio;	// 종횡비
	float		m_fNear;		// 투영 최소 거리
	float		m_fFar;			// 투영 최대 거리

	// 변환행렬 Result
	Matrix		m_matView;		// View 변환 행렬
	Matrix		m_matProj;		// Projection 변환 행렬
	
private:
	int32		m_iPriority;				// 카메라의 우선순위
	bool		m_arrLayerCheck[LAYER_MAX];	// 카메라가 Render할 Layer (true만 Render)

private:
	// 물체 분류 : 불투명/반투명/투명/후처리/디버그
	vector<CGameObject*> m_DomainObj[(uint32)SHADER_DOMAIN::END];

public:
	// Getter
	PROJ_TYPE		GetProjectionType() { return m_eProjType; }
	float			GetFOV()			{ return m_fFOV; }
	float			GetScale()			{ return m_fScale; }
	const Matrix	GetViewMatrix()		{ return m_matView; }
	const Matrix	GetProjMatrix()		{ return m_matProj; }

	// Setter
	void		SetProjectionType(PROJ_TYPE _type)	{ m_eProjType = _type; }
	void		SetFOV(float _fov)					{ m_fFOV = _fov; }
	void		SetScale(float _scale)				{ m_fScale = _scale; }

private:
	void		ViewMatrix();		// View 변환 행렬 계산
	void		ProjectionMatrix();	// Projection 변환 행렬 계산

public:
	void		SetPriority(int32 _priority);
	void		LayerCheck(LAYER_TYPE _layer, bool _bCheck);			// 카메라 레이어 인식 여부 설정
	void		LayerCheck(const wstring& _layerName, bool _bCheck);	// 카메라 레이어 인식 여부 설정
	void		LayerCheckAll(bool _bCheck = true);

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};
	virtual void Render();

public:
	void		 SortObject();
private:
	void		 Render(vector<CGameObject*>& _vecObj);
	void		 Render_PostProcess(vector<CGameObject*>& _vecObj);
};

