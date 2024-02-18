#pragma once

//class CShader;
#include "CShader.h"

class CComputeShader
	: public CShader
{
	using Super = CShader;

public:
	CComputeShader(UINT _threadX, UINT _threadY, UINT _threadZ);
	virtual ~CComputeShader();

private:
	ComPtr<ID3DBlob>			m_CSBlob;
	ComPtr<ID3D11ComputeShader> m_CS;

	// 그룹 개수
	UINT			m_iGroupX;
	UINT			m_iGroupY;
	UINT			m_iGroupZ;

protected:
	// 스레드 개수
	const UINT		m_iThreadX;
	const UINT		m_iThreadY;
	const UINT		m_iThreadZ;

protected:
	tMaterial		m_tMtrlConst;

public:
	// Getter
	UINT GetGroupX() { return m_iGroupX; }
	UINT GetGroupY() { return m_iGroupY; }
	UINT GetGroupZ() { return m_iGroupZ; }

	// Setter
	void SetGroupX(UINT _groupCnt) { m_iGroupX = _groupCnt; }
	void SetGroupY(UINT _groupCnt) { m_iGroupY = _groupCnt; }
	void SetGroupZ(UINT _groupCnt) { m_iGroupZ = _groupCnt; }

public:
	int		Create(const wstring& _wstrRelativePath, const string& _strFuncName, const string& _version = "cs_5_0");
	void	Execute();

private:
	virtual int UpdateData() = 0;
	virtual void Clear() = 0;
};

