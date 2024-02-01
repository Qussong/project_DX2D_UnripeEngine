#include "pch.h"
#include "func.h"

void GamePlayStatic::SpawnGameObject(CGameObject* _target, LAYER_TYPE _layerType)
{
	// UINT_PTR :
	// - 32bit : unsigned int
	// - 64bit : unsigned __int64

	// DWORD_PTR : 
	//	- 32bit : unsigned long
	//	- 64bit : unsigned __int64

	tTask task = {};
	task.eType = TASK_TYPE::ADD_OBJET;
	task.iParam1 = (DWORD_PTR)_target; 
	task.iParam2 = (DWORD_PTR)_layerType;

	M_TASK->AddTask(task);
}

void GamePlayStatic::DestroyGameObject(CGameObject* _target)
{
	tTask task = {};
	task.eType = TASK_TYPE::SUB_OBJECT;
	task.iParam1 = (DWORD_PTR)_target;
	task.iParam2 = (DWORD_PTR)NULL;

	M_TASK->AddTask(task);
}

void GamePlayStatic::DrawDebugRect(const Matrix& _worldMat, Vec3 _color, bool _depthTest, float _duration)
{
	tDebugShapeInfo info = {};
	{
		info.eShape = DEBUG_SHAPE::RECT;
		info.v3Color = _color;
		info.matWorld = _worldMat;
		info.fDuration = _depthTest;
		info.bDepthTest = _duration;
	}

	M_RENDER->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugRect(Vec3 _worldPos, Vec3 _worldScale, Vec3 _worldRot, Vec3 _color, bool _depthTest, float _duration)
{
	tDebugShapeInfo info = {};
	{
		info.eShape = DEBUG_SHAPE::RECT;
		info.v3Color = _color;
		info.v3WorldPos = _worldPos;
		info.v3WorldScale = _worldScale;
		info.v3WorldRot = _worldRot;
		info.matWorld = 
			XMMatrixScaling(info.v3WorldScale.x, info.v3WorldScale.y, info.v3WorldScale.z)
			* XMMatrixRotationX(info.v3WorldRot.x) * XMMatrixRotationY(info.v3WorldRot.y) * XMMatrixRotationZ(info.v3WorldRot.z)
			* XMMatrixTranslation(info.v3WorldPos.x, info.v3WorldPos.y, info.v3WorldPos.z);
		info.fDuration = _depthTest;
		info.bDepthTest = _duration;
	}

	M_RENDER->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugCircle(Vec3 _worldPos, float _radius, Vec3 _color, bool _depthTest, float _duration)
{
	tDebugShapeInfo info = {};
	{
		info.eShape = DEBUG_SHAPE::CIRCLE;
		info.v3Color = _color;
		info.v3WorldPos = _worldPos;
		info.v3WorldScale = Vec3(_radius, _radius, 1.f);
		info.v3WorldRot = Vec3(0.f, 0.f, 0.f);
		info.matWorld = 
			XMMatrixScaling(info.v3WorldScale.x, info.v3WorldScale.y, info.v3WorldScale.z)
			* XMMatrixRotationX(info.v3WorldRot.x) * XMMatrixRotationY(info.v3WorldRot.y) * XMMatrixRotationZ(info.v3WorldRot.z)
			* XMMatrixTranslation(info.v3WorldPos.x, info.v3WorldPos.y, info.v3WorldPos.z);
		info.fDuration = _depthTest;
		info.bDepthTest = _duration;
	}

	M_RENDER->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugCircle(const Matrix& _worldMat, Vec3 _color, bool _depthTest, float _duration)
{
	tDebugShapeInfo info = {};
	{
		info.eShape = DEBUG_SHAPE::CIRCLE;
		info.v3Color = _color;
		info.matWorld = _worldMat;
		info.fDuration = _depthTest;
		info.bDepthTest = _duration;
	}

	M_RENDER->AddDebugShapeInfo(info);
}

template<typename T>
void Lazy::DelVector(vector<T>&_vec)
{
	size_t length = _vec.size();
	for (size_t i = 0; i < length; i++)
	{
		if (nullptr == _vec[i])
			return;
		delete _vec[i];
	}
}