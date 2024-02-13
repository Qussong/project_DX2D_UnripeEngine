#pragma once

class CGameObject;

namespace Lazy
{
	template <typename T>
	void DelVector(vector<T>& _vec);

	template <typename T1, typename T2>
	void DelMap(map<T1, T2>& _map);

	template<typename T, UINT SIZE>
	void DelArray(T* (&Arr)[SIZE]);
}

namespace GamePlayStatic
{
	void SpawnGameObject(CGameObject* _target, LAYER_TYPE _layerType);
	void DestroyGameObject(CGameObject* _target);

	void DrawDebugRect(const Matrix& _worldMat, Vec3 _color, bool _depthTest = false, float _duration = 0.f);
	void DrawDebugRect(Vec3 _worldPos, Vec3 _worldScale, Vec3 _worldRot, Vec3 _color, bool _depthTest = false, float _duration = 0.f);

	void DrawDebugCircle(Vec3 _worldPos, float _radius, Vec3 _color, bool _depthTest = false, float _duration = 0.f);
	void DrawDebugCircle(const Matrix& _worldMat, Vec3 _color, bool _depthTest = false, float _duration = 0.f);

	void DrawDebugCross(Vec3 _worldPos, float _scale, Vec3 _color, bool _depthTest = false, float _duration = 0.f);

	//void DrawDebugCube();
	//void DrawDebugSphere();
}

template<typename T>
void Lazy::DelVector(vector<T>& _vec)
{
	size_t length = _vec.size();
	for (size_t i = 0; i < length; i++)
	{
		if (nullptr == _vec[i])
			return;
		delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Lazy::DelMap(map<T1, T2>& _map)
{
	for (auto& pair : _map)
	{
		delete pair.second;
	}
	_map.clear();
}

template<typename T, UINT SIZE>
void Lazy::DelArray(T* (&Arr)[SIZE])
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