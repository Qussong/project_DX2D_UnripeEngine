#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"

// Parameter
#define v2LeftTopUV  g_vec2_0
#define v2SliceUV    g_vec2_1

struct VS_IN
{
    float3 v3Pos     : POS; 
    float2 v2UV      : TEXCOORD;
};

struct VS_OUT
{
    float4 v4Pos         : SV_Position;
    float2 v2UV          : TEXCOORD;
};

VS_OUT VS_TileMap(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
 
    output.v4Pos = mul(float4(_in.v3Pos, 1.f), g_matWVP);
    output.v2UV = _in.v2UV;
    
    return output;
}

float4 PS_TileMap(VS_OUT _in) : SV_Target
{
    float4 v4Color = (float4) 0.f;
    
    if(g_btex_0)
    {
        float2 v2UV = v2LeftTopUV + (v2SliceUV * _in.v2UV);
        v4Color = G_TEXTURE_0.Sample(G_SAMPLER_1, v2UV);
    }
    
    return v4Color;
}

#endif