#pragma once

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
	SINGLETON(CCollisionMgr);

private:
	bool					m_arr2LayerCollisionConfig[LAYER_MAX][LAYER_MAX];
	map<UINT_PTR, bool>		m_mapCollsionRecord;		// �浹���� ����(key : �� �浹ü�� id����, value : ���� ������ �浹 ����Ȯ�ο뵵)

private:
	void CollisionBtwLayer(UINT _left, UINT _right);	
	bool CollisionBtwCollider(CCollider2D* _left, CCollider2D* _right);	// true = �浹, false = ���浹

	// OBB
	bool ObbRectRect(const Matrix& _matRect1, const Matrix& _matRect2);
	bool ObbCircleCircle(const Matrix& _matCircle1, const Matrix& _matCircle2);
	bool ObbRectCircle(const Matrix& _matRect, const Matrix& _matCircle);

public:
	void LayerCheck(LAYER_TYPE _left, LAYER_TYPE _right);								// �浹����
	void LayerCheck(const wstring& _leftLayerName, const wstring& _rightLayerName);		// �浹����
	void Clear();

public:
	void Tick();
};