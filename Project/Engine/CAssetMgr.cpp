#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
}

void CAssetMgr::Init()
{
	Mesh();		// Mesh 생성
	Shader();	// shader 생성
	Material();	// Material 생성
	Texture();	// Texture 생성
}

void CAssetMgr::Mesh()
{
	// Rect Mesh
	{
		Vtx		arrRect[4] = {};
		UINT	arrIdx[6] = {};

		// 정점 정보 입력
		{
			// 사각형 정점 위치 설정
			// 0(R)--- 1(B)	     
			//  |   \   |	     
			// 3(G)--- 2(M)  

			arrRect[0].v3Pos = Vec3{ -0.5f, 0.5f, 0.f };
			arrRect[0].v4Color = Vec4{ 0.5f, 0.f, 0.5f, 1.f };
			arrRect[0].v2UV = Vec2{ 0.f, 0.f };

			arrRect[1].v3Pos = Vec3{ 0.5f, 0.5f, 0.f };
			arrRect[1].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
			arrRect[1].v2UV = Vec2{ 1.f, 0.f };

			arrRect[2].v3Pos = Vec3{ 0.5f, -0.5f, 0.f };
			arrRect[2].v4Color = Vec4{ 0.5f, 0.f, 0.5f, 1.f };
			arrRect[2].v2UV = Vec2{ 1.f, 1.f };

			arrRect[3].v3Pos = Vec3{ -0.5f, -0.5f, 0.f };
			arrRect[3].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
			arrRect[3].v2UV = Vec2{ 0.f, 1.f };
		}

		// 인덱스 정보 입력
		{
			arrIdx[0] = 0;
			arrIdx[1] = 1;
			arrIdx[2] = 2;

			arrIdx[3] = 0;
			arrIdx[4] = 2;
			arrIdx[5] = 3;
		}

		CMesh* pRectMesh = new CMesh;
		pRectMesh->Create(arrRect, 4, arrIdx, 6);
		AddAsset(L"RectMesh", pRectMesh);

		// Debug (Topology : LineStrip)
		arrIdx[0] = 0;
		arrIdx[1] = 1;
		arrIdx[2] = 2;
		arrIdx[3] = 3;
		arrIdx[4] = 0;
		
		CMesh* pRectDbgMesh = new CMesh;
		pRectDbgMesh->Create(arrRect, 4, arrIdx, 5);
		AddAsset(L"RectMesh_Debug", pRectDbgMesh);
	}

	// Circle Mesh
	{
		vector<Vtx>		vecCircle;
		vector<UINT>	vecIdx;
		Vtx				center;	// 중심점
		center.v3Pos = Vec3(0.f, 0.f, 0.f);
		center.v4Color = Vec4(0.5f, 0.f, 0.5f, 1.f);
		center.v2UV = Vec2(0.5f, 0.5f);
		vecCircle.push_back(center);

		// 원 둘레
		Vtx		temp;
		int32	iSlice = 20;
		float	fTheta = 0.f;
		float	fRadius = 0.5f;

		for (size_t i = 0; i < iSlice; ++i)
		{
			fTheta = (XM_2PI / iSlice) * i;

			temp.v3Pos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
			temp.v4Color = Vec4(0.f, 0.5f, 0.5f, 1.f);
			temp.v2UV = Vec2(0.f, 0.f);

			vecCircle.push_back(temp);
		}

		// 인덱스 정보 입력
		for (size_t i = 0; i < iSlice - 1; i++)
		{
			vecIdx.push_back(0);
			vecIdx.push_back((UINT)i + 2);
			vecIdx.push_back((UINT)i + 1);
		}
		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back((UINT)iSlice);

		CMesh* pCircleMesh = new CMesh;
		pCircleMesh->Create(vecCircle.data(),
			(uint32)vecCircle.size(),
			vecIdx.data(),
			(uint32)vecIdx.size());
		AddAsset(L"CircleMesh", pCircleMesh);

		// Debug
		vecIdx.clear();
		size_t vtxCnt = vecCircle.size();
		for (size_t i = 1; i < vtxCnt; ++i)
		{
			vecIdx.push_back((UINT)i);
		}
		vecIdx.push_back(1);

		CMesh* pCircleDbgMesh = new CMesh;
		pCircleDbgMesh->Create(vecCircle.data(), (uint32)vtxCnt, vecIdx.data(), (uint32)vecIdx.size());
		AddAsset(L"CircleMesh_Debug", pCircleDbgMesh);
	}

	// Cross Mesh
	{
		vector<Vtx>		vecVtx;
		vector<UINT>	vecIdx;
		Vtx				point;

		// 정점 정보 입력
		{
			point.v3Pos = Vec3(0.f, 0.5f, 0.f);
			point.v4Color = Vec4(0.f, 1.f, 0.f, 1.f);
			point.v2UV = Vec2(0.f, 0.f);
			vecVtx.push_back(point);

			point.v3Pos = Vec3(0.f, -0.5f, 0.f);
			vecVtx.push_back(point);

			point.v3Pos = Vec3(-0.5f, 0.f, 0.f);
			vecVtx.push_back(point);

			point.v3Pos = Vec3(0.5f, 0.f, 0.f);
			vecVtx.push_back(point);
		}

		// 인덱스 정보 입력
		{
			vecIdx.push_back(0); vecIdx.push_back(1);
			vecIdx.push_back(2); vecIdx.push_back(3);
		}

		CMesh* pMesh = new CMesh;
		pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
		AddAsset(L"CrossMesh_Debug", pMesh);
	}
}

