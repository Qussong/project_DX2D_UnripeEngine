#ifndef _STRUCT
#define _STRUCT

struct tLightColorInfo
{
    float4 v4Color;     // ���� ���� : ������ ���� ����
    float4 v4Specular;  // �ݻ籤 : ������ ��ü ǥ�鿡 �ݻ�� ����
    float4 v4Ambient;   // ȯ�汤(�ֺ���) : ������ ���� ����Ǵ� �ּ� ���
};

struct tLightInfo
{
    tLightColorInfo tColor;     // ������ ���� ����(����, �ݻ籤, ȯ�汤)
    float3          v3WorldPos; // ������ ��ġ
    float3          v3WorldDir; // ������ ���ϴ� ����
    float           fRadius;    // ������ ���� �ݰ�, �Ÿ�����
    float           fAngle;     // ������ ���� ����
    int             iLightType; // ����Ÿ��(LIGHT_TYPE) -> 0 : Directional, 1 : Point, 2 : Spot
    
    float3          v3Padding;
};

#endif