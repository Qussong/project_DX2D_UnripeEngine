#pragma once

class CPathMgr
	: public CSingleton<CPathMgr>
{
	SINGLETON(CPathMgr);

private:
	wchar_t m_rootPath[255];
	wchar_t m_resourcePath[255];
	wchar_t m_shaderPath[255];

public:
	void Init();
	const wchar_t* GetResourcetPath() { return m_resourcePath; }
	const wchar_t* GetShaderPath() { return m_shaderPath; }
};

