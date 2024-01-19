#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	for (size_t i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		for (pair<wstring, CAsset*> pair : m_mapAsset[i])
		{
			if (nullptr != pair.second)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}
		m_mapAsset[i].clear();
	}
}

void CAssetMgr::Init()
{
	Mesh();		// Mesh 생성
	Shader();	// shader 생성
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
			arrRect[0].v2UV = Vec2{ -1.f, 1.f };

			arrRect[1].v3Pos = Vec3{ 0.5f, 0.5f, 0.f };
			arrRect[1].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
			arrRect[1].v2UV = Vec2{ 1.f, 1.f };

			arrRect[2].v3Pos = Vec3{ 0.5f, -0.5f, 0.f };
			arrRect[2].v4Color = Vec4{ 0.5f, 0.f, 0.5f, 1.f };
			arrRect[2].v2UV = Vec2{ 1.f, -1.f };

			arrRect[3].v3Pos = Vec3{ -0.5f, -0.5f, 0.f };
			arrRect[3].v4Color = Vec4{ 0.f, 0.5f, 0.5f, 1.f };
			arrRect[3].v2UV = Vec2{ -1.f, -1.f };
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
	}

	// Circle Mesh
	{
		vector<Vtx> vecCircle;
		vector<UINT> vecIdx;

		// 정점 정보 입력
		// 중심점
		Vtx center;
		center.v3Pos = Vec3(0.f, 0.f, 0.f);
		center.v4Color = Vec4(0.5f, 0.f, 0.5f, 1.f);
		center.v2UV = Vec2(0.5f, 0.5f);
		vecCircle.push_back(center);

		// 원 둘레
		Vtx		temp;
		int32	iSlice = 100;
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
			vecIdx.push_back(i + 2);
			vecIdx.push_back(i + 1);
		}
		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(iSlice);

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
	CGraphicShader* pShader = new CGraphicShader;

	pShader->VertexShader(L"std2d.fx", "VS_Std2D");
	pShader->PixelShader(L"std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::WIRE_FRAME);	// default = CULL_BACK
	pShader->SetDSType(DS_TYPE::LESS);		// default = LESS
	pShader->SetBSType(BS_TYPE::DEFAULT);	// default = DEFAULT

	AddAsset(L"Std2DShader", pShader);
}