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
	Vec3	v3Pos;
	Vec4	v4Color;
	Vec2	v2UV;
};

// ������� ����ü
struct tTransform
{
	Vec4 v4WorldPos;
	Vec4 v4WorldScale;
};