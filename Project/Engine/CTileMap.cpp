#include "pch.h"
#include "CTileMap.h"

CTileMap::CTileMap()
	: Super(COMPONENT_TYPE::TILEMAP)
	, m_iFaceXCnt(2)
	, m_iFaceYCnt(2)
	, m_v2TileRenderSize(Vec2(128.f, 128.f))
	, m_iMaxCol(0)
	, m_iMaxRow(0)
	, m_iTileIdx(47)	// 타일 48개
	, m_pTileInfoBuffer(nullptr)
{
	SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(M_ASSET->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_pTileInfoBuffer = new CStructuredBuffer;
	SetFaceCnt(m_iFaceXCnt, m_iFaceYCnt);
}

CTileMap::~CTileMap()
{
	if (nullptr != m_pTileInfoBuffer)
		delete m_pTileInfoBuffer;
}

void CTileMap::SetTileAtlas(Ptr<CTexture> _atlas, Vec2 _tilePixelSize)
{
	m_pTileAtlas = _atlas;
	m_v2TilePixelSize = _tilePixelSize;

	m_iMaxCol = m_pTileAtlas->GetWidth() / (uint32)m_v2TilePixelSize.x;
	m_iMaxRow = m_pTileAtlas->GetHeight() / (uint32)m_v2TilePixelSize.y;

	m_v2SliceSizeUV = Vec2(m_v2TilePixelSize.x / m_pTileAtlas->GetWidth(), 
							m_v2TilePixelSize.y / m_pTileAtlas->GetHeight());
}

void CTileMap::SetFaceCnt(uint32 _faceX, uint32 _faceY)
{
	m_iFaceXCnt = _faceX;
	m_iFaceYCnt = _faceY;

	vector<tTileInfo> vecTemp;
	m_vecTileInfo.swap(vecTemp);
	m_vecTileInfo.resize(_faceX * _faceY);

	m_pTileInfoBuffer->Create(sizeof(tTileInfo), _faceX * _faceY, SB_TYPE::READ_ONLY, true);
}

void CTileMap::SetTileIndex(uint32 _row, uint32 _col, uint32 _imgIdx)
{
	if (nullptr == m_pTileAtlas)
		return;

	UINT idx = _row * m_iFaceXCnt + _col;

	// 렌더링할 타일 정보
	UINT iRow = _imgIdx / m_iMaxCol;
	UINT iCol = _imgIdx % m_iMaxCol;

	m_vecTileInfo[idx].v2LeftTopUV = Vec2((iCol * m_v2TilePixelSize.x) / m_pTileAtlas->GetWidth()
		, (iRow * m_v2TilePixelSize.y) / m_pTileAtlas->GetHeight());

	m_vecTileInfo[idx].bRender = 1;
}

void CTileMap::FinalTick()
{
	// 타일 개수 * 타일 사이즈 = 사이즈
	Vec3 v3TileMapSize = Vec3(m_iFaceXCnt * m_v2TileRenderSize.x, m_iFaceYCnt * m_v2TileRenderSize.y, 1.f);
	GetOwner()->Transform()->SetLocalScale(v3TileMapSize);
}

void CTileMap::UpdateData()
{
	//
}

void CTileMap::Render()
{
	// 재질에 아틀라스 텍스쳐 전달.
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_pTileAtlas);

	// 타일의 가로 세로 개수
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_iFaceXCnt);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, m_iFaceYCnt);

	// 아틀라스 이미지에서 타일 1개의 자르는 사이즈(UV 기준)
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, m_v2SliceSizeUV);

	// 각 타일 정보를 구조화 버퍼로 이동
	m_pTileInfoBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	// 타일 구조화 버퍼를 t20 에 바인딩
	m_pTileInfoBuffer->UpdateData(20);

	// 재질 업데이트
	GetMaterial()->UpdateData();
	GetOwner()->Transform()->UpdateData();
	GetMesh()->Render();
}