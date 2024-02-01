#ifndef _STD2D
#define _STD2D

#include "value.fx"

// ���� ����ü Vtx �κ��� �Ѱܹ޴� ����
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
    
    // ������� : local -> World -> View -> Projection
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
    
    // 0�� Texture ���ø�
    if (g_btex_0)
        v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
    
    // ���İ� 0.1f ���� Render ����
    if (v4Color.a < 0.1f)
        discard; // clip(-1);

    // Player Highlight
    if(g_int_0)
        v4Color.r += 1.f;
    
    return v4Color;
}
#endif
