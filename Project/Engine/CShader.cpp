#include "pch.h"
#include "CShader.h"

CShader::CShader(ASSET_TYPE _type)
	: Super(_type)
{
	SetName(L"Shader");
}

CShader::~CShader()
{
}
