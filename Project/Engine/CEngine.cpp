#include "pch.h"
#include "CEngine.h"

#include "CGraphics.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_width(0)
	, m_height(0)

{
}

CEngine::~CEngine()
{
}

int CEngine::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	// member init
	m_hWnd = _hWnd;
	m_width = _width;
	m_height = _height;

	// Device, Context, SwapChain init
	CGraphics::GetInst()->Init(m_hWnd, m_width, m_height);

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

	//render
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
	// ���� ���� �Է�
	{
		// �簢�� ���� ��ġ ����
		// 0(R)--- 1(B)	     
		//  |   \   |	     
		// 3(G)--- 2(M)  

		m_rectangle[0].vPos = Vec3{ -0.5f, 0.5f, 0.f };
		m_rectangle[0].vColor = Vec4{ 1.f, 0.f, 0.f, 1.f };
		m_rectangle[0].vUV = Vec2{ 0.f, 0.f };

		m_rectangle[1].vPos = Vec3{ 0.5f, 0.5f, 0.f };
		m_rectangle[1].vColor = Vec4{ 0.f, 0.f, 1.f, 1.f };
		m_rectangle[1].vUV = Vec2{ 0.f, 0.f };

		m_rectangle[2].vPos = Vec3{ 0.5f, -0.5f, 0.f };
		m_rectangle[2].vColor = Vec4{ 1.f, 0.f, 1.f, 1.f };
		m_rectangle[2].vUV = Vec2{ 0.f, 0.f };

		m_rectangle[3].vPos = Vec3{ -0.5f, -0.5f, 0.f };
		m_rectangle[3].vColor = Vec4{ 0.f, 1.f, 0.f, 1.f };
		m_rectangle[3].vUV = Vec2{ 0.f, 0.f };
	}

	// Vertex Buffer ����
	{
		int32 typeSize = sizeof(Vtx);
		int32 cnt = sizeof(m_rectangle) / sizeof(Vtx);

		D3D11_BUFFER_DESC desc = {};	// ZeroMemory();
		{
			desc.ByteWidth = typeSize * cnt;
			desc.Usage = D3D11_USAGE_DYNAMIC;	// GPU �б�, CPU ����
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = typeSize;
		}

		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = m_rectangle;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &tSubData, m_VB.GetAddressOf());
		if(FAILED(hr))
		{
			MessageBoxA(nullptr, "Vertex Buffer Create Failed", "VertexBuffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// �ε��� ���� �Է�
	{
		m_idx[0] = 0;
		m_idx[1] = 1;
		m_idx[2] = 2;

		m_idx[3] = 0;
		m_idx[4] = 2;
		m_idx[5] = 3;
	}

	// Index Buffer ����
	{
		int32 typeSize = sizeof(UINT);
		int32 cnt = sizeof(m_idx) / sizeof(UINT);

		D3D11_BUFFER_DESC desc = {};
		{
			desc.ByteWidth = typeSize * cnt;
			desc.Usage = D3D11_USAGE_DEFAULT;	// GPU �б�, ����
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = typeSize;
		}

		// �ε��� ���ۿ� �� �������� �ʱ� �� ����
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = m_idx;

		// Index Buffer
		HRESULT hr = DEVICE->CreateBuffer(&desc, &tSubData, m_IB.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Index Buffer Create Failed", "Index Buffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// Vertex Shader ����
	{
		wstring path = CPathMgr::GetInst()->GetShaderPath();
		path.append(L"std2d.fx");

		const char function[] = "VS_Std2D";
		const char version[] = "vs_5_0";

		// hlsl �� VS ������
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

		// VS ����
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
		//	float3 vPos : POS;
		//	float4 vColor : COLOR;
		//	float2 vUV : TEXCOORD;

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

	// Pixel Shader ����
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
			//char* pErrMsg = (char*)m_ErrBlob->GetBufferPointer();
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

	// Constant Buffer ����
	{
		UINT elementSize = sizeof(cTransform);
		UINT elementCnt = sizeof(cTransform) / sizeof(cTransform);

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
		tSubData.pSysMem = &m_transform;

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
		m_transform.vWorldPos.x -= DT;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		m_transform.vWorldPos.x += DT;
	}

	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	memcpy(tSub.pData, &m_transform, sizeof(cTransform) * 1);

	CONTEXT->Unmap(m_CB.Get(), 0);
}

void CEngine::Test_render()
{
	UINT	elementSize = sizeof(Vtx);
	UINT	offset		= 0;
	uint32	idxCnt		= sizeof(m_idx) / sizeof(uint32);
	UINT	slotNum		= 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &elementSize, &offset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CONTEXT->IASetInputLayout(m_Layout.Get());
	CONTEXT->VSSetShader(m_VS.Get(), 0, 0);
	CONTEXT->PSSetShader(m_PS.Get(), 0, 0);
	CONTEXT->DrawIndexed(idxCnt, 0, 0);
	CONTEXT->VSSetConstantBuffers(slotNum, 1, m_CB.GetAddressOf());
}