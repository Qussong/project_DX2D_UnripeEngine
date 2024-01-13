#pragma once

// STL
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
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
#include "singleton.h"
#include "define.h"
#include "value.h"
#include "types.h"
#include "struct.h"
#include "enum.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"

#include "CGraphics.h"
#include "CEntity.h"
#include "CAsset.h"
#include "CMesh.h"