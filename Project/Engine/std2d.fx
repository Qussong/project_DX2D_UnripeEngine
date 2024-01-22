#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0) // b = (constant) buffer
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
}

Texture2D       TEXTURE : register(t0);
SamplerState    SAMPLER : register(s0);

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
    float4 color = TEXTURE.Sample(SAMPLER, _in.vUV);
    
    return color;
}

#endif
