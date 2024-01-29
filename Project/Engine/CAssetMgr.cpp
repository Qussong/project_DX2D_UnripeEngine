#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
	//for (size_t i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	//{
	//	for (pair<wstring, Ptr<CAsset>> pair : m_mapAsset[i])
	//	{
	//		if (nullptr != pair.second)
	//		{
	//			delete pair.second;
	//			pair.second = nullptr;
	//		}
	//	}
	//	m_mapAsset[i].clear();
	//}
}

void CAssetMgr::Init()
{
	Mesh();		// Mesh ����
	Shader();	// shader ����
	Material();	// Material ����
}

void CAssetMgr::Mesh()
{
	// Rect Mesh
	{
		Vtx		arrRect[4] = {};
		UINT	arrIdx[6] = {};

		// ���� ���� �Է�
		{
			// �簢�� ���� ��ġ ����
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

		// �ε��� ���� �Է�
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
	}

	// Circle Mesh
	{
		vector<Vtx> vecCircle;
		vector<UINT> vecIdx;

		// ���� ���� �Է�
		// �߽���
		Vtx center;
		center.v3Pos = Vec3(0.f, 0.f, 0.f);
		center.v4Color = Vec4(0.5f, 0.f, 0.5f, 1.f);
		center.v2UV = Vec2(0.5f, 0.5f);
		vecCircle.push_back(center);

		// �� �ѷ�
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

		// �ε��� ���� �Է�
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
	}
}

void CAssetMgr::Shader()
{
	// Default Shader(2D_DefaultShader)
	{
		CGraphicShader* pShader = new CGraphicShader;
		pShader->VertexShader(L"std2d.fx", "VS_Std2D");
		pShader->PixelShader(L"std2d.fx", "PS_Std2D");
		pShader->SetRSType(RS_TYPE::CULL_NONE);	// default = CULL_BACK
		pShader->SetDSType(DS_TYPE::LESS);		// default = LESS
		pShader->SetBSType(BS_TYPE::DEFAULT);	// default = DEFAULT
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
}

void CAssetMgr::Material()
{
	// Default Material
	{
		CMaterial* pMaterial = new CMaterial;
		
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_DefaultShader"));
		AddAsset(L"DefaultMaterial", pMaterial);
	}

	// WireFrame Material
	{
		CMaterial* pMaterial = new CMaterial;
		pMaterial->SetShader(FindAsset<CGraphicShader>(L"2D_WireframeShader"));
		AddAsset(L"WireframeMaterial", pMaterial);
	}
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
	CTexture* pTex = FindAsset<CTexture>(_strKey).Get();

	// �Է��� Key ������ �̹� �ٸ� Texture ������ ���
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

	pTex->SetAssetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	AddAsset(_strKey, pTex);

	return pTex;
}