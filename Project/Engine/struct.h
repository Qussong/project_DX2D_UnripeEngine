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

// 상수버퍼(CB_TYPE::TRANSFORM) 대응 구조체 (16 Byte 단위)
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
};

// TaskMgr 클래스 전용 데이터
struct tTask
{
	TASK_TYPE	eType;
	UINT_PTR	iParam1;
	UINT_PTR	iParam2;

	// UINT_PTR : 
	// 자료형 자체가 포인터 타입이 아니라, 주로 포인터 연산을
	// 목적으로 활용되는 자료형이기 때문에 _PTR접미사가 붙는다.
};

// 상수버퍼(CB_TYPE::MATERIAL) 대응 구조체
struct tMaterial
{
	int32		iArr[4];
	float		fArr[4];
	Vec2		v2Arr[4];
	Vec4		v4Arr[4];
	Matrix		matArr[4];

	int32		bTex[(int32)TEX_PARAM::END];

	int32		iPadding[2];
};