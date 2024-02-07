#pragma once

class CCamera
	:public CComponent
{
	using Super = CComponent;

public:
	CCamera();
	virtual ~CCamera();

private:
	PROJ_TYPE	m_eProjType;	// ����Ÿ��

	// �������� Perspective
	float		m_fFOV;			// �þ߰� (Filed Of View)
	
	// �������� Orthographic
	float		m_fScale;		// �������� ����

	// ����	Common
	Vec2		m_v2Resolution;	// �ػ�
	float		m_fAspectRatio;	// ��Ⱦ��
	float		m_fNear;		// ���� �ּ� �Ÿ�
	float		m_fFar;			// ���� �ִ� �Ÿ�

	// ��ȯ��� Result
	Matrix		m_matView;		// View ��ȯ ���
	Matrix		m_matProj;		// Projection ��ȯ ���
	
private:
	int32		m_iPriority;				// ī�޶��� �켱����
	bool		m_arrLayerCheck[LAYER_MAX];	// ī�޶� Render�� Layer (true�� Render)

private:
	// ��ü �з� : ������/������/����/��ó��/�����
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
	void		ViewMatrix();		// View ��ȯ ��� ���
	void		ProjectionMatrix();	// Projection ��ȯ ��� ���

public:
	void		SetPriority(int32 _priority);
	void		LayerCheck(LAYER_TYPE _layer, bool _bCheck);			// ī�޶� ���̾� �ν� ���� ����
	void		LayerCheck(const wstring& _layerName, bool _bCheck);	// ī�޶� ���̾� �ν� ���� ����
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

