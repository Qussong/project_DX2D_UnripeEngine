#pragma once

class CPathMgr
	: public CSingleton<CPathMgr>
{
	SINGLETON(CPathMgr);

private:
	wchar_t m_contentPath[255];

public:
	void Init();
	const wchar_t* GetContentPath() { return m_contentPath; }

};

