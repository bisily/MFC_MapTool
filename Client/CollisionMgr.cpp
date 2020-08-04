#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Enemy.h"
#include "Player.h"
#include "Car.h"
#include "Boat.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

// Obj가 가지고 있는 렉트로 충돌 체크
void CCollisionMgr::CollisionRect(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	RECT vTem;
	for (auto dst : DstList)
	{
		for (auto src : SrcList)
		{
			if (IntersectRect(&vTem, &dst->GetRect(), &src->GetRect()))
			{
				if (lstrcmp(dst->GetObjKey().c_str(), L"DRUM") &&
					lstrcmp(dst->GetObjKey().c_str(), L"GENERATOR"))
				{
					src->SetHP(-1);
				}
			}
		}
	}
}

//// 적군이 플레이어를 바라보며 총을 쏘는 스프라이트를 취하는 함수
//void CCollisionMgr::CheckLengh(list<CObj*>& DstList, list<CObj*>& SrcList)
//{
//	for (auto dst : DstList)
//	{
//		for (auto src : SrcList)
//		{
//			if (CheckAttack(dst, src))
//			{
//				dynamic_cast<CEnemy*>(src)->SetAttak();
//			}
//			else
//			{
//				dynamic_cast<CEnemy*>(src)->SetOffAttak();
//			}
//		}
//	}
//}

// Obj가 가지고 있는 렉트가 충돌이 되면 Src에 대미지 -1을 세팅하는 함수
void CCollisionMgr::CollisionRectKnifeAttack(CObj * Dst, list<CObj*>& SrcList)
{
	for (auto src : SrcList)
	{
		RECT CollisionRect{};
		if (IntersectRect(&CollisionRect, &Dst->GetRect(), &src->GetRect()))
		{
			dynamic_cast<CPlayer*>(Dst)->SetKnifeAttact();
		}
	}
}

void CCollisionMgr::CollisionAction(CObj * Dst, list<CObj*>& SrcList, CObj* PlayerStandard)
{
	if (KEY_PRESSING(VK_LBUTTON))
	{
		if (!lstrcmp(Dst->GetObjKey().c_str(), L"GUN"))
		{
			for (auto Src : SrcList)
			{
				if (CheckAttackAbleDis(PlayerStandard, Src))
				{
					if (Src->GetRect().left		<= (Dst->GetInfo()->vPos.x - Dst->GetScroll().x) &&
						Src->GetRect().right	>= (Dst->GetInfo()->vPos.x - Dst->GetScroll().x) &&
						Src->GetRect().top		<= (Dst->GetInfo()->vPos.y - Dst->GetScroll().y) &&
						Src->GetRect().bottom	>= (Dst->GetInfo()->vPos.y - Dst->GetScroll().y) &&
						!lstrcmp(Src->GetObjKey().c_str(), L"DRUM"))
					{
						Src->SetHP(-1);
					}
				}
			}
		}
	}

}

void CCollisionMgr::CollisionActionSniper(CObj * Dst, list<CObj*>& SrcList, CObj * PlayerStandard)
{
	if (KEY_PRESSING(VK_LBUTTON))
	{
		if (!lstrcmp(Dst->GetObjKey().c_str(), L"SNIPING"))
		{
			for (auto Src : SrcList)
			{
				if (CheckAttackAbleSniperDis(PlayerStandard, Src))
				{
					if (Src->GetRect().left <= (Dst->GetInfo()->vPos.x - Dst->GetScroll().x) &&
						Src->GetRect().right >= (Dst->GetInfo()->vPos.x - Dst->GetScroll().x) &&
						Src->GetRect().top <= (Dst->GetInfo()->vPos.y - Dst->GetScroll().y) &&
						Src->GetRect().bottom >= (Dst->GetInfo()->vPos.y - Dst->GetScroll().y) &&
						!lstrcmp(Src->GetObjKey().c_str(), L"DRUM"))
					{
						Src->SetHP(-1);
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionMove(CObj * Dst, list<CObj*>& SrcList, CObj* PlayerStadard)
{
	// 마우스의 키값이 HAND일 때
	if (!lstrcmp(Dst->GetObjKey().c_str(), L"HAND"))
	{
		if (KEY_PRESSING(VK_LBUTTON))
		{
			RECT vTemp{};
			for (auto Src : SrcList)
			{
				if (!lstrcmp(Src->GetObjKey().c_str(), L"DRUM") && CheckOverlap(Dst, Src))
				{
					if (IntersectRect(&vTemp, &PlayerStadard->GetRect(), &Src->GetRect()))
					{
						Src->SetPos(D3DXVECTOR3(0.f, 0.f, 0.f));
						dynamic_cast<CPlayer*>(PlayerStadard)->SetDrum(Src);
					}
				}

				else if (!lstrcmp(Src->GetObjKey().c_str(), L"SNIPERRIFLE") && CheckOverlap(Dst, Src))
				{
					if (IntersectRect(&vTemp, &PlayerStadard->GetRect(), &Src->GetRect()))
					{
						dynamic_cast<CPlayer*>(PlayerStadard)->SetGetSniper();
						Src->SetHP(-1);
					}
				}
			}
		}
	}

	if (lstrcmp(Dst->GetObjKey().c_str(), L"GUN") &&
		lstrcmp(Dst->GetObjKey().c_str(), L"HAND"))
	{
		if (!lstrcmp(Dst->GetObjKey().c_str(), L"TAKE"))
		{
			if (KEY_PRESSING(VK_LBUTTON))
			{
				RECT vTemp{};
				for (auto Src : SrcList)
				{
					if (!lstrcmp(Src->GetObjKey().c_str(), L"BOAT"))
					{
						if (IntersectRect(&vTemp, &PlayerStadard->GetRect(), &Src->GetRect()))
						{
							PlayerStadard->SetPos(Src->GetInfo()->vPos);
							PlayerStadard->SetSpeed(0.f);
							PlayerStadard->SetStateKey(L"SitB");
							dynamic_cast<CPlayer*>(PlayerStadard)->SetSit();

							dynamic_cast<CBoat*>(Src)->SetTarget(PlayerStadard);
						}
					}
				}
			}
		}
	}

}

void CCollisionMgr::CollisionCar(CObj * Dst, list<CObj*>& SrcList)
{
	RECT vTem;
	
	for (auto src : SrcList)
	{
		if (lstrcmp(src->GetObjKey().c_str(), L"CAR"))
		{
			continue;
		}

		if (IntersectRect(&vTem, &Dst->GetRect(), &src->GetRect()))
		{
			dynamic_cast<CCar*>(src)->SetTarGet(Dst);
			Dst->SetPos(-100, -100);
		}
	}
}

void CCollisionMgr::CollisionShoot(CObj * Dst, list<CObj*>& SrcList, CObj* PlayerStandard)
{
	// 마우스의 ObjKey 값이 GUN 일때
	if (!lstrcmp(Dst->GetObjKey().c_str(), L"GUN"))
	{
		// 마우스 좌클릭을 했을 때
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
		{
			for (auto Src : SrcList)
			{
				// 플레이어와 적군의 거리가 일정치 일때
				if (CheckAttackAbleDis(PlayerStandard, Src))
				{
					// 좌표가 겹쳤을 때
					if (CheckOverlap(Dst, Src))
					{
						Src->SetHP(-1);
					}
				}
			}
		}
	}
}

// 점 4개로 피킹
bool CCollisionMgr::CheckOverlap(CObj* pDst, CObj* pSrc)
{

	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3((float)pSrc->GetRect().left, (float)pSrc->GetRect().top, 0.f),
		D3DXVECTOR3((float)pSrc->GetRect().right, (float)pSrc->GetRect().top, 0.f),
		D3DXVECTOR3((float)pSrc->GetRect().right, (float)pSrc->GetRect().bottom, 0.f),
		D3DXVECTOR3((float)pSrc->GetRect().left, (float)pSrc->GetRect().bottom, 0.f)
	};

	D3DXVECTOR3		vDirection[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]

	};

	D3DXVECTOR3		vNormal[4] = {

		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f)
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vDestDir = (pDst->GetInfo()->vPos - pDst->GetScroll()) - vPoint[i];
		D3DXVec3Normalize(&vDestDir, &vDestDir);

		float	fDotResult = D3DXVec3Dot(&vDestDir, &vNormal[i]);

		if (fDotResult > 0.f)
			return false;
	}

	return true;
}

bool CCollisionMgr::CheckRect(CObj* pDst, CObj* pSrc)
{
	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3((float)pDst->GetRect().left, (float)pDst->GetRect().top, 0.f),
		D3DXVECTOR3((float)pDst->GetRect().right, (float)pDst->GetRect().top, 0.f),
		D3DXVECTOR3((float)pDst->GetRect().right, (float)pDst->GetRect().bottom, 0.f),
		D3DXVECTOR3((float)pDst->GetRect().left, (float)pDst->GetRect().bottom, 0.f)
	};

	D3DXVECTOR3		vDirection[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]

	};

	D3DXVECTOR3		vNormal[4] = {

		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f)
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vDestDir = pSrc->GetInfo()->vPos - vPoint[i];
		D3DXVec3Normalize(&vDestDir, &vDestDir);

		float	fDotResult = D3DXVec3Dot(&vDestDir, &vNormal[i]);

		if (fDotResult > 0.f)
			return false;
	}

	return true;
}

bool CCollisionMgr::CheckAttack(CObj * pDst, CObj * pSrc)
{
	D3DXVECTOR3 vTempLeng = pDst->GetInfo()->vPos - pSrc->GetInfo()->vPos;

	float Length = D3DXVec3Length(&vTempLeng);
	
	if (Length < 20)
	{
		return true;
	}

	return false;
}

bool CCollisionMgr::CheckAttackAbleDis(CObj * PlayerStandard, CObj* pSrc)
{
	D3DXVECTOR3 vLeng = pSrc->GetInfo()->vPos - PlayerStandard->GetInfo()->vPos;
		
	float Length = D3DXVec3Length(&vLeng);
	
	if (Length <= 300.f)
	{
		return true;
	}
	
	return false;
}

bool CCollisionMgr::CheckAttackAbleSniperDis(CObj * PlayerStandard, CObj* pSrc)
{
	D3DXVECTOR3 vLeng = pSrc->GetInfo()->vPos - PlayerStandard->GetInfo()->vPos;

	float Length = D3DXVec3Length(&vLeng);

	if (Length <= 800.f)
	{
		return true;
	}

	return false;
}
