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

// Dear ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

// ETC
#include "value_client.h"
#include "enum_client.h"

// Manager
#include "CImGuiMgr.h"

// UI
#include "CUI.h"
#include "COutliner.h"
#include "CInspector.h"
#include "CContent.h"
#include "COverlay.h"
#include "CComponentUI.h"
#include "CTransformUI.h"
#include "CMeshRenderUI.h"