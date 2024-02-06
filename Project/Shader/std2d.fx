#ifndef _STD2D
#define _STD2D

#include "struct.fx"
#include "value.fx"
#include "func.fx"

// 정점 구조체 Vtx 로부터 넘겨받는 정보
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
    
    // 연산순서 : local -> World -> View -> Projection
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
        // 애니메이션 사용하는 경우
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
                // 10번 Texture 샘플링(Animation)
                v4Color = TEX_ANIM2D_0.Sample(SAMPLER_1, vUV);
            }
        }
        // 애니메이션 사용하지 않는 경우
        else
        {
            // 0번 Texture 샘플링(Texture)
            if (g_btex_0)
                v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
        }
        
        // 알파값 0.1f 이하 Render 안함
        if (v4Color.a < 0.1f)
            discard; // clip(-1);
            
        // Player Highlight
        if (g_int_0)
            v4Color.r += 1.f;
    }
    
    // 광원처리
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
        // 애니메이션 사용하는 경우
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
                // 10번 Texture 샘플링(Animation)
                v4Color = TEX_ANIM2D_0.Sample(SAMPLER_1, vUV);
            }
        }
        // 애니메이션 사용하지 않는 경우
        else
        {
            // 0번 Texture 샘플링(Texture)
            if (g_btex_0)
                v4Color = TEXTURE_0.Sample(SAMPLER_1, _in.vUV);
        }
            
        // Player Highlight
        if (g_int_0)
            v4Color.r += 1.f;
    }
    
    // 광원처리
    tLightColorInfo tLightColor = (tLightColorInfo) 0.f;
    for (int idx = 0; idx < g_iLight2DCnt; ++idx)
    {
        CalLight2D(_in.vWorldPos, idx, tLightColor);
    }
    
    v4Color.rgb *= (tLightColor.v4Color.rgb + tLightColor.v4Ambient.rgb);
    
    return v4Color;
}

#endif