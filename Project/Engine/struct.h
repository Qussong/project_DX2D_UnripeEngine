#pragma once

#include "enum.h"

struct KeyData
{
	KEY			eKey;		// key ����
	KEY_STATE	eState;		// key ����
	bool		bPressed;
};

// ���� ����ü
struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};

// ������� ����ü
struct Transform
{
	Vec4 vWorldScale;
	Vec4 vWorldPos;
};