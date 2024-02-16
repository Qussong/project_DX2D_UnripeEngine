#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"
#include "struct.fx"

// Parameter
#define FACE_X      g_int_0
#define FACE_Y      g_int_1

#define vSliceUV    g_vec2_0

#define TileAtlas   G_TEXTURE_0

StructuredBuffer<tTileInfo> g_TileInfo : register(t20);

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
        // 면 개수만큼 _in.vUV 를 배율을 늘림
        float2 vUV = _in.v2UV * float2(FACE_X, FACE_Y);
        int2 Integer = (int2) floor(vUV);
        vUV = vUV - Integer;
                
        int bufferidx = Integer.y * FACE_X + Integer.x;
        
        if (!g_TileInfo[bufferidx].bRender)
            discard;
        
        vUV = g_TileInfo[bufferidx].v2LeftTopUV + (vSliceUV * vUV);
        v4Color = TileAtlas.Sample(G_SAMPLER_1, vUV);
    }
    
    return v4Color;
}

#endif