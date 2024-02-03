#pragma once

// KeyMgr
enum class KEY
{
	_0, _1, _2, _3, _4,
	_5, _6, _7, _8, _9,

	NUM0, NUM1, NUM2, NUM3, NUM4,
	NUM5, NUM6, NUM7, NUM8, NUM9,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D,F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	TAB, LSHIFT, LALT, LCTRL,
	SPACE, ESC, ENTER, BACK,
	LEFT, RIGHT, UP, DOWN,

	LBTN, RBTN,

	KEY_END,
};

enum class KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,

	END,
};

enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHIC_SHADER,

	END,
};

enum class COMPONENT_TYPE
{
	NONE,

	// Basic Component
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	LIGHT2D,
	LIGHT3D,
	CAMERA,

	BASIC_END,

	// Render Component
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE,

	RENDER_END,

	// Script
	SCRIPT,
};

enum class DIR_TYPE
{
	RIGHT,	// x
	UP,		// y
	FRONT,	// z

	END,
};

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	ANI_2D,
	GLOBAL,

	END,
};

enum class PROJ_TYPE
{
	ORTHOGRAPHIC,	// 직교투영
	PERSPECTIVE,	// 원근투영

	END,
};

// Rasterizer State Type
enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,

	END,
};

// DepthStencil State Type
enum class DS_TYPE
{
	LESS,				// 작은게 통과				깊이 기록 O
	LESS_EQUAL,			// 작거나 같으면 통과		깊이 기록 O
	GRATER,				// 더 멀면 통과				깊이 기록 O
	GRATER_EQUAL,		// 더 멀거나 같으면 통과	깊이 기록 O
	NO_TEST,			// 깊이 테스트 X			깊이 기록 O
	NO_WRITE,			// 깊이 테스트 O			깊이 기록 X
	NO_TEST_NO_WRITE,	// 깊이 테스트 X			깊이 기록 X

	END,
};

// Blend State
enum class BS_TYPE
{
	DEFAULT,
	ALPHA_BLEND,
	ONE_ONE,

	END,
};

// Sampler State
enum class SS_TYPE
{
	ANISOTROPIC,	// 이방성
	POINT,

	END,
};

enum class LAYER_TYPE
{
	UNREGISTER = -1,

	DEFAULT,	// 0
	BACKGROUND,	// 1
	TILE,		// 2
	PLAYER,		// 3
	MONSTER,	// 4
	UI,			// 5
	
	END,
};

enum class TASK_TYPE
{
	// p1: GameObject, p2 : LayerType
	ADD_OBJET,

	// p1 : GameObject, p2 : NULL
	SUB_OBJECT,

	ADD_CHILD,
	DISCONNECT_PARENT,
	LEVEL_CHANGE,

	END,
};

// Transform) World Matrix -> Vec3 Scale/Rot/Pos
enum class SRT_TYPE
{
	SCALE,
	ROTATE,
	POS,

	END,
};

// Material 상수버퍼
enum class TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};

enum class SCALAR_PARAM
{
	INT_0,		// 0
	INT_1,
	INT_2,
	INT_3,	

	FLOAT_0,	// 4
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,		// 8
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,		// 12
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,		// 16
	MAT_1,
	MAT_2,
	MAT_3,
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,

	CUBE,
	SPHERE,

	END,
};

enum class COLLIDER2D_TYPE
{
	RECT,
	CIRCLE,

	END,
};

// StructuredBuffer
enum class SB_TYPE
{
	READ_ONLY,
	READ_WRITE,

	END,
};