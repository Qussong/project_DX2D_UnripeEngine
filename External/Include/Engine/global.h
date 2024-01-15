#pragma once

// STL
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

// WIN
#include <windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;
#include <assert.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
using namespace DirectX;
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#include "SimpleMath.h"

// Custom
#include "etc.h"		// ���� ���
#include "CEngine.h"	// ����
#include "component.h"	// ������Ʈ
#include "manager.h"	// �Ŵ���

#include "CGraphics.h"
#include "CEntity.h"
#include "CAsset.h"
#include "CMesh.h"
#include "CShader.h"
#include "CGraphicShader.h"
#include "CConstantBuffer.h"
#include "CGameObject.h"