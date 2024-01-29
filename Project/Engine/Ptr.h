#pragma once


template<typename T>
class Ptr
{
public:
	Ptr()
		: m_pAsset(nullptr)
	{}

	Ptr(T* _asset)
		: m_pAsset(_asset)
	{
		if (nullptr != m_pAsset)
			m_pAsset->AddRefCnt();
	}

	Ptr(const Ptr<T>& _other)
		: m_pAsset(_other.m_pAsset)
	{
		if (nullptr != m_pAsset)
			m_pAsset->AddRefCnt();
	}

	~Ptr()
	{
		if (nullptr != m_pAsset)
			m_pAsset->SubRefCnt();
	}

private:
	T* m_pAsset;

public:
	// 함수 선언의 const : 함수 내부에서 멤버변수(m_pAsset)의 변경 불가능
	// 리턴 자료형의 const : 외부에서 반환값
	T* Get() const { return m_pAsset; }
	T** GetAddress() const { return *m_pAsset; }
	T* operator->() const { return m_pAsset; }

public:
	void operator=(T* _asset)
	{
		if (nullptr != m_pAsset)
			m_pAsset->SubRefCnt();

		m_pAsset = _asset;

		if (nullptr != m_pAsset)
			m_pAsset->AddRefCnt();
	}

	void operator=(const Ptr<T>& _ptr)
	{
		if (nullptr != m_pAsset)
			m_pAsset->SubRefCnt();
		
		m_pAsset = _ptr.m_pAsset;

		if (nullptr != m_pAsset)
			m_pAsset->AddRefCnt();
	}

	bool operator==(const T* _other)
	{
		return (m_pAsset == _other);
	}

	bool operator!=(const T* _other)
	{
		return (m_pAsset != _other);
	}

	bool operator==(const Ptr<T>& _other)
	{
		return (m_pAsset == _other.m_pAsset);
	}

	bool operator!=(const Ptr<T>& _other)
	{
		return (m_pAsset != _other.m_pAsset);
	}
};

template <typename T>
bool operator==(const void* _asset, const Ptr<T>& _ptr)
{
	return (_asset == _ptr.Get());
}

template <typename T>
bool operator!=(const void* _asset, const Ptr<T>& _ptr)
{
	return (_asset != _ptr.Get());
}