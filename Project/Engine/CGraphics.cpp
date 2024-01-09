#include "pch.h"
#include "CGraphics.h"

CGraphics::CGraphics()
	: m_hWnd(nullptr)
	, m_width(0)
	, m_height(0)
	, m_bStandByMode(false)
	, m_viewport{}
{

}

CGraphics::~CGraphics()
{

}

int CGraphics::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	m_hWnd = _hWnd;
	m_width = _width;
	m_height = _height;

	RECT rt = { 0, 0, (LONG)m_width, (LONG)m_height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	int resizeWindowWidth = rt.right - rt.left;
	int resizeWindowHeight = rt.bottom - rt.top;
	int centerPosLeft = (MONITOR_SIZE_WIDTH - resizeWindowWidth) / 2;
	int centerPosTop = (MONITOR_SIZE_HEIGHT - resizeWindowHeight) / 2;
	SetWindowPos(m_hWnd, nullptr, centerPosLeft, centerPosTop, resizeWindowWidth, resizeWindowHeight, SWP_NOZORDER);

	DeviceAndSwapChain();
	RenderTargetView();
	SetViewport();

	return S_OK;
}

void CGraphics::RenderBegin()
{
	float clearColor[4] = { 1.f, 0.f, 0.f, 1.f };
	m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);	// ·»´õ Å¸°Ù ¼³Á¤
	m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);			// ·»´õ Å¸°Ù Å¬¸®¾î (clearColor)
	m_context->RSSetViewports(1, &m_viewport);
}

void CGraphics::RenderEnd()
{
	HRESULT hr = NULL;

	if (!m_bStandByMode)
	{
		hr = m_swapChain->Present(1, 0);
		assert(SUCCEEDED(hr));

		// StanbyMode Check
		if (hr == DXGI_STATUS_OCCLUDED)
			m_bStandByMode = true;
	}
	else
	{
		hr = m_swapChain->Present(0, DXGI_PRESENT_TEST);
		if (DXGI_STATUS_OCCLUDED == hr)
			return;
		else
			m_bStandByMode = false;
	}
}

void CGraphics::DeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	{
		desc.BufferDesc.Width = m_width;
		desc.BufferDesc.Height = m_height;
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
		m_swapChain.GetAddressOf(), m_device.GetAddressOf(), nullptr, m_context.GetAddressOf());

	assert(SUCCEEDED(hr));
}

void CGraphics::RenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer;

	// backBuffer
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// renderTargetVier (backBuffer)
	hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void CGraphics::SetViewport()
{
	m_viewport.TopLeftX = 0.f;
	m_viewport.TopLeftY = 0.f;
	m_viewport.Width = (FLOAT)m_width;
	m_viewport.Height = (FLOAT)m_height;
	m_viewport.MinDepth = 0.f;
	m_viewport.MaxDepth = 1.f;
}