void CAssetMgr::Shader()
{
	// Default Shader(2D_DefaultShader)
	{
		CGraphicShader* pShader = new CGraphicShader;
		pShader->VertexShader(L"std2d.fx", "VS_Std2D");
		pShader->PixelShader(L"std2d.fx", "PS_Std2D");
		pShader->SetRSType(RS_TYPE::CULL_NONE);		// default = CULL_BACK
		pShader->SetDSType(DS_TYPE::LESS);			// default = LESS
		pShader->SetBSType(BS_TYPE::ALPHA_BLEND);	// default = DEFAULT
		AddAsset(L"2D_DefaultShader", pShader);
	}

	// WireFrame Shader(2D_WireframeShader)
	{
		CGraphicShader* pShader = new CGraphicShader;
		pShader->VertexShader(L"std2d.fx", "VS_Std2D");
		pShader->PixelShader(L"std2d.fx", "PS_Std2D");
		pShader->SetRSType(RS_TYPE::WIRE_FRAME);	
		pShader->SetDSType(DS_TYPE::LESS);		
		pShader->SetBSType(BS_TYPE::DEFAULT);	
		AddAsset(L"2D_WireframeShader", pShader);
	}

	// Debug Shader(2D_DebugShader)
	{
		CGraphicShader* pShader = new CGraphicShader;
		pShader->VertexShader(L"debug2d.fx", "VS_DebugShape");
		pShader->PixelShader(L"debug2d.fx", "PS_DebugShape");
		pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		pShader->SetRSType(RS_TYPE::CULL_NONE);
		pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
		pShader->SetBSType(BS_TYPE::DEFAULT);
		AddAsset(L"2D_DebugShader", pShader);
	}
}

void CAssetMgr::Material()
{
	// Default Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DefaultShader"));
		AddAsset(L"DefaultMaterial", pMaterial);
	}

	// UI Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DefaultShader"));
		AddAsset(L"UIMaterial", pMaterial);
	}

	// Monster Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DefaultShader"));
		AddAsset(L"MonsterMaterial", pMaterial);
	}

	// WireFrame Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_WireframeShader"));
		AddAsset(L"WireframeMaterial", pMaterial);
	}

	// Debug Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DebugShader"));
		AddAsset(L"DebugMaterial", pMaterial);
	}

	// Background Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DefaultShader"));
		AddAsset(L"BackgroundMaterial", pMaterial);
	}
}

void CAssetMgr::Texture()
{
	Ptr<CTexture> pTex = nullptr;

	// Texture
	pTex = LoadTexture(L"cloud", L"Test\\cloud.png");
	pTex = LoadTexture(L"flower", L"Test\\flower.png");
	pTex = LoadTexture(L"bluebird_hit", L"Test\\bluebird_hit.png");
	pTex = LoadTexture(L"penguin_hit", L"Test\\penguin_hit.png");
	// Animation Texture
	pTex = LoadTexture(L"bluebird_jump_atlas", L"Test\\bluebird_jump.png");
	pTex = LoadTexture(L"penguin_jump_atlas", L"Test\\penguin_jump.png");
}

template<typename T>
ASSET_TYPE CAssetMgr::GetAssetType()
{
	const type_info& info = typeid(T);

	ASSET_TYPE type = ASSET_TYPE::END;

	if (&typeid(CMesh) == &info)
		type = ASSET_TYPE::MESH;
	else if (&typeid(CGraphicShader) == &info)
		type = ASSET_TYPE::GRAPHIC_SHADER;
	else if (&typeid(CTexture) == &info)
		type = ASSET_TYPE::TEXTURE;
	else if (&typeid(CMaterial) == &info)
		type = ASSET_TYPE::MATERIAL;

	return type;
}

Ptr<CTexture> CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = nullptr;
	pTex = FindAsset<CTexture>(_strKey).Get();

	// 입력한 Key 값으로 이미 다른 Texture 존재할 경우
	if (nullptr != pTex)
		return pTex;

	wstring strFilePath = M_PATH->GetResourcetPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		MessageBoxA(nullptr, "Texture Load Failed", "Asset Error", MB_OK);
		pTex = nullptr;
		return nullptr;
	}

	pTex->SetName(_strKey);
	pTex->SetAssetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	AddAsset(_strKey, pTex);

	return pTex;
}