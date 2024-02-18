#ifndef _VALUE
#define _VALUE

#include "struct.fx"

#define     PI      3.141592f

// Transform �������
cbuffer TRANSFORM : register(b0) // b = (constant) buffer
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    row_major matrix g_matWVP;
}

// Material �������
cbuffer MATERIAL : register(b1)
{
    // [scalar �� ����]
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;    // UI ����(0 : UI ��ü �ƴ�, 1~ : UI ��ü)
    
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
    
    // [texture ���翩��]
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

// Animation �������
cbuffer ANIM2D_DATA : register(b2)
{
    float2  g_v2LeftTop;
    float2  g_v2SliceSize;
    float2  g_v2Background;
    float2  g_v2Offset;
    int     g_iUseAnim2D;
    
    float3  v3Padding;
}

// ���� ����
cbuffer GLOBAL_DATA : register(b3)
{
    float2  g_v2RenderResolution;   // �ػ�
    float   g_fDeltaTime;           // ��ŸŸ��
    float   g_fAccTime;             // �����ð� (Accumulate : ����)
    int     g_iLight2DCnt;          // 2D ���� ����
    int     g_iLight3DCnt;          // 3D ���� ����
    int     g_iDebugCheck;          // Debug Render On/Off
    
    int     padding;
}

//RWTexture2D<float4> G_TARGETTEX         : register(u0);

Texture2D           G_TEXTURE_0         : register(t0);
Texture2D           G_TEXTURE_1         : register(t1);
Texture2D           G_TEXTURE_2         : register(t2);
Texture2D           G_TEXTURE_3         : register(t3);
Texture2D           G_TEXTURE_4         : register(t4);
Texture2D           G_TEXTURE_5         : register(t5);

TextureCube         G_TEXCUBE_0         : register(t6);
TextureCube         G_TEXCUBE_1         : register(t7);

Texture2DArray      G_TEXARR_0          : register(t8);
Texture2DArray      G_TEXARR_1          : register(t9);

Texture2D           G_TEX_ANIM2D_0      : register(t10);    // Animation�� Atlas Texture

StructuredBuffer<tLightInfo> G_LIGHT2D  : register(t11);   // ����ȭ ����, Light2D
StructuredBuffer<tLightInfo> G_LIGHT3D  : register(t12);   // ����ȭ ����, Light3D

Texture2D           G_POSTPROCESS       : register(t13);

SamplerState        G_SAMPLER_0         : register(s0); // ANISOTROPIC
SamplerState        G_SAMPLER_1         : register(s1); // POINT

#endif