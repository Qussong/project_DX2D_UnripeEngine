#ifndef _SETCOLOR
#define _SETCOLOR

#include "value.fx"

#define TEX_WIDTH   g_int_0
#define TEX_HEIGHT  g_int_1
#define RANGE       100.f
//RWTexture2D<float4> G_TARGETTEX : register(u0);

// 그룹 하나의 Thread 차원 수
// HLSL5.0 하나의 그룹이 가질 수 있는 최대 스레드 개수 = 1024개
[numthreads(32, 32, 1)]
void CS_SetColor(uint3 id : SV_DispatchThreadID)
{   
    // 색칠될 범위
    //if (id.y >= TEX_HEIGHT / 2 - RANGE && id.y <= TEX_HEIGHT / 2 + RANGE)
    //{
    //    G_TARGETTEX[id.xy] = float4(g_vec4_0.rgb, 1.f);
    //}
    
    if (id.y >= TEX_HEIGHT / 2)
    {
        G_TARGETTEX[id.xy] = float4(g_vec4_0.rgb, 1.f);
    }
    else
    {
        G_TARGETTEX[id.xy] = float4(0.f, 1.f, 1.f, 1.f);
    }
}

#endif