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
	Vec3	v3Pos;
	Vec4	v4Color;
	Vec2	v2UV;
};

// 상수버퍼 대응 구조체 (16 Byte 단위)
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
};