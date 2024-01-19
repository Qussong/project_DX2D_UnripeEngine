#include "pch.h"
#include "CGraphics.h"

CGraphics::CGraphics()
	: m_hWnd(nullptr)
	, m_v2Resolution{}
	, m_arrClearColor{}
	, m_bStandByMode(false)
	, m_arrCB{}
	, m_arrRS{}
	, m_arrDS{}
	, m_arrBS{}
{
}

CGraphics::~CGraphics()
{
	uint32 size = (uint32)CB_TYPE::END;
	for (size_t i = 0; i < size; i++)
	{
		if (nullptr != m_arrCB[i])
		{
			delete m_arrCB[i];
			m_arrCB[i] = nullptr;
		}
	}
}

int CGraphics::Init(HWND _hWnd, float _width, float _height)
{
	m_hWnd = _hWnd;
	m_v2Resolution.x = _width;
	m_v2Resolution.y = _height;

	SetWindow();

	DeviceAndSwapChain();
	RenderTargetView();
	DepthStencilView();
	CostantBuffer();
	
	if (FAILED(RasterizerState()))
	{
		MessageBoxA(nullptr, "Rasterizer State Create Failed", "Rasterizer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	if (FAILED(DepthStencilState()))
	{
		MessageBoxA(nullptr, "DepthStencil State Create Failed", "DepthStencil Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	if (FAILED(BlendState()))
	{
		MessageBoxA(nullptr, "Blend State Create Failed", "Blend Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	return S_OK;
}

void CGraphics::RenderBegin()
{
	CONTEXT->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	CONTEXT->ClearRenderTargetView(m_RenderTargetView.Get(), m_arrClearColor);		// 렌더 타겟 클리어 (clearColor)
	CONTEXT->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, (UINT8)0);
	
	D3D11_VIEWPORT	viewport = {};
	{
		viewport.TopLeftX = 0.f;
		viewport.TopLeftY = 0.f;
		viewport.Width = m_v2Resolution.x;
		viewport.Height = m_v2Resolution.y;
		viewport.MinDepth = 0.f;
		viewport.MaxDepth = 1.f;
	}
	CONTEXT->RSSetViewports(1, &viewport);
}

void CGraphics::RenderEnd()
{
	// window 최소화 o
	if (m_bStandByMode)
	{
		HRESULT hr = SWAPCHAIN->Present(0, DXGI_PRESENT_TEST);

		if (DXGI_STATUS_OCCLUDED == hr)
			return;
		else
			m_bStandByMode = false;
	}

	// window 최소화 x
	else
	{
		HRESULT hr = SWAPCHAIN->Present(0, 0);

		// StanbyMode Check
		if (hr == DXGI_STATUS_OCCLUDED)
			m_bStandByMode = true;
	}
}

void CGraphics::SetWindow()
{
	RECT rt = { 0, 0, (LONG)m_v2Resolution.x, (LONG)m_v2Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	int resizeWindowWidth = rt.right - rt.left;
	int resizeWindowHeight = rt.bottom - rt.top;
	int centerPosLeft = (MONITOR_SIZE_WIDTH - resizeWindowWidth) / 2;
	int centerPosTop = (MONITOR_SIZE_HEIGHT - resizeWindowHeight) / 2;

	SetWindowPos(m_hWnd, nullptr, centerPosLeft, centerPosTop, resizeWindowWidth, resizeWindowHeight, SWP_NOZORDER);
}

void CGraphics::DeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	{
		desc.BufferDesc.Width = static_cast<UINT>(m_v2Resolution.x);
		desc.BufferDesc.Height = static_cast<UINT>(m_v2Resolution.y);
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = m_hWnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		// Device
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		// SwapChain
		&desc,
		// Result
		m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Device Init Failed", "Device Error", MB_OK);
		_exit(EXIT_FAILURE);
	}
}

void CGraphics::RenderTargetView()
{
	ComPtr<ID3D11Texture2D> renderTarget;	// = back buffer

	// render target texture
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)renderTarget.GetAddressOf());
	// render target view
	HRESULT hr = m_Device->CreateRenderTargetView(renderTarget.Get(), nullptr, m_RenderTargetView.GetAddressOf());
	
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Render Target View Create Failed", "RenderTarget Error", MB_OK);
		_exit(EXIT_FAILURE);
	}
}

void CGraphics::DepthStencilView()
{
	ComPtr<ID3D11Texture2D> depthStencil;

	D3D11_TEXTURE2D_DESC desc = {};
	{
		desc.Width = static_cast<UINT>(m_v2Resolution.x);
		desc.Height = static_cast<UINT>(m_v2Resolution.y);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;	// GPU 읽기, 쓰기
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
	}

	DEVICE->CreateTexture2D(&desc, nullptr, depthStencil.GetAddressOf());
	HRESULT hr = DEVICE->CreateDepthStencilView(depthStencil.Get(), nullptr, m_DepthStencilView.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Depth-Stencil View Create Failed", "DepthStendcil Error", MB_OK);
		_exit(EXIT_FAILURE);
	}
}

void CGraphics::CostantBuffer()
{
	// Transform
	{
		CConstantBuffer* pCB = new CConstantBuffer;
		pCB->Create(sizeof(tTransform), 1);
		m_arrCB[(UINT)CB_TYPE::TRANSFORM] = pCB;
	}
}

int CGraphics::RasterizerState()
{
	//	CULL_BACK	0
	//	CULL_FRONT	1
	//	CULL_NONE	2
	//	WIRE_FRAME	3

	HRESULT hr = S_OK;	// ↔ E_FAIl
	D3D11_RASTERIZER_DESC desc = {};

	// CULL_BACK 은 기본값이기에 따로 생성할 필요가 없다.
	m_arrRS[(uint32)RS_TYPE::CULL_BACK] = nullptr;

	m_arrRS[(uint32)RS_TYPE::CULL_FRONT] = nullptr;
	{
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_FRONT;
		//desc.FrontCounterClockwise;
		//desc.DepthBias;
		//desc.DepthBiasClamp;
		//desc.SlopeScaledDepthBias;
		//desc.DepthClipEnable;
		//desc.ScissorEnable;
		//desc.MultisampleEnable;
		//desc.AntialiasedLineEnable;
	}
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(uint32)RS_TYPE::CULL_FRONT].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrRS[(uint32)RS_TYPE::CULL_NONE] = nullptr;
	{
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
	}
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(uint32)RS_TYPE::CULL_NONE].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrRS[(uint32)RS_TYPE::WIRE_FRAME] = nullptr;
	{
		desc.FillMode = D3D11_FILL_WIREFRAME;
		desc.CullMode = D3D11_CULL_NONE;
	}
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(uint32)RS_TYPE::WIRE_FRAME].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	return hr;
}

int CGraphics::DepthStencilState()
{
	// LESS				0
	// LESS_EQUAL		1
	// GRATER			2
	// GRATER_EQUAL		3
	// NO_TEST			4
	// NO_WRITE			5
	// NO_TEST_NO_WRITE	6	

	HRESULT hr = S_OK;	// ↔ E_FAIl
	D3D11_DEPTH_STENCIL_DESC desc = {};

	// LESS 는 기본값이기에 따로 생성할 필요가 없다.
	m_arrDS[(uint32)DS_TYPE::LESS] = nullptr;

	m_arrDS[(uint32)DS_TYPE::LESS_EQUAL] = nullptr;
	{
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		desc.StencilEnable = false;
		//desc.StencilReadMask;
		//desc.StencilWriteMask;
		//desc.FrontFace;
		//desc.BackFace;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::LESS_EQUAL].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrDS[(uint32)DS_TYPE::GRATER] = nullptr;
	{
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_GREATER;
		desc.StencilEnable = false;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::GRATER].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrDS[(uint32)DS_TYPE::GRATER_EQUAL] = nullptr;
	{
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		desc.StencilEnable = false;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::GRATER_EQUAL].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrDS[(uint32)DS_TYPE::NO_TEST] = nullptr;
	{
		desc.DepthEnable = false;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_NEVER;
		desc.StencilEnable = false;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::NO_TEST].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrDS[(uint32)DS_TYPE::NO_WRITE] = nullptr;
	{
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS;
		desc.StencilEnable = false;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::NO_WRITE].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	m_arrDS[(uint32)DS_TYPE::NO_TEST_NO_WRITE] = nullptr;
	{
		desc.DepthEnable = false;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_NEVER;
		desc.StencilEnable = false;
	}
	hr = DEVICE->CreateDepthStencilState(&desc, m_arrDS[(uint32)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());
	if (FAILED(hr)) return E_FAIL;

	return hr;
}

int CGraphics::BlendState()
{
	// DEFAULT		0
	// ALPHA_BLEND	1
	// ONE_ONE		2

	HRESULT hr = S_OK;	// ↔ E_FAIl
	D3D11_BLEND_DESC desc = {};

	// DEFAULT 는 기본값이기에 따로 생성할 필요가 없다.
	m_arrBS[(uint32)BS_TYPE::DEFAULT] = nullptr;

	m_arrBS[(uint32)BS_TYPE::ALPHA_BLEND] = nullptr;
	{
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = true;

		// D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	hr = DEVICE->CreateBlendState(&desc, m_arrBS[(uint32)BS_TYPE::ALPHA_BLEND].GetAddressOf());
	if (FAILED(hr)) { return E_FAIL; }

	m_arrBS[(uint32)BS_TYPE::ONE_ONE] = nullptr;

	return hr;
}
