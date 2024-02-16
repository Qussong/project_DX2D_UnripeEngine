#pragma once

class CRenderComponent;

class CTileMap
	: public CRenderComponent
{
	using Super = CRenderComponent;

public:
	CTileMap();
	virtual ~CTileMap();

private:
	uint32			m_iFaceX;				// ���� Ÿ�� ����
	uint32			m_iFaceY;				// ���� Ÿ�� ����
	Vec2			m_v2TileRenderSize;		// Ÿ�� 1ĭ ������
	Vec3			m_v3TileMapWorldPos;	//

	Ptr<CTexture>	m_pTileAtlas;			//

	Vec2			m_v2TilePixelSize;		//

	uint32			m_iMaxCol;				//
	uint32			m_iMaxRow;				//
	uint32			m_iTileIdx;				//

public:
	// Getter
	Ptr<CTexture> GetTileAtlas() { return m_pTileAtlas; }

	// Setter
	void SetTileAtlas(Ptr<CTexture> _atlas, Vec2 _tilePixelSize);

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;
	virtual void Render() override;
};