#ifndef _VALUE
#define _VALUE

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
cbuffer ANIM_DATA2D : register(b2)
{
    float2  g_v2LeftTop;
    float2  g_v2SliceSize;
    float2  g_v2Offset;
    int     g_iUseAnim2D;
    int     iPadding;
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

Texture2D       TEX_ANIM2D_0    : register(t10);    // Animation에 사용될 Atlas Texture 저장

SamplerState    SAMPLER_0       : register(s0); // ANISOTROPIC
SamplerState    SAMPLER_1       : register(s1); // POINT

#endif