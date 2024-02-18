#ifndef _SETCOLOR
#define _SETCOLOR

#include "value.fx"

RWTexture2D<float4> G_TARGETTEX : register(u0);

[numthreads(32, 32, 1)]
void CS_SetColor(uint3 id : SV_DispatchThreadID)
{
    G_TARGETTEX[id.xy].rgb = g_vec4_0.rgb;
    //G_TARGETTEX[id.xy] = float4(g_vec4_0.rgb, 0.f);
}

#endif