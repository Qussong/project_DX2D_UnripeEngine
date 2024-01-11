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
	// �������� ���
	GetCurrentDirectory(255, m_contentPath);

	size_t Len = wcslen(m_contentPath);

	int goalCnt = 0;	// ��ǥ���� ī��Ʈ
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

	// ���ҽ� ���
	wcscat_s(m_contentPath, 255, L"External\\Resource\\");	
}
