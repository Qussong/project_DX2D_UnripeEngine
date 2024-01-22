#include "pch.h"
#include "CGraphicShader.h"

CGraphicShader::CGraphicShader()
	: Super(ASSET_TYPE::GRAPHIC_SHADER)
	, m_Topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_eRSType(RS_TYPE::CULL_BACK)
	, m_eDSType(DS_TYPE::LESS)
	, m_eBSType(BS_TYPE::DEFAULT)
{
	SetName(L"GraphicShader");
}

CGraphicShader::~CGraphicShader()
{
}

void CGraphicShader::UpdateData()
{
	CONTEXT->IASetInputLayout(m_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(m_Topology);

	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);
	// + Hull Shader
	// + Domain Shader
	// + Geometry Shader

	CONTEXT->RSSetState(GRAPHICS->GetRSState(m_eRSType).Get());
	CONTEXT->OMSetDepthStencilState(GRAPHICS->GetDSState(m_eDSType).Get(), 0);
	CONTEXT->OMSetBlendState(GRAPHICS->GetBSState(m_eBSType).Get(), nullptr, 0xffffffff);
}

void CGraphicShader::Layout()
{
	// Vtx 备炼眉 备己
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

void CGraphicShader::VertexShader(const wstring& _fileName, const string& _function, const string& _version)
{
	wstring shaderFilePath = M_PATH->GetShaderPath() + _fileName;

	// hlsl 狼 VS 哪颇老
	HRESULT hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_function.c_str(),
		_version.c_str(),
		D3DCOMPILE_DEBUG,
		0,
		m_VSBlob.GetAddressOf(),
		m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Vertex Shader Copile Failed", "VertexShader Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// Layout 积己
	Layout();

	// VS 积己
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

void CGraphicShader::PixelShader(const wstring& _fileName, const string& _function, const string& _version)
{
	wstring shaderFilePath = M_PATH->GetShaderPath() + _fileName;

	HRESULT hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_function.c_str(),
		_version.c_str(),
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
