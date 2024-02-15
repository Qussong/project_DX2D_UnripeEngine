#pragma once

#define WINDOW_WIDTH			1280
#define WINDOW_HEIGHT			720

typedef void (*CALL_BACK_0)(void);					// void (*functionPointerName)(void);
typedef void (*CALL_BACK_1)(DWORD_PTR);				// void (*functionPointerName)(DWORD_PTR);
typedef void (*CALL_BACK_2)(DWORD_PTR, DWORD_PTR);	// void (*functionPointerName)(DWORD_PTR, DWORD_PTR);