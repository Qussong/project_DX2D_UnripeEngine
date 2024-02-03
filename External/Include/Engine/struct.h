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

// �������(CB_TYPE::TRANSFORM) ���� ����ü (16 Byte ����)
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWVP;
};

// TaskMgr Ŭ���� ���� ������
struct tTask
{
	TASK_TYPE	eType;
	UINT_PTR	iParam1;
	UINT_PTR	iParam2;

	// UINT_PTR : 
	// �ڷ��� ��ü�� ������ Ÿ���� �ƴ϶�, �ַ� ������ ������
	// �������� Ȱ��Ǵ� �ڷ����̱� ������ _PTR���̻簡 �ٴ´�.
};

// �������(CB_TYPE::MATERIAL) ���� ����ü
struct tMaterial
{
	int32		iArr[4];	// ���� ������ (SCALAR_PARAM::INT_0 ~ 1)
	float		fArr[4];	// �Ǽ� ������ (SCALAR_PARAM::FLOAT_0 ~ 1)
	Vec2		v2Arr[4];	// Vec2 ������ (SCALAR_PARAM::VEC2_0 ~ 1)
	Vec4		v4Arr[4];	// Vec4 ������ (SCALAR_PARAM::VEC4_0 ~ 1)
	Matrix		matArr[4];	// Matrix ������ (SCALAR_PARAM::MAT_0 ~ 1)	

	int32		bTex[(int32)TEX_PARAM::END];	// Texture ���� ����

	int32		iPadding[2];	// 16Byte ���� ���ߴ� �뵵
};

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

// �������(CB_TYPE::ANI_2D) ���� ����ü
struct tAnimation2D
{
	Vec2	v2LeftTop;
	Vec2	v2SliceSize;
	Vec2	v2Background;
	Vec2	v2Offset;
	int32	iUseAni2D;	// �ִϸ��̼� ��뿩��( 0 = false, 1 = true)
	int32	iDebugCheck;
	Vec2	v2Padding;	// 16Byte ���� �����ִ� �뵵
};