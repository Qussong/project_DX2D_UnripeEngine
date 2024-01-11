#pragma once

#include "enum.h"

struct KeyData
{
	KEY			eKey;		// key ����
	KEY_STATE	eState;		// key ����
	bool		bPressed;
};

struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};