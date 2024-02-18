#pragma once

// STL
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <list>
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

// DirectxTex
#include <DirectXTex/DirectXTex.h>
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_d")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex")
#endif

// Custom
#include "etc.h"		// 각종 헤더
#include "struct.h"		// 구조체
#include "extern.h"		// 전역변수
#include "CEngine.h"	// 엔진
#include "component.h"	// 컴포넌트

#include "CEntity.h"
#include "CAsset.h"
#include "CMesh.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CGraphics.h"
#include "CShader.h"
#include "CGraphicShader.h"
#include "CConstantBuffer.h"
#include "CStructuredBuffer.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CComputeShader.h"
#include "CSetColorShader.h"

#include "manager.h"	// 매니저