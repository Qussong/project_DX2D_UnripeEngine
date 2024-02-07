#ifndef _POSTPROCESS
#define _POSTPROCESS

struct VS_IN
{
    float3 vPos     : POS;
    float4 vColor   : COLOR;
};

struct VS_OUT
{
    float4 vPos : SV_Position;
    float2 vUV  : TEXCOORD;
};

VS_OUT VS_GreyFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    return output;
}

float4 PS_GreyFilter(VS_OUT _in) : SV_Target
{
    float4 v4Color = (float4) 0.f;
    
    return v4Color;
}

#endif