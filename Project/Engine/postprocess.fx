#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

struct VS_IN
{
    float3 vPos : POS;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// ==========
// GreyFilter
// ==========

VS_OUT VS_GreyFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = (_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GreyFilter(VS_OUT _in) : SV_Target
{
    float4 v4Color = (float4) 0.f;
    
    //v4Color = G_POSTPROCESS.Sample(G_SAMPLER_1, _in.vUV);
    //float fAvg = (v4Color.r + v4Color.g + v4Color.b) / 3.f;
    //v4Color.rgb = float3(fAvg, fAvg, fAvg);
    
    v4Color = float4(0.3f, 0.3f, 0.3f, 1.f);
    
    return v4Color;
}

#endif