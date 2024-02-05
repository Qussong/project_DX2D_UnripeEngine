#ifndef _VALUE
#define _VALUE

#include "struct.fx"

#define     PI      3.141592f

// Transform 상수버퍼
cbuffer TRANSFORM : register(b0) // b = (constant) buffer
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    row_major matrix g_matWVP;
}

// Material 상수버퍼
cbuffer MATERIAL : register(b1)
{
    // [scalar 값 전달]
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    row_major matrix g_mat_0;
    row_major matrix g_mat_1;
    row_major matrix g_mat_2;
    row_major matrix g_mat_3;
    
    // [texture 존재여부]
    // TEX_PARAM::TEX_0 ~ TEX_5
    int g_btex_0;
    int g_btex_1;
    int g_btex_2;
    int g_btex_3;
    int g_btex_4;
    int g_btex_5;
    
    // TEX_PARAM::TEXCUBE_0, TEXCUBE_1
    int g_btexcube_0;
    int g_btexcube_1;
    
    // TEX_PARAM::TEXARR_0, TEXARR_1
    int g_btexarr_0;
    int g_btexarr_1;
}

// Animation 상수버퍼
cbuffer ANIM2D_DATA : register(b2)
{
    float2  g_v2LeftTop;
    float2  g_v2SliceSize;
    float2  g_v2Background;
    float2  g_v2Offset;
    int     g_iUseAnim2D;
    
    float3  v3Padding;
}

// 공용 변수
cbuffer GLOBAL_DATA : register(b3)
{
    float2  g_v2RenderResolution;   // 해상도
    float   g_fDeltaTime;           // 델타타임
    float   g_fAccTime;             // 누적시간 (Accumulate : 누적)
    int     g_iLight2DCnt;          // 2D 광원 개수
    int     g_iLight3DCnt;          // 3D 광원 개수
    int     g_iDebugCheck;          // Debug Render On/Off
    
    int     padding;
}


Texture2D       TEXTURE_0       : register(t0);
Texture2D       TEXTURE_1       : register(t1);
Texture2D       TEXTURE_2       : register(t2);
Texture2D       TEXTURE_3       : register(t3);
Texture2D       TEXTURE_4       : register(t4);
Texture2D       TEXTURE_5       : register(t5);

TextureCube     TEXCUBE_0       : register(t6);
TextureCube     TEXCUBE_1       : register(t7);

Texture2DArray  TEXARR_0        : register(t8);
Texture2DArray  TEXARR_1        : register(t9);

Texture2D       TEX_ANIM2D_0    : register(t10);    // Animation용 Atlas Texture

StructuredBuffer<tLightInfo> LIGHT2D : register(t11);   // 구조화 버퍼, Light2D
StructuredBuffer<tLightInfo> LIGHT3D : register(t12);   // 구조화 버퍼, Light3D

SamplerState    SAMPLER_0       : register(s0); // ANISOTROPIC
SamplerState    SAMPLER_1       : register(s1); // POINT

#endif