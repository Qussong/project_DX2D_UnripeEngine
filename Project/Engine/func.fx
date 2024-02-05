#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"

void CalLight2D(float3 _worldPos, int _lightIdx, inout tLightColorInfo _output)
{
    // ������ ����
    tLightInfo tInfo = LIGHT2D[_lightIdx];
    
    int iType = tInfo.iLightType;
    
    // DIRECTIONAL
    if (0 == iType)
    {
        _output.v4Ambient += tInfo.tColor.v4Ambient;
    }
    // POINT
    else if(1 == iType)
    {
        float fAttenu = 0.f;    // ���� ( 0 : Dark, 1 : Bright)
        float fDist = distance(tInfo.v3WorldPos.xy, _worldPos.xy); // Pixel �� ���������� �Ÿ�
        
        // ������ ����� ���ο� �ִ� ���
        if (fDist < tInfo.fRadius)
        {
            if(g_int_0)
            {
                float fTheta = (fDist / tInfo.fRadius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            }
            else
            {
                fAttenu = saturate(1.f - fDist / LIGHT2D[0].fRadius);
            }
        }
        
        _output.v4Color += (tInfo.tColor.v4Color * fAttenu);
    }
    // SPOT
    else if(2 == iType)
    {
        
    }
}

#endif