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
	int32		iArr[4];	//  4Byte * 4 =  16Byte
	float		fArr[4];	//  4Byte * 4 =  16Byte
	Vec2		v2Arr[4];	//  8Byte * 4 =  32Byte
	Vec4		v4Arr[4];	// 16Byte * 4 =  64Byte
	Matrix		matArr[4];	// 64Byte * 4 = 256Byte
};