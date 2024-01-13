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
	// 정점 정보 입력
	{
		// 사각형 정점 위치 설정
		// 0(R)--- 1(B)	     
		//  |   \   |	     
		// 3(G)--- 2(M)  

		m_arrRect[0].vPos = Vec3{ -0.5f, 0.5f, 0.f };
		m_arrRect[0].vColor = Vec4{ 1.f, 0.f, 0.f, 1.f };
		m_arrRect[0].vUV = Vec2{ 0.f, 0.f };

		m_arrRect[1].vPos = Vec3{ 0.5f, 0.5f, 0.f };
		m_arrRect[1].vColor = Vec4{ 0.f, 0.f, 1.f, 1.f };
		m_arrRect[1].vUV = Vec2{ 0.f, 0.f };

		m_arrRect[2].vPos = Vec3{ 0.5f, -0.5f, 0.f };
		m_arrRect[2].vColor = Vec4{ 1.f, 0.f, 1.f, 1.f };
		m_arrRect[2].vUV = Vec2{ 0.f, 0.f };

		m_arrRect[3].vPos = Vec3{ -0.5f, -0.5f, 0.f };
		m_arrRect[3].vColor = Vec4{ 0.f, 1.f, 0.f, 1.f };
		m_arrRect[3].vUV = Vec2{ 0.f, 0.f };
	}

	// 인덱스 정보 입력
	{
		m_arrIdx[0] = 0;
		m_arrIdx[1] = 1;
		m_arrIdx[2] = 2;

		m_arrIdx[3] = 0;
		m_arrIdx[4] = 2;
		m_arrIdx[5] = 3;
	}

	// Vertex Buffer & Index Buffer 생성
	m_RectMesh = new CMesh();
	m_RectMesh->Create(m_arrRect, 4, m_arrIdx, 6);

	// Vertex Shader 생성
	{
		wstring path = CPathMgr::GetInst()->GetShaderPath();
		path.append(L"std2d.fx");

		const char function[] = "VS_Std2D";
		const char version[] = "vs_5_0";

		// hlsl 의 VS 컴파일
		HRESULT hr = D3DCompileFromFile(
			path.c_str(), 
			nullptr, 
			D3D_COMPILE_STANDARD_FILE_INCLUDE, 
			function,
			version,
			D3DCOMPILE_DEBUG, 
			0, 
			m_VSBlob.GetAddressOf(),
			m_ErrBlob.GetAddressOf());
		
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Vertex Shader Copile Failed", "VertexShader Error", MB_OK);
			_exit(EXIT_FAILURE);
		}

		// VS 생성
		hr = DEVICE->CreateVertexShader(
			m_VSBlob->GetBufferPointer(),
			m_VSBlob->GetBufferSize(),
			nullptr, 
			m_VS.GetAddressOf());

		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Vertex Shader Create Failed", "VertexShader Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// Layout
	{
		//	float3 vPos		: POS;
		//	float4 vColor	: COLOR;
		//	float2 vUV		: TEXCOORD;

		const int32 elementCnt = 3;
		D3D11_INPUT_ELEMENT_DESC descVtx[elementCnt] = {};
		{
			descVtx[0].SemanticName = "POS";
			descVtx[0].SemanticIndex = 0;
			descVtx[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			descVtx[0].InputSlot = 0;
			descVtx[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;// 0;
			descVtx[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			descVtx[0].InstanceDataStepRate = 0;

			descVtx[1].SemanticName = "COLOR";
			descVtx[1].SemanticIndex = 0;
			descVtx[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			descVtx[1].InputSlot = 0;
			descVtx[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;// 12;
			descVtx[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			descVtx[1].InstanceDataStepRate = 0;

			descVtx[2].SemanticName = "TEXCOORD";
			descVtx[2].SemanticIndex = 0;
			descVtx[2].Format = DXGI_FORMAT_R32G32_FLOAT;
			descVtx[2].InputSlot = 0;
			descVtx[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;// 28;
			descVtx[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			descVtx[2].InstanceDataStepRate = 0;
		}

		HRESULT hr = DEVICE->CreateInputLayout(
			descVtx,
			elementCnt,
			m_VSBlob->GetBufferPointer(),
			m_VSBlob->GetBufferSize(),
			m_Layout.GetAddressOf());

		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "InputLayout Create Failed", "InputLayout Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// Pixel Shader 생성
	{
		wstring path = CPathMgr::GetInst()->GetShaderPath();
		path.append(L"std2d.fx");

		const char function[] = "PS_Std2D";
		const char version[] = "ps_5_0";

		HRESULT hr = D3DCompileFromFile(
			path.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			function,
			version,
			D3DCOMPILE_DEBUG,
			0,
			m_PSBlob.GetAddressOf(),
			m_ErrBlob.GetAddressOf());

		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Pixel Shader Compile Failed", "PixelShader Error", MB_OK);
			_exit(EXIT_FAILURE);
		}

		DEVICE->CreatePixelShader(
			m_PSBlob->GetBufferPointer(),
			m_PSBlob->GetBufferSize(),
			nullptr,
			m_PS.GetAddressOf());

		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Pixel Shader Create Failed", "PixelShader Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// Constant Buffer 생성
	{
		UINT elementSize = sizeof(tTransform);
		UINT elementCnt = sizeof(tTransform) / sizeof(tTransform);

		D3D11_BUFFER_DESC desc = {};
		{
			desc.ByteWidth = elementSize * elementCnt;
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = elementSize;
		}

		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = &m_tTransform;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &tSubData, m_CB.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Constant Buffer Create Failed", "Constant Buffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
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
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &m_tTransform, sizeof(tTransform) * 1);
	CONTEXT->Unmap(m_CB.Get(), 0);
	CONTEXT->VSSetConstantBuffers(0, 1, m_CB.GetAddressOf());
}

void CEngine::Test_render()
{
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CONTEXT->IASetInputLayout(m_Layout.Get());

	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);

	m_RectMesh->Render();
}