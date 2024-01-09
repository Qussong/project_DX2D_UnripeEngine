#pragma once

// win
#include <windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;
#include <assert.h>

// dx
#include <d3d11.h>
#include <d3dcompiler.h>
//#include <DirectXMath.h>
//using namespace DirectX;
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// custom
#include "define.h"
#include "singleton.h"
#include "value.h"