#include "stdafx.h"
#include "Obj.h"

D3DXVECTOR3		CObj::m_vScroll{};

CObj::CObj()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}


CObj::~CObj()
{
}
