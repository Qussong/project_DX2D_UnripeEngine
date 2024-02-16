#include "pch.h"
#include "CTileMap.h"

CTileMap::CTileMap()
	: Super(COMPONENT_TYPE::TILEMAP)
	, m_iFaceX(2)
	, m_iFaceY(2)
	, m_v2TileRenderSize(Vec2(128.f, 128.f))
	, m_iMaxCol(0)
	, m_iMaxRow(0)
	, m_iTileIdx(0)
{
	SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(M_ASSET->FindAsset<CMaterial>(L"TileMapMtrl"));
}

CTileMap::~CTileMap()
{
}

void CTileMap::SetTileAtlas(Ptr<CTexture> _atlas, Vec2 _tilePixelSize)
{
	m_pTileAtlas = _atlas;
	m_v2TilePixelSize = _tilePixelSize;

	m_iMaxCol = m_pTileAtlas->GetWidth() / (uint32)m_v2TilePixelSize.x;
	m_iMaxRow = m_pTileAtlas->GetHeight() / (uint32)m_v2TilePixelSize.y;
}

void CTileMap::FinalTick()
{
	// 타일 개수 * 타일 사이즈 = 사이즈
	Vec3 v3TileMapSize = Vec3(m_iFaceX * m_v2TileRenderSize.x, m_iFaceY * m_v2TileRenderSize.y, 1.f);
	GetOwner()->Transform()->SetLocalScale(v3TileMapSize);
}

void CTileMap::UpdateData()
{
	//
}

void CTileMap::Render()
{
	// Material 에 Atlas Texture 전달
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_pTileAtlas);

	// 렌더링할 타일 정보
	uint32 iRow = m_iTileIdx / m_iMaxRow;
	uint32 iCol = m_iTileIdx / m_iMaxCol;
	
	Vec2 v2LeftTopUV = Vec2((iCol * m_v2TilePixelSize.x) / m_pTileAtlas->GetWidth(),
							(iRow * m_v2TilePixelSize.y) / m_pTileAtlas->GetHeight());

	Vec2 v2SliceSizeUV = Vec2(m_v2TilePixelSize.x / m_pTileAtlas->GetWidth(),
							  m_v2TilePixelSize.y / m_pTileAtlas->GetHeight());

	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, v2LeftTopUV);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_1, v2SliceSizeUV);
	GetMaterial()->UpdateData();

	GetOwner()->Transform()->UpdateData();
	GetMesh()->Render();
}