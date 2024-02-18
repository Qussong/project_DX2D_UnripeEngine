#include "pch.h"
#include "CComputeShader.h"

CComputeShader::CComputeShader(UINT _threadX, UINT _threadY, UINT _threadZ)
	: Super(ASSET_TYPE::COMPUTE_SHADER)
	, m_iGroupX(1)
	, m_iGroupY(1)
	, m_iGroupZ(1)
	, m_iThreadX(_threadX)
	, m_iThreadY(_threadY)
	, m_iThreadZ(_threadZ)
	, m_tMtrlConst{}
{
}

CComputeShader::~CComputeShader()
{
}

int CComputeShader::Create(const wstring& _wstrRelativePath, const string& _strFuncName, const string& _version)
{
	wstring strShaderFolderPath = M_PATH->GetShaderPath();
	wstring strShaderFilePath = strShaderFolderPath + _wstrRelativePath;

	// Create PixelShader 
	HRESULT hr = D3DCompileFromFile(
		strShaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_strFuncName.c_str(),
		_version.c_str(),
		D3DCOMPILE_DEBUG,
		0,
		m_CSBlob.GetAddressOf(),
		m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != m_ErrBlob)
		{
			char* pErrMsg = (char*)m_ErrBlob->GetBufferPointer();
			MessageBoxA(nullptr, pErrMsg, "CComputeShader Error", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, "Create PixelShader Failed", "CComputeShader Error", MB_OK);
		}

		return E_FAIL;
	}

	// Compile PixelShader
	DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer(),
								m_CSBlob->GetBufferSize(),
								nullptr,
								m_CS.GetAddressOf());

	return S_OK;
}

void CComputeShader::Execute()
{
	if (FAILED(UpdateData()))
		return;

	// 상수 데이터 바인딩
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::MATERIAL);
	pCB->SetData(&m_tMtrlConst);
	pCB->UpdateData_CS();

	// ComputeShader Execute
	CONTEXT->CSSetShader(m_CS.Get(), 0, 0);
	CONTEXT->Dispatch(m_iGroupX, m_iGroupY, m_iGroupZ);

	Clear();
}