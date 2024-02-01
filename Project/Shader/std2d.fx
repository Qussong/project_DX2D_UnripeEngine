#ifndef _STD2D
#define _STD2D

#include "value.fx"

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
    float4 v4Color = float4(1.f, 1.f, 1.f, 1.f);
    
    // 0번 Texture 샘플링
    if (g_btex_0)
        v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
    
    // 알파값 0.1f 이하 Render 안함
    if (v4Color.a < 0.1f)
        discard; // clip(-1);

    // Player Highlight
    if(g_int_0)
        v4Color.r += 1.f;
    
    return v4Color;
}
#endif
