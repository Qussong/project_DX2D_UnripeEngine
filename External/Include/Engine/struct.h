#pragma once

#include "enum.h"

////////////////////////////////////////
// [ �Ϲ� ����ü ]
////////////////////////////////////////

// Ű
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

// TaskMgr Ŭ���� ���� ������
struct tTask
{
	TASK_TYPE	eType;
	UINT_PTR	iParam1;
	UINT_PTR	iParam2;
};

// �����
struct tDebugShapeInfo
{
	DEBUG_SHAPE		eShape;
	Vec3			v3Color;
	Vec3			v3WorldPos;
	Vec3			v3WorldScale;
	Vec3			v3WorldRot;
	Matrix			matWorld;
	float			fLifeTime;	// ���� �����ð�
	float			fDuration;	// �������� �ð�
	bool			bDepthTest;
};

// �浹ü
union CollisionID
{
	struct
	{
		UINT iLeftID;
		UINT iRightID;
	};
	UINT_PTR iID;
};

// �ִϸ��̼�
struct tAniFrmInfo
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Offset;
	Vec2	v2Background;
	float	fDuration;
};

// Ÿ�ϸ�
struct tTileInfo
{
	Vec2 v2LeftTopUV;
	int  bRender;
	int	 iPadding;
};

// �ȼ�
struct tPixel
{
	BYTE r, g, b, a;
};

////////////////////////////////////////
// [ ���/����ȭ ���� ���� ����ü ]
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
	int32		iArr[4];						// ���� ������ (SCALAR_PARAM::INT_0 ~ 1)
	float		fArr[4];						// �Ǽ� ������ (SCALAR_PARAM::FLOAT_0 ~ 1)
	Vec2		v2Arr[4];						// Vec2 ������ (SCALAR_PARAM::VEC2_0 ~ 1)
	Vec4		v4Arr[4];						// Vec4 ������ (SCALAR_PARAM::VEC4_0 ~ 1)
	Matrix		matArr[4];						// Matrix ������ (SCALAR_PARAM::MAT_0 ~ 1)

	int32		bTex[(int32)TEX_PARAM::END];	// Texture ���� ����

	int32		iPadding[2];					// 16Byte ���� ���ߴ� �뵵
};

// CB_TYPE::ANI2D
struct tAnimation2D
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Background;
	Vec2	v2Offset;
	int32	iUseAni2D;		// �ִϸ��̼� ��뿩��( 0 = false, 1 = true)

	Vec3	v2Padding;
};

// CB_TYPE::GLOBAL
struct tGlobalData
{
	Vec2	v2RenderResolution;
	float	iDT;
	float	fAccTime;		// �����ð�
	int32	iLight2DCnt;
	int32	iLight3DCnt;
	int32	iDebugCheck;	// Debug Render On/Off

	int32	iPadding;
};

// Structured Buffer
struct tLight2D
{
	Vec4	v4Color;		// ���� ���� : ������ ���� ����
	Vec4	v4Specular;		// �ݻ籤 : ������ ��ü ǥ�鿡 �ݻ�� ����
	Vec4	v4Ambient;		// ȯ�汤(�ֺ���) : ������ ���� ����Ǵ� �ּ� ���

	Vec3	v3WorldPos;		// ������ ��ġ
	Vec3	v3WorldDir;		// ������ ���ϴ� ����
	float	fRadius;		// ������ ���� �ݰ�, �Ÿ�����
	float	fAngle;			// ������ ���� ����
	int32	iLightType;		// ����Ÿ��(LIGHT_TYPE)

	Vec3	v3Padding;
};