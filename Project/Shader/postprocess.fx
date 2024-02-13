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
    // SV_Position���� �Էµ� ���� PS�� ȣ���� �ش� �ȼ��� ��ǥ�� ���´�.
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
    
    // UV�� �ִ밪�� x,y������ ���� 1
    // PS�� ȣ���� ��ǥ�� ȭ��󿡼��� ���� ���
    float2 vScreenUV = _in.vPos.xy / g_v2RenderResolution;
    
    // ������� ����� �̹����� �ִ� ���
    if(g_btex_0)
    {
        float2 vUV = _in.vUV;
        vUV.x += g_fAccTime * 0.1f;
        
        // Noise �̹������� ������ RGBA�� ���� ���� ��ǥ������ ���
        float2 vNoise = G_TEXTURE_0.Sample(G_SAMPLER_0, vUV);
        // ?
        float fNoiseRatio = 0.03f;
        vNoise = (vNoise.xy - 0.5f) * fNoiseRatio;
        // ����� noise���� PS�� ȣ���� ��ǥ�� ������ ����
        vScreenUV += vNoise;
    }
    
    v4Color = G_POSTPROCESS.Sample(G_SAMPLER_0, vScreenUV);
    
    // test
    v4Color += float4(0.1f, 0.f, 0.2f, 0.f);
    
    return v4Color;
}

#endif