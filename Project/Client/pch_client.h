#pragma once

// default
#include "framework.h"

// 디버그용 콘솔
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 메모리 누수 체크
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// engine
#include <Engine/global.h>
#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

// new 재정의 (ImGui 와 충돌로 주석처리)
//#ifdef _DEBUG
//#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#endif

// Dear ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

// custom
#include "value_client.h"
#include "CImGuiMgr.h"