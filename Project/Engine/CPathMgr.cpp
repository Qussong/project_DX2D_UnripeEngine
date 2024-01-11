#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_contentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	// 실행파일 경로
	GetCurrentDirectory(255, m_contentPath);

	size_t Len = wcslen(m_contentPath);

	int goalCnt = 0;	// 목표지점 카운트
	for (size_t i = Len - 1; i >= 0; --i)
	{
		if ('\\' == m_contentPath[i])
		{
			++goalCnt;
			if (2 == goalCnt)
			{
				m_contentPath[i + 1] = '\0';
				break;
			}
		}
	}

	// 리소스 경로
	wcscat_s(m_contentPath, 255, L"External\\Resource\\");	
}
