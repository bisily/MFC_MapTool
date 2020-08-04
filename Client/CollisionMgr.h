#pragma once

class CObj;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	void CollisionRect(list<CObj*>& DstList, list<CObj*>& SrcList);
	//void CheckLengh(list<CObj*>& DstList, list<CObj*>& SrcList);
	void CollisionShoot(CObj* Dst, list<CObj*>& SrcList, CObj* PlayerStandard);
	void CollisionRectKnifeAttack(CObj* Dst, list<CObj*>& SrcList);
	void CollisionAction(CObj* Dst, list<CObj*>& SrcList, CObj* PlayerStandard);
	void CollisionActionSniper(CObj* Dst, list<CObj*>& SrcList, CObj* PlayerStandard);
	void CollisionMove(CObj* Dst, list<CObj*>& SrcList, CObj* PlayerStadard);
	void CollisionCar(CObj* Dst, list<CObj*>& SrcList);

private:
	bool CheckOverlap(CObj* pDst, CObj* pSrc);
	bool CheckRect(CObj * pDst, CObj * pSrc);
	bool CheckAttack(CObj * pDst, CObj * pSrc);
	bool CheckAttackAbleDis(CObj* PlayerStandard, CObj* pSrc);
	bool CheckAttackAbleSniperDis(CObj * PlayerStandard, CObj* pSrc);
};

