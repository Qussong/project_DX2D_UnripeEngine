#pragma once

template <typename T>
class CSingleton
{
public:
	CSingleton()
	{
		typedef void(*FUNC_TYPE)(void);
		atexit((FUNC_TYPE)(&CSingleton::Destroy));
	}
	~CSingleton()
	{
	}

private:
	static T* m_this;

public:
	static T* GetInst()
	{
		if (nullptr == m_this)
			m_this = new T;
		return m_this;
	}

	static void Destroy()
	{
		if (nullptr != m_this)
		{
			delete m_this;
			m_this = nullptr;
		}
	}
};

template <typename T>
T* CSingleton<T>::m_this = nullptr;