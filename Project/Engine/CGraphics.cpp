#include "pch.h"
#include "CGraphics.h"

CGraphics::CGraphics()
	: m_hWnd(nullptr)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_arrClearColor{}
	, m_bStandByMode(false)
	, m_arrCB{}
{
}

CGraphics::~CGraphics()
{
}

int CGraphics::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	m_hWnd = _hWnd;
	m_iWidth = _width;
	m_iHeight = _height;

	SetWindow();

	DeviceAndSwapChain();
	RenderTargetView();
	DepthStencilView();
	CostantBuffer();

	return S_OK;
}

void CGraphics::RenderBegin()
{
	// test
	TestKey();

	CONTEXT->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	CONTEXT->ClearRenderTargetView(m_RenderTargetView.Get(), m_arrClearColor);		// 렌더 타겟 클리어 (clearColor)
	CONTEXT->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, (UINT8)0);
	
	D3D11_VIEWPORT	viewport = {};
	{
		viewport.TopLeftX = 0.f;
		viewport.TopLeftY = 0.f;
		viewport.Width = (FLOAT)m_iWidth;
		viewport.Height = (FLOAT)m_iHeight;
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
	RECT rt = { 0, 0, (LONG)m_iWidth, (LONG)m_iHeight };
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
		desc.BufferDesc.Width = m_iWidth;
		desc.BufferDesc.Height = m_iHeight;
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
		desc.Width = m_iWidth;
		desc.Height = m_iHeight;
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
	CConstantBuffer* buffer = new CConstantBuffer;
	buffer->Create(sizeof(tTransform), 1);
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = buffer;

}

// ClearColor 변경
void CGraphics::TestKey()
{
	if (KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_arrClearColor[i] >= 1.f ? m_arrClearColor[i] = 1.f : m_arrClearColor[i] += 0.1f;
		}

		cout << "R " << (int)(m_arrClearColor[0] * 255)
			 << "/G " << (int)(m_arrClearColor[1] * 255)
			 << "/G " << (int)(m_arrClearColor[2] * 255) << endl;
	}

	if (KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_arrClearColor[i] <= 0.f ? m_arrClearColor[i] = 0.f : m_arrClearColor[i] -= 0.1f;
		}

		cout << "R " << (int)(m_arrClearColor[0] * 255)
			 << "/G " << (int)(m_arrClearColor[1] * 255)
			 << "/G " << (int)(m_arrClearColor[2] * 255) << endl;
	}
}
