#pragma once
class CRay
{
public:
	CRay();
	~CRay();

public:
	enum eRaySpace
	{
		E_NONE
		, E_VIEW
		, E_WORLD
		, E_LOCAL
	};

protected:
	D3DXVECTOR3		m_vOriginal;	// ���� �������
	D3DXVECTOR3		m_vDirection;	// ���� ����
	SPHER			m_tagRay;		// ���� ??? ��� �ȴٰ�?
};

