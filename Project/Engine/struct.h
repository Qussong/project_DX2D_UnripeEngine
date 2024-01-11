#pragma once

#include "enum.h"

struct KeyData
{
	KEY			eKey;		// key 종류
	KEY_STATE	eState;		// key 상태
	bool		bPressed;
};

struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};