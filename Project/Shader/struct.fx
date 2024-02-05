#ifndef _STRUCT
#define _STRUCT

struct tLightColorInfo
{
    float4 v4Color;     // 빛의 색상 : 광원의 순수 색상
    float4 v4Specular;  // 반사광 : 광원이 물체 표면에 반사된 색상
    float4 v4Ambient;   // 환경광(주변광) : 광원에 의해 보장되는 최소 밝기
};

struct tLightInfo
{
    tLightColorInfo tColor;     // 광원의 색상 정보(색상, 반사광, 환경광)
    float3          v3WorldPos; // 광원의 위치
    float3          v3WorldDir; // 광원이 향하는 방향
    float           fRadius;    // 광원의 영향 반경, 거리정보
    float           fAngle;     // 광원의 범위 각도
    int             iLightType; // 광원타입(LIGHT_TYPE) -> 0 : Directional, 1 : Point, 2 : Spot
    
    float3          v3Padding;
};

#endif