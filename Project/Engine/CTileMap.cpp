#include "pch.h"
#include "CTileMap.h"

CTileMap::CTileMap()
	: Super(COMPONENT_TYPE::TILEMAP)
	, m_iFaceXCnt(2)
	, m_iFaceYCnt(2)
	, m_v2TileRenderSize(Vec2(128.f, 128.f))
	, m_iMaxCol(0)
	, m_iMaxRow(0)
	, m_iTileIdx(47)	// Ÿ�� 48��
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

	// �������� Ÿ�� ����
	UINT iRow = _imgIdx / m_iMaxCol;
	UINT iCol = _imgIdx % m_iMaxCol;

	m_vecTileInfo[idx].v2LeftTopUV = Vec2((iCol * m_v2TilePixelSize.x) / m_pTileAtlas->GetWidth()
		, (iRow * m_v2TilePixelSize.y) / m_pTileAtlas->GetHeight());

	m_vecTileInfo[idx].bRender = 1;
}

void CTileMap::FinalTick()
{
	// Ÿ�� ���� * Ÿ�� ������ = ������
	Vec3 v3TileMapSize = Vec3(m_iFaceXCnt * m_v2TileRenderSize.x, m_iFaceYCnt * m_v2TileRenderSize.y, 1.f);
	GetOwner()->Transform()->SetLocalScale(v3TileMapSize);
}

void CTileMap::UpdateData()
{
	//
}

void CTileMap::Render()
{
	// ������ ��Ʋ�� �ؽ��� ����.
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_pTileAtlas);

	// Ÿ���� ���� ���� ����
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_iFaceXCnt);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, m_iFaceYCnt);

	// ��Ʋ�� �̹������� Ÿ�� 1���� �ڸ��� ������(UV ����)
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, m_v2SliceSizeUV);

	// �� Ÿ�� ������ ����ȭ ���۷� �̵�
	m_pTileInfoBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	// Ÿ�� ����ȭ ���۸� t20 �� ���ε�
	m_pTileInfoBuffer->UpdateData(20);

	// ���� ������Ʈ
	GetMaterial()->UpdateData();
	GetOwner()->Transform()->UpdateData();
	GetMesh()->Render();
}