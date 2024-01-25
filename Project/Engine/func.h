#pragma once

class CGameObject;

namespace Lazy
{
	void DelVector(vector<CEntity>& _vec);
}

namespace GamePlayStatic
{
	void SpawnGameObject(CGameObject* _target, LAYER_TYPE _layerType);
	void DestroyGameObject(CGameObject* _target);
}

template<typename T, UINT SIZE>
void Delete_Array(T* (&Arr)[SIZE])
{
	for (int i = i = 0; i < SIZE; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}

template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}