#include "stdafx.h"
#include "MathMgr.h"

IMPLEMENT_SINGLETON(CMathMgr)

CMathMgr::CMathMgr()
{
}


CMathMgr::~CMathMgr()
{
}

float CMathMgr::CalcDistance(D3DXVECTOR3 vecDst, D3DXVECTOR3 vecSrc)
{
	D3DXVECTOR3 vPos = vecDst - vecSrc;

	float fLength = D3DXVec3Length(&vPos);

	return fLength;
}