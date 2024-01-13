#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_iWidth(0)
	, m_iHeight(0)

{
}

CEngine::~CEngine()
{
	if (nullptr != m_RectMesh)
		delete m_RectMesh;

	if (nullptr != m_CircleMesh)
		delete m_CircleMesh;

	if (nullptr != m_Shader)
		delete m_Shader;

	if (nullptr != m_CB)
		delete m_CB;
}

int CEngine::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	// member init
	m_hWnd = _hWnd;
	m_iWidth = _width;
	m_iHeight = _height;

	// Device, Context, SwapChain init
	CGraphics::GetInst()->Init(m_hWnd, m_iWidth, m_iHeight);

	// Manager init
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	// test
	Test_init();

	return S_OK;
}

void CEngine::Progress()
{
	// update
	Tick();

	// render
	Render();
}

void CEngine::Tick()
{
	// manager
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	// test
	Test_tick();
}

void CEngine::Render()
{
	CGraphics::GetInst()->RenderBegin();

	// Rendering Pipeline
	{
		// test
		Test_render();
	}

	CGraphics::GetInst()->RenderEnd();
}

void CEngine::Test_init()
{
	// Rect Mesh 생성
	//Test_RectMesh();
	Test_CircleMesh();

	// Shader 생성
	m_Shader = new CGraphicShader();
	m_Shader->VertexShader(L"std2d.fx", "VS_Std2D");
	m_Shader->PixelShader(L"std2d.fx", "PS_Std2D");

	// Constant Buffer 생성
	m_CB = new CConstantBuffer();
	m_CB->Create(sizeof(tTransform), 1);
}

void CEngine::Test_RectMesh()
{
	// Vertex Buffer & Index Buffer 생성
	m_RectMesh = new CMesh();

	Vtx		arrRect[4] = {};
	UINT	arrIdx[6] = {};
	// 정점 정보 입력
	{
		// 사각형 정점 위치 설정
		// 0(R)--- 1(B)	     
		//  |   \   |	     
		// 3(G)--- 2(M)  

		arrRect[0].vPos = Vec3{ -0.5f, 0.5f, 0.f };
		arrRect[0].vColor = Vec4{ 1.f, 0.f, 0.f, 1.f };
		arrRect[0].vUV = Vec2{ -1.f, 1.f };

		arrRect[1].vPos = Vec3{ 0.5f, 0.5f, 0.f };
		arrRect[1].vColor = Vec4{ 0.f, 0.f, 1.f, 1.f };
		arrRect[1].vUV = Vec2{ 1.f, 1.f };

		arrRect[2].vPos = Vec3{ 0.5f, -0.5f, 0.f };
		arrRect[2].vColor = Vec4{ 1.f, 0.f, 1.f, 1.f };
		arrRect[2].vUV = Vec2{ 1.f, -1.f };

		arrRect[3].vPos = Vec3{ -0.5f, -0.5f, 0.f };
		arrRect[3].vColor = Vec4{ 0.f, 1.f, 0.f, 1.f };
		arrRect[3].vUV = Vec2{ -1.f, -1.f };
	}

	// 인덱스 정보 입력
	{
		arrIdx[0] = 0;
		arrIdx[1] = 1;
		arrIdx[2] = 2;

		arrIdx[3] = 0;
		arrIdx[4] = 2;
		arrIdx[5] = 3;
	}

	m_RectMesh->Create(arrRect, 4, arrIdx, 6);
}

void CEngine::Test_CircleMesh()
{
	// Vertex Buffer & Index Buffer 생성
	m_CircleMesh = new CMesh();

	vector<Vtx> vecCircle;
	vector<UINT> vecIdx;
	// 정점 정보 입력
	{
		// 중심점
		Vtx center;
		center.vPos = Vec3(0.f, 0.f, 0.f);
		center.vColor = Vec4(0.5f, 0.f, 0.5f, 1.f);
		center.vUV = Vec2(0.5f, 0.5f);
		vecCircle.push_back(center);

		// 원 둘레
		Vtx		temp;
		int32	iSlice = 100;
		float	fTheta = 0.f;
		float	fRadius = 0.5f;

		for (size_t i = 0; i < iSlice; ++i)
		{
			fTheta = (XM_2PI / iSlice) * i;
			
			temp.vPos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
			temp.vColor = Vec4(0.f, 0.5f, 0.5f, 1.f);
			temp.vUV = Vec2(0.f, 0.f);

			vecCircle.push_back(temp);
		}

		for (size_t i = 0; i < iSlice - 1; i++)
		{
			vecIdx.push_back(0);
			vecIdx.push_back(i+2);
			vecIdx.push_back(i+1);
		}
		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(iSlice);

		m_CircleMesh->Create(vecCircle.data(),
							(uint32)vecCircle.size(), 
							vecIdx.data(), 
							(uint32)vecIdx.size());
	}
}

void CEngine::Test_tick()
{
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		m_tTransform.vWorldPos.x -= DT;

		cout << "X " << (int)(m_tTransform.vWorldPos[0] * 255)
			<< "/Y " << (int)(m_tTransform.vWorldPos[1] * 255) << endl;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		m_tTransform.vWorldPos.x += DT;

		cout << "X " << (int)(m_tTransform.vWorldPos[0] * 255)
			<< "/Y " << (int)(m_tTransform.vWorldPos[1] * 255) << endl;
	}


	// 상수 버퍼 바인딩
	uint32 registerNum = 0;
	m_CB->SetData(&m_tTransform, 1);
	m_CB->Update(registerNum);
}

void CEngine::Test_render()
{
	// update data
	//m_RectMesh->Update();
	m_CircleMesh->Update();
	m_Shader->Update();

	// render
	//m_RectMesh->Render();
	m_CircleMesh->Render();
}