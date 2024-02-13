#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

struct VS_IN
{
    float3 vPos : POS;
    float2 vUV  : TEXCOORD;
};

struct VS_OUT
{
    // SV_Position으로 입력된 값은 PS를 호출한 해당 픽셀의 좌표가 들어온다.
    float4 vPos : SV_Position;
    float2 vUV  : TEXCOORD;
};

// ==========
// GreyFilter
// ==========
VS_OUT VS_GreyFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GreyFilter(VS_OUT _in) : SV_Target
{
    float4 v4Color = (float4) 0.f;
    
    // Texture Sampling
    v4Color = G_POSTPROCESS.Sample(G_SAMPLER_1, _in.vUV);
    
    float fAvg  = (v4Color.r + v4Color.g + v4Color.b) / 3.f;
    v4Color.rgb = float3(fAvg, fAvg, fAvg);
    
    return v4Color;
}

// ==========
// Distortion
// ==========
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPos = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV  = _in.vUV;
    
    return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    float4 v4Color = (float4) 0.f;
    
    // UV의 최대값은 x,y축으로 각각 1
    // PS를 호출한 좌표의 화면상에서의 비율 계산
    float2 vScreenUV = _in.vPos.xy / g_v2RenderResolution;
    
    // 노이즈로 사용할 이미지가 있는 경우
    if(g_btex_0)
    {
        float2 vUV = _in.vUV;
        vUV.x += g_fAccTime * 0.1f;
        
        // Noise 이미지에서 추출한 RGBA에 대한 값을 좌표값으로 사용
        float2 vNoise = G_TEXTURE_0.Sample(G_SAMPLER_0, vUV);
        // ?
        float fNoiseRatio = 0.03f;
        vNoise = (vNoise.xy - 0.5f) * fNoiseRatio;
        // 연산된 noise값을 PS를 호출한 좌표의 비율에 가산
        vScreenUV += vNoise;
    }
    
    v4Color = G_POSTPROCESS.Sample(G_SAMPLER_0, vScreenUV);
    
    // test
    v4Color += float4(0.1f, 0.f, 0.2f, 0.f);
    
    return v4Color;
}

#endif