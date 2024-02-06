#ifndef _STD2D
#define _STD2D

#include "struct.fx"
#include "value.fx"
#include "func.fx"

// ���� ����ü Vtx �κ��� �Ѱܹ޴� ����
struct VS_IN
{
    float3 vPos     : POS;      // Semantic
    float4 vColor   : COLOR;
    float2 vUV      : TEXCOORD;
};

struct VS_OUT
{
    float4 vPos         : SV_Position;
    float4 vColor       : COLOR;
    float2 vUV          : TEXCOORD;
    float3 vWorldPos    : POS;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ������� : local -> World -> View -> Projection
    float4 v4WorldPos   = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 v4ViewPos    = mul(v4WorldPos, g_matView);
    float4 v4ProjPos    = mul(v4ViewPos, g_matProj);
    
    output.vPos         = v4ProjPos;
    output.vColor       = _in.vColor;
    output.vUV          = _in.vUV;
    output.vWorldPos    = float3(v4WorldPos.x, v4WorldPos.y, v4WorldPos.z);
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 v4Color = float4(1.f, 1.f, 1.f, 1.f);
    
    if (g_btex_0 || g_iUseAnim2D)
    {
        // �ִϸ��̼� ����ϴ� ���
        if (g_iUseAnim2D)
        {
            float2 v2BackgroundLeftTop = g_v2LeftTop + (g_v2SliceSize / 2.f) - (g_v2Background / 2.f);
            v2BackgroundLeftTop -= g_v2Offset;
            float2 vUV = v2BackgroundLeftTop + (g_v2Background * _in.vUV);
        
            if (vUV.x < g_v2LeftTop.x
            || (g_v2LeftTop.x + g_v2SliceSize.x) < vUV.x
            || vUV.y < g_v2LeftTop.y
            || (g_v2LeftTop.y + g_v2SliceSize.y) < vUV.y)
            {
                if (g_iDebugCheck)
                    v4Color = float4(.5f, .7f, .5f, 1.f);
                else
                    discard;
            }
            else
            {
                // 10�� Texture ���ø�(Animation)
                v4Color = TEX_ANIM2D_0.Sample(SAMPLER_1, vUV);
            }
        }
        // �ִϸ��̼� ������� �ʴ� ���
        else
        {
            // 0�� Texture ���ø�(Texture)
            if (g_btex_0)
                v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
        }
        
        // ���İ� 0.1f ���� Render ����
        if (v4Color.a < 0.1f)
            discard; // clip(-1);
            
        // Player Highlight
        if (g_int_0)
            v4Color.r += 1.f;
    }
    
    // ����ó��
    tLightColorInfo tLightColor = (tLightColorInfo) 0.f;
    for (int idx = 0; idx < g_iLight2DCnt; ++idx)
    {
        CalLight2D(_in.vWorldPos, idx, tLightColor);
    }
    
    v4Color.rgb *= (tLightColor.v4Color.rgb + tLightColor.v4Ambient.rgb);
    
    return v4Color;
}

float4 PS_Std2D_Effect(VS_OUT _in) : SV_Target
{
    float4 v4Color = float4(1.f, 1.f, 1.f, 1.f);
    
    if (g_btex_0 || g_iUseAnim2D)
    {
        // �ִϸ��̼� ����ϴ� ���
        if (g_iUseAnim2D)
        {
            float2 v2BackgroundLeftTop = g_v2LeftTop + (g_v2SliceSize / 2.f) - (g_v2Background / 2.f);
            v2BackgroundLeftTop -= g_v2Offset;
            float2 vUV = v2BackgroundLeftTop + (g_v2Background * _in.vUV);
        
            if (vUV.x < g_v2LeftTop.x
            || (g_v2LeftTop.x + g_v2SliceSize.x) < vUV.x
            || vUV.y < g_v2LeftTop.y
            || (g_v2LeftTop.y + g_v2SliceSize.y) < vUV.y)
            {
                if (g_iDebugCheck)
                    v4Color = float4(.5f, .7f, .5f, 1.f);
                else
                    discard;
            }
            else
            {
                // 10�� Texture ���ø�(Animation)
                v4Color = TEX_ANIM2D_0.Sample(SAMPLER_1, vUV);
            }
        }
        // �ִϸ��̼� ������� �ʴ� ���
        else
        {
            // 0�� Texture ���ø�(Texture)
            if (g_btex_0)
                v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
        }
            
        // Player Highlight
        if (g_int_0)
            v4Color.r += 1.f;
    }
    
    // ����ó��
    tLightColorInfo tLightColor = (tLightColorInfo) 0.f;
    for (int idx = 0; idx < g_iLight2DCnt; ++idx)
    {
        CalLight2D(_in.vWorldPos, idx, tLightColor);
    }
    
    v4Color.rgb *= (tLightColor.v4Color.rgb + tLightColor.v4Ambient.rgb);
    
    return v4Color;
}

#endif