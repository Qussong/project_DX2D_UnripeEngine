#pragma once

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
	SINGLETON(CCollisionMgr);

private:
	bool					m_arr2LayerCollisionConfig[LAYER_MAX][LAYER_MAX];
	map<UINT_PTR, bool>		m_mapCollsionRecord;		// 충돌여부 저장(key : 두 충돌체의 id조합, value : 이전 프레임 충돌 여부확인용도)

private:
	void CollisionBtwLayer(UINT _left, UINT _right);	
	bool CollisionBtwCollider(CCollider2D* _left, CCollider2D* _right);	// true = 충돌, false = 비충돌

public:
	void LayerCheck(LAYER_TYPE _left, LAYER_TYPE _right);								// 충돌설정
	void LayerCheck(const wstring& _leftLayerName, const wstring& _rightLayerName);		// 충돌설정
	void Clear();

public:
	void Tick();
};