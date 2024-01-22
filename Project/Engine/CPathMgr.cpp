#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_rootPath{}
	, m_resourcePath{}
	, m_shaderPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	// 실행파일 경로
	GetCurrentDirectory(255, m_rootPath);

	size_t Len = wcslen(m_rootPath);

	int goalCnt = 0;	// 목표지점 카운트
	for (size_t i = Len - 1; i >= 0; --i)
	{
		if ('\\' == m_rootPath[i])
		{
			++goalCnt;
			if (2 == goalCnt)
			{
				m_rootPath[i + 1] = '\0';
				break;
			}
		}
	}

	// root path = "~\project_DX2D_UnripeEngine\"
	wcscpy_s(m_resourcePath, m_rootPath);
	wcscpy_s(m_shaderPath, m_rootPath);
	
	wcscat_s(m_resourcePath, 255, L"External\\Resource\\");
	wcscat_s(m_shaderPath, 255, L"Project\\Shader\\");
}
