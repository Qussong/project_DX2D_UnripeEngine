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
	Matrix matWVP;
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
	int32		iArr[4];	// 정수 데이터 (SCALAR_PARAM::INT_0 ~ 1)
	float		fArr[4];	// 실수 데이터 (SCALAR_PARAM::FLOAT_0 ~ 1)
	Vec2		v2Arr[4];	// Vec2 데이터 (SCALAR_PARAM::VEC2_0 ~ 1)
	Vec4		v4Arr[4];	// Vec4 데이터 (SCALAR_PARAM::VEC4_0 ~ 1)
	Matrix		matArr[4];	// Matrix 데이터 (SCALAR_PARAM::MAT_0 ~ 1)	

	int32		bTex[(int32)TEX_PARAM::END];	// Texture 존재 여부

	int32		iPadding[2];	// 16Byte 단위 맞추는 용도
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE		eShape;
	Vec3			v3Color;

	Vec3			v3WorldPos;
	Vec3			v3WorldScale;
	Vec3			v3WorldRot;
	Matrix			matWorld;

	float			fLifeTime;	// 렌더 유지시간
	float			fDuration;	// 렌더링된 시간

	bool			bDepthTest;	
};

union CollisionID
{
	struct
	{
		UINT iLeftID;
		UINT iRightID;
	};
	UINT_PTR iID;
};

struct tAniFrmInfo
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Offset;
	Vec2	v2Background;
	float	fDuration;
};

// 상수버퍼(CB_TYPE::ANI_2D) 대응 구조체
struct tAnimation2D
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Background;
	Vec2	v2Offset;
	int32	iUseAni2D;	// 애니메이션 사용여부( 0 = false, 1 = true)
	int32	iDebugCheck;
	Vec2	v2Padding;	// 16Byte 단위 맞춰주는 용도
};