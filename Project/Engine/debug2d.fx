#ifndef _DEBUG2D
#define _DEBUG2D

#include "value.fx"

struct VS_IN
{
    float3 vPos : POS;
    float2 vUV  : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV       : TEXCOORD;
};

VS_OUT VS_DebugShape(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

static float g_fThickness = 0.1f;
float4 PS_DebugShape(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (g_fThickness <= _in.vUV.x
        && _in.vUV.x <= (1.f - g_fThickness)
        && g_fThickness <= _in.vUV.y
        && _in.vUV.y <= (1.f - g_fThickness))
    {
        discard;
    }
    
    vOutColor = float4(.7f, 0.f, 0.5f, 1.f);
    
    return vOutColor;
}
#endif