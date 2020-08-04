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
	D3DXVECTOR3		m_vOriginal;	// 광선 출발지점
	D3DXVECTOR3		m_vDirection;	// 광선 방향
	SPHER			m_tagRay;		// 종류 ??? 없어도 된다고?
};

