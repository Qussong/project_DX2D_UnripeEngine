#pragma once

#include "enum.h"

////////////////////////////////////////
// [ 일반 구조체 ]
////////////////////////////////////////

// 키
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

// TaskMgr 클래스 전용 데이터
struct tTask
{
	TASK_TYPE	eType;
	UINT_PTR	iParam1;
	UINT_PTR	iParam2;
};

// 디버그
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

// 충돌체
union CollisionID
{
	struct
	{
		UINT iLeftID;
		UINT iRightID;
	};
	UINT_PTR iID;
};

// 애니메이션
struct tAniFrmInfo
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Offset;
	Vec2	v2Background;
	float	fDuration;
};

// 타일맵
struct tTileInfo
{
	Vec2 v2LeftTopUV;
	int  bRender;
	int	 iPadding;
};

// 픽셀
struct tPixel
{
	BYTE r, g, b, a;
};

////////////////////////////////////////
// [ 상수/구조화 버퍼 대응 구조체 ]
////////////////////////////////////////

// CB_TYPE::TRANSFORM
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWVP;
};

// CB_TYPE::MATERIAL
struct tMaterial
{
	int32		iArr[4];						// 정수 데이터 (SCALAR_PARAM::INT_0 ~ 1)
	float		fArr[4];						// 실수 데이터 (SCALAR_PARAM::FLOAT_0 ~ 1)
	Vec2		v2Arr[4];						// Vec2 데이터 (SCALAR_PARAM::VEC2_0 ~ 1)
	Vec4		v4Arr[4];						// Vec4 데이터 (SCALAR_PARAM::VEC4_0 ~ 1)
	Matrix		matArr[4];						// Matrix 데이터 (SCALAR_PARAM::MAT_0 ~ 1)

	int32		bTex[(int32)TEX_PARAM::END];	// Texture 존재 여부

	int32		iPadding[2];					// 16Byte 단위 맞추는 용도
};

// CB_TYPE::ANI2D
struct tAnimation2D
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Background;
	Vec2	v2Offset;
	int32	iUseAni2D;		// 애니메이션 사용여부( 0 = false, 1 = true)

	Vec3	v2Padding;
};

// CB_TYPE::GLOBAL
struct tGlobalData
{
	Vec2	v2RenderResolution;
	float	iDT;
	float	fAccTime;		// 누적시간
	int32	iLight2DCnt;
	int32	iLight3DCnt;
	int32	iDebugCheck;	// Debug Render On/Off

	int32	iPadding;
};

// Structured Buffer
struct tLight2D
{
	Vec4	v4Color;		// 빛의 색상 : 광원의 순수 색상
	Vec4	v4Specular;		// 반사광 : 광원이 물체 표면에 반사된 색상
	Vec4	v4Ambient;		// 환경광(주변광) : 광원에 의해 보장되는 최소 밝기

	Vec3	v3WorldPos;		// 광원의 위치
	Vec3	v3WorldDir;		// 광원이 향하는 방향
	float	fRadius;		// 광원의 영향 반경, 거리정보
	float	fAngle;			// 광원의 범위 각도
	int32	iLightType;		// 광원타입(LIGHT_TYPE)

	Vec3	v3Padding;
};