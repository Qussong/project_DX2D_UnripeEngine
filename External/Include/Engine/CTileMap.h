#pragma once

class CRenderComponent;
class CStructuredBuffer;

class CTileMap
	: public CRenderComponent
{
	using Super = CRenderComponent;

public:
	CTileMap();
	virtual ~CTileMap();

private:
	uint32				m_iFaceXCnt;			// 가로 타일 개수
	uint32				m_iFaceYCnt;			// 세로 타일 개수
	Vec2				m_v2TileRenderSize;		// 타일 1칸 사이즈
	Vec3				m_v3TileMapWorldPos;	//

	Ptr<CTexture>		m_pTileAtlas;			//
	Vec2				m_v2TilePixelSize;		//
	Vec2				m_v2SliceSizeUV;		//

	uint32				m_iMaxCol;				//
	uint32				m_iMaxRow;				//
	uint32				m_iTileIdx;				// Atlas Tex 안의 Tile 개수

	vector<tTileInfo>	m_vecTileInfo;
	CStructuredBuffer*	m_pTileInfoBuffer;

public:
	// Getter
	Ptr<CTexture>	GetTileAtlas()	{ return m_pTileAtlas; }
	UINT			GetFaceX()		{ return m_iFaceXCnt; }
	UINT			GetFaceY()		{ return m_iFaceYCnt; }

	// Setter
	void SetTileAtlas(Ptr<CTexture> _atlas, Vec2 _tilePixelSize);
	void SetFaceCnt(uint32 _faceX, uint32 _faceY);
	void SetTileIndex(uint32 _row, uint32 _col, uint32 _imgIdx);
	void SetTileRenderSize(Vec2 _size) { m_v2TileRenderSize = _size; }

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;
	virtual void Render() override;
};