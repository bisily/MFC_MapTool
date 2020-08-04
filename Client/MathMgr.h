#pragma once

class CObj;
class CMathMgr
{
	DECLARE_SINGLETON(CMathMgr)
	
public:
	float CalcDistance(D3DXVECTOR3 vecDst, D3DXVECTOR3 vecSrc);


private:
	CMathMgr();
	virtual ~CMathMgr();
};

