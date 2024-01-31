#pragma once

class CCollider2D
	: public CComponent
{
	using Super = CComponent;

public:
	CCollider2D();
	virtual ~CCollider2D();

private:
	Vec3				m_v3OffsetPos;		// �浹ü�� ���� ��ġ
	Vec3				m_v3OffsetScale;	// �浹ü�� ���� ������
	int32				m_iCollisionCnt;	// �ٸ� �浹ü�� �浹���� Ƚ��
	bool				m_bAbsolute;		// �����ڷκ��� Scale ���� (�⺻ �� : false = �������)
	Matrix				m_matColWorld;		// �浹ü�� ���� ���
	COLLIDER2D_TYPE		m_eType;

public:
	// Getter
	bool IsAbsolute() { return m_bAbsolute; }
	Vec2 GetOffsetPos() { return Vec2(m_v3OffsetPos.x, m_v3OffsetPos.y); }
	Vec2 GetOffsetScale() { return Vec2(m_v3OffsetScale.x, m_v3OffsetScale.y); }
	COLLIDER2D_TYPE GetColliderType() { return m_eType; }

	// Setter
	void SetAbsolute(bool _absolute) { m_bAbsolute = _absolute; }
	void SetOffsetPos(Vec2 _pos) { m_v3OffsetPos = Vec3(_pos.x, _pos.y, 0.f); }
	void SetOffsetPos(Vec3 _pos) { m_v3OffsetPos = _pos; }
	void SetOffsetScale(Vec2 _scale) { m_v3OffsetScale = Vec3(_scale.x, _scale.y, 1.f); }
	void SetOffsetScale(Vec3 _scale) { m_v3OffsetScale = _scale; }
	void SetColliderType(COLLIDER2D_TYPE _type) { m_eType = _type; }

public:
	virtual void Begin() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override;
	virtual void UpdateData() override {}
};