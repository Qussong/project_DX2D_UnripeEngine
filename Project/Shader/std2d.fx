#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0) // b = (constant) buffer
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
}

Texture2D       TEXTURE : register(t0); 

SamplerState    SAMPLER_0 : register(s0); // ANISOTROPIC
SamplerState    SAMPLER_1 : register(s1); // POINT

cbuffer MATERIAL : register(b1)
{
    int     g_int_0;
    int     g_int_1;
    int     g_int_2;
    int     g_int_3;
    
    float   g_float_0;
    float   g_float_1;
    float   g_float_2;
    float   g_float_3;
    
    float2  g_vec2_0;
    float2  g_vec2_1;
    float2  g_vec2_2;
    float2  g_vec2_3;
    
    float4  g_vec4_0;
    float4  g_vec4_1;
    float4  g_vec4_2;
    float4  g_vec4_3;
    
    row_major matrix g_mat_0;
    row_major matrix g_mat_1;
    row_major matrix g_mat_2;
    row_major matrix g_mat_3;
}

// 정점 구조체 Vtx 로부터 넘겨받는 정보
struct VS_IN
{
    float3 vPos     : POS;  // Semantic
    float4 vColor   : COLOR;
    float2 vUV      : TEXCOORD;
};

struct VS_OUT
{
    float4 vPos     : SV_Position;
    float4 vColor   : COLOR;
    float2 vUV      : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // 연산순서 : local -> World -> View -> Projection
    float4 v4WorldPos   = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 v4ViewPos    = mul(v4WorldPos, g_matView);
    float4 v4ProjPos    = mul(v4ViewPos, g_matProj);
    
    output.vPos     = v4ProjPos;
    output.vColor   = _in.vColor;
    output.vUV      = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 v4Color = TEXTURE.Sample(SAMPLER_1, _in.vUV);
    
    if (v4Color.a < 0.1f)
        discard;
    
    if (1 != g_int_0)
        v4Color = float4(1.f, 1.f, 1.f, 1.f);

    return v4Color;
}
#endif
