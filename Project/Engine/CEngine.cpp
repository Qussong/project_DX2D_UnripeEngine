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
	if (nullptr != m_pRectMesh)
		delete m_pRectMesh;

	if (nullptr != m_pCircleMesh)
		delete m_pCircleMesh;

	if (nullptr != m_pShader)
		delete m_pShader;
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

	// Mesh 생성
	RectMesh();
	CircleMesh();

	// Shader 생성
	m_pShader = new CGraphicShader();
	m_pShader->VertexShader(L"std2d.fx", "VS_Std2D");
	m_pShader->PixelShader(L"std2d.fx", "PS_Std2D");

	// GameObject 생성
	Test_GameObject();

	return S_OK;
}

void CEngine::Progress()
{
	Tick();
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

void CEngine::Test_tick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->Tick();
		m_vecObj[i]->FinalTick();
	}
}

void CEngine::RectMesh()
{
	// Vertex Buffer & Index Buffer 생성
	m_pRectMesh = new CMesh();

	Vtx		arrRect[4] = {};
	UINT	arrIdx[6] = {};
	// 정점 정보 입력
	{
		// 사각형 정점 위치 설정
		// 0(R)--- 1(B)	     
		//  |   \   |	     
		// 3(G)--- 2(M)  

		arrRect[0].v3Pos = Vec3{ -0.5f, 0.5f, 0.f };
		arrRect[0].v4Color = Vec4{ 0.5f, 0.f, 0.5f, 1.f };
		arrRect[0].v2UV = Vec2{ -1.f, 1.f };

		arrRect[1].v3Pos = Vec3{ 0.5f, 0.5f, 0.f };
		arrRect[1].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
		arrRect[1].v2UV = Vec2{ 1.f, 1.f };

		arrRect[2].v3Pos = Vec3{ 0.5f, -0.5f, 0.f };
		arrRect[2].v4Color = Vec4{ 0.5f, 0.f, 0.5f, 1.f };
		arrRect[2].v2UV = Vec2{ 1.f, -1.f };

		arrRect[3].v3Pos = Vec3{ -0.5f, -0.5f, 0.f };
		arrRect[3].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
		arrRect[3].v2UV = Vec2{ -1.f, -1.f };
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

	m_pRectMesh->Create(arrRect, 4, arrIdx, 6);
}

void CEngine::CircleMesh()
{
	// Vertex Buffer & Index Buffer 생성
	m_pCircleMesh = new CMesh();

	vector<Vtx> vecCircle;
	vector<UINT> vecIdx;
	// 정점 정보 입력
	{
		// 중심점
		Vtx center;
		center.v3Pos = Vec3(0.f, 0.f, 0.f);
		center.v4Color = Vec4(0.5f, 0.f, 0.5f, 1.f);
		center.v2UV = Vec2(0.5f, 0.5f);
		vecCircle.push_back(center);

		// 원 둘레
		Vtx		temp;
		int32	iSlice = 100;
		float	fTheta = 0.f;
		float	fRadius = 0.5f;

		for (size_t i = 0; i < iSlice; ++i)
		{
			fTheta = (XM_2PI / iSlice) * i;
			
			temp.v3Pos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
			temp.v4Color = Vec4(0.f, 0.5f, 0.5f, 1.f);
			temp.v2UV = Vec2(0.f, 0.f);

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

		m_pCircleMesh->Create(vecCircle.data(),
							(uint32)vecCircle.size(), 
							vecIdx.data(), 
							(uint32)vecIdx.size());
	}
}

void CEngine::Test_render()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->Render();
	}
}

void CEngine::Test_GameObject()
{
	// Rect
	{
		CGameObject* obj = new CGameObject;

		obj->AddComponent(new CTransform);
		obj->AddComponent(new CMeshRender);

		obj->Transform()->SetRelativePos(Vec3(-0.5f, 0.f, 0.f));
		obj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		obj->MeshRender()->SetMesh(m_pRectMesh);
		obj->MeshRender()->SetGraphicShader(m_pShader);

		m_vecObj.push_back(obj);
	}

	// Circle
	{
		CGameObject* obj = new CGameObject;

		obj->AddComponent(new CTransform);
		obj->AddComponent(new CMeshRender);

		obj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
		obj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		obj->MeshRender()->SetMesh(m_pCircleMesh);
		obj->MeshRender()->SetGraphicShader(m_pShader);

		m_vecObj.push_back(obj);
	}

}
