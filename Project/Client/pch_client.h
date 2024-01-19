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
#include <Engine/CEngine.h>
#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

// new 재정의
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

// custom
#include "value_client.h"