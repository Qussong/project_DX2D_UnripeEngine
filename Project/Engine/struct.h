#pragma once

#include "enum.h"

struct KeyData
{
	KEY			eKey;		// key 종류
	KEY_STATE	eState;		// key 상태
	bool		bPressed;
};

// 정점 구조체
struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};

// 상수버퍼 구조체
struct tTransform
{
	Vec4 vWorldPos;
	Vec4 vWorldScale;
};