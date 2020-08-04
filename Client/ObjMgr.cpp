#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Back.h"
#include "Building.h"
#include "Enemy.h"
#include "Player.h"
#include "Mouse.h"
#include "UI.h"
#include "Effect.h"
#include "Drum.h"
#include "Generator.h"
#include "MathMgr.h"
#include "Car.h"
#include "Boat.h"
#include "SniperRifle.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(CObj * pObj, OBJID eID)
{
	m_ObjList[eID].push_back(pObj);
}

HRESULT CObjMgr::Initialize()
{
	if (FAILED(LoadObject(L"../Data/Object.dat")))
	{
		ERR_MSG(L"Object Load Failed!!");
		return E_FAIL;
	}

	if (FAILED(LoadPlayer(L"../Data/Player.dat")))
	{
		ERR_MSG(L"Player Load Failed!!");
		return E_FAIL;
	}

	if (FAILED(LoadEnemy(L"../Data/TestCase4.dat")))
	{
		ERR_MSG(L"Enenmy Load Failed!!");
		return E_FAIL;
	}

	AddObject(CObjFactory<CBack>::CreateObj(), OBJ_BACK);
	AddObject(CObjFactory<CMouse>::CreateObj(), OBJ_MOUSE);
	AddObject(CObjFactory<CUI>::CreateObj(), OBJ_UI);
	AddObject(CObjFactory<CCar>::CreateObj(), OBJ_ACTIVE);
	AddObject(CObjFactory<CBoat>::CreateObj(), OBJ_ACTIVE);
	AddObject(CObjFactory<CSniperRifle>::CreateObj(), OBJ_ITEM);

	 dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->SetMouse(m_ObjList[OBJ_MOUSE].back());

	 list<CObj*>::iterator begin_Enemy = m_ObjList[OBJ_ENEMY].begin();
	 list<CObj*>::iterator end_Enemy = m_ObjList[OBJ_ENEMY].end();

	 for (; begin_Enemy != end_Enemy; ++begin_Enemy)
	 {
		/*dynamic_cast<CEnemy*>(m_ObjList[OBJ_ENEMY].back())->SetTaret(m_ObjList[OBJ_PLAYER].back());*/
		 dynamic_cast<CEnemy*>(*begin_Enemy)->SetTaret(m_ObjList[OBJ_PLAYER].back());
	 }

	return S_OK;
}

int CObjMgr::Progress()
{
	if (KEY_PRESSING('F'))
	{
		m_bClearContion = TRUE;
	}

	int iResult = 0;

	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator begin = m_ObjList[i].begin();
		list<CObj*>::iterator end = m_ObjList[i].end();

		for (; begin != end; )
		{
			iResult = (*begin)->Progress();

			if (1 == iResult)
			{
				begin = m_ObjList[i].erase(begin);
			}
			else
				++begin;
		}
	}

	// 플레이어가 적군을 칼로 공격 시 충돌 처리
	CCollisionMgr::GetInstance()->CollisionRectKnifeAttack(m_ObjList[OBJ_PLAYER].back(), m_ObjList[OBJ_ENEMY]);
	
	// 플레이어가 적군을 총으로 쐈을 경우 충돌 처리
	CCollisionMgr::GetInstance()->CollisionShoot(m_ObjList[OBJ_MOUSE].back(), m_ObjList[OBJ_ENEMY], m_ObjList[OBJ_PLAYER].back());
	
	// 플레이어가 총을 꺼낸 상태에서 마우스와 Object 충돌 처리
	CCollisionMgr::GetInstance()->CollisionAction(m_ObjList[OBJ_MOUSE].back(), m_ObjList[OBJ_ACTIVE], m_ObjList[OBJ_PLAYER].back());
	
	// 스나이퍼 
	CCollisionMgr::GetInstance()->CollisionActionSniper(m_ObjList[OBJ_MOUSE].back(), m_ObjList[OBJ_ACTIVE], m_ObjList[OBJ_PLAYER].back());

	// 마우스 충돌
	CCollisionMgr::GetInstance()->CollisionMove(m_ObjList[OBJ_MOUSE].back(), m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER].back());

	// 드럼통을 옮기 때
	CCollisionMgr::GetInstance()->CollisionMove(m_ObjList[OBJ_MOUSE].back(), m_ObjList[OBJ_ACTIVE], m_ObjList[OBJ_PLAYER].back());

	// Active object와 적군의 충돌
	CCollisionMgr::GetInstance()->CollisionRect(m_ObjList[OBJ_ACTIVE], m_ObjList[OBJ_ENEMY]);
	
	
	if (m_bClearContion)
	{
		CCollisionMgr::GetInstance()->CollisionCar(m_ObjList[OBJ_PLAYER].back(), m_ObjList[OBJ_ACTIVE]);
	}
	
	CScrollMgr::GetInstance()->Update();

	if (!m_ObjList[OBJ_EFFECT].empty())
	{
		CCollisionMgr::GetInstance()->CollisionRect(m_ObjList[OBJ_EFFECT], m_ObjList[OBJ_ACTIVE]);
		CCollisionMgr::GetInstance()->CollisionRect(m_ObjList[OBJ_EFFECT], m_ObjList[OBJ_ENEMY]);
	}

	return iResult;
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator begin = m_ObjList[i].begin();
		list<CObj*>::iterator end = m_ObjList[i].end();
		for (; begin != end; ++begin)
		{
			if (RENDER_OBJ == (*begin)->GetLayer())
			{
				// Y 소팅할 객체들을 vector에 담아 놓고 출력은 미룬다.
				m_vecRender[RENDER_OBJ].push_back(*begin);
				continue;
			}

			if (RENDER_EFFECT == (*begin)->GetLayer())
			{
				// Y 소팅할 객체들을 vector에 담아 놓고 출력은 미룬다.
				m_vecRender[RENDER_EFFECT].push_back(*begin);
				continue;
			}

			if (RENDER_UI == (*begin)->GetLayer())
			{
				// Y 소팅할 객체들을 vector에 담아 놓고 출력은 미룬다.
				m_vecRender[RENDER_UI].push_back(*begin);
				continue;
			}

			if (KEY_PRESSING('E'))
			{
				Rectangle(hDC
					, (*begin)->GetRect().left + (int)(*begin)->GetScroll().x
					, (*begin)->GetRect().top + (int)(*begin)->GetScroll().y
					, (*begin)->GetRect().right + (int)(*begin)->GetScroll().x
					, (*begin)->GetRect().bottom + (int)(*begin)->GetScroll().y);
			}

			(*begin)->Render(hDC);

		}
	}

	// vector에 담긴 그룹별로 Y소팅을 진행한다.
	for (int i = 0; i < END; ++i)
	{
		sort(m_vecRender[i].begin(), m_vecRender[i].end(), LessY<CObj*>);

		for (auto obj : m_vecRender[i])
		{
			if (KEY_PRESSING('E'))
			{
				Rectangle(hDC
					, obj->GetRect().left + (int)obj->GetScroll().x
					, obj->GetRect().top + (int)obj->GetScroll().y
					, obj->GetRect().right + (int)obj->GetScroll().x
					, obj->GetRect().bottom + (int)obj->GetScroll().y);
			}

			obj->Render(hDC);
		}

		m_vecRender[i].clear();
	}


}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto List : m_ObjList[i])
		{
			Safe_Delete(List);
		}
		m_ObjList[i].clear();
	}
}

void CObjMgr::ReleaseObj(OBJID eID)
{
}

HRESULT CObjMgr::LoadObject(const wstring& wstrPath)
{

	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);


	HANDLE	hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	TCHAR szBuffer[MIN_STR] = L"";
	D3DXVECTOR3 vPos;

	while (true)
	{
		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);

		if (dwByte == 0)
		{
			break;
		}

		if (!lstrcmp(szBuffer, L"Drum_0"))
		{
			CObjMgr::GetInstance()->AddObject(CObjFactory<CDrum>::CreateObj(vPos, szBuffer), OBJ_ACTIVE);
		}
		else if (!lstrcmp(szBuffer, L"Generator_0"))
		{
			CObjMgr::GetInstance()->AddObject(CObjFactory<CGenerator>::CreateObj(vPos, szBuffer), OBJ_ACTIVE);
		}
		else
		{
			CObjMgr::GetInstance()->AddObject(CObjFactory<CBuilding>::CreateObj(vPos, szBuffer), OBJ_BUILDING);
		}
	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CObjMgr::LoadEnemy(const wstring & wstrPath)
{
	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);


	HANDLE	hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	TCHAR szBuffer[MIN_STR] = L"";
	TCHAR szBuffer2[MIN_STR] = L"";
	TCHAR szBuffer3[MIN_STR] = L"";
	TCHAR szBuffer4[MIN_STR] = L"";

	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vRotate;

	while (true)
	{
		/*ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);

		if (dwByte == 0)
		{
			break;
		}

		CObjMgr::GetInstance()->AddObject(CObjFactory<CEnemy>::CreateObj(vPos, szBuffer), OBJ_ENEMY);*/

		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		if (dwByte == 0)
		{
			break;
		}

		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);
		
		if (dwByte == 0)
		{
			break;
		}

		ReadFile(hFile, szBuffer2, MIN_STR, &dwByte, NULL);
		
		if (dwByte == 0)
		{
			break;
		}
		ReadFile(hFile, szBuffer3, MIN_STR, &dwByte, NULL);
		
		if (dwByte == 0)
		{
			break;
		}

		ReadFile(hFile, szBuffer4, MIN_STR, &dwByte, NULL);

		const wstring wstrTemp = szBuffer2;
		CString wstrTemp2 = "ENEMY";

		

		CObjMgr::GetInstance()->AddObject(CObjFactory<CEnemy>::CreateObj(vPos, wstrTemp2, wstrTemp), OBJ_ENEMY);

		if (!lstrcmp(szBuffer4, L"RotateMode"))
		{
			lstrcpy(szBuffer3, L"NEXT");

			
			while (lstrcmp(szBuffer3, L"END"))
			{
				ReadFile(hFile, vRotate, sizeof(D3DXVECTOR2), &dwByte, NULL);

				dynamic_cast<CEnemy*>(m_ObjList[OBJ_ENEMY].back())->SetRotate(vRotate);

				ReadFile(hFile, szBuffer3, MIN_STR, &dwByte, NULL);
			}

			dynamic_cast<CEnemy*>(m_ObjList[OBJ_ENEMY].back())->SetMaxRotateSize();
		}
	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CObjMgr::LoadPlayer(const wstring & wstrPath)
{
	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);


	HANDLE	hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	TCHAR szBuffer[MIN_STR] = L"";
	TCHAR szBuffer2[MIN_STR] = L"";
	D3DXVECTOR3 vPos;

	while (true)
	{
		//ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
		//ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);
		//ReadFile(hFile, szBuffer2, MIN_STR, &dwByte, NULL);

		//if (dwByte == 0)
		//{
		//	break;
		//}

		//CObjMgr::GetInstance()->AddObject(CObjFactory<CPlayer>::CreateObj(vPos, szBuffer), OBJ_PLAYER);

		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);
		ReadFile(hFile, szBuffer2, MIN_STR, &dwByte, NULL);

		const wstring wstrTemp = szBuffer2;
		CString wstrTemp2 = szBuffer;

		if (dwByte == 0)
		{
			break;
		}

		CObjMgr::GetInstance()->AddObject(CObjFactory<CPlayer>::CreateObj(vPos, wstrTemp2, wstrTemp), OBJ_PLAYER);
	}

	CloseHandle(hFile);

	return S_OK;
}

const vector<TILE*>* CObjMgr::GetTile(void)
{
	return dynamic_cast<CBack*>(m_ObjList[OBJ_BACK].front())->GetTile();
}

CObj * CObjMgr::FindObj(OBJID eObj, CString wstrObjKey)
{

	list<CObj*>::iterator begin =  m_ObjList[eObj].begin();
	list<CObj*>::iterator end = m_ObjList[eObj].end();

	for (; begin != end; ++begin)
	{
		if ((*begin)->GetObjKey().c_str() == wstrObjKey)
		{
			return *begin;
		}
	}

	return nullptr;
}
