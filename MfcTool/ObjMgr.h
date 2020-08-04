#pragma once

#include "MainFrm.h"
#include "MfcToolView.h"

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

public:
	void Render();
	void RenderMini();
	void Release();
	void ReleaseObj(OBJID eID);
	void AddObject(CObj* pObj, OBJID eID);

public:
	list<CObj*>& GetBuildingObjList() { return m_ObjList[OBJ_BUILDING]; }
	list<CObj*>& GetPlayerObjList() { return m_ObjList[OBJ_PLAYER]; }
	list<CObj*>& GetEnemyObjList() { return m_ObjList[OBJ_ENEMY]; }
	list<CObj*>& GetActiveObjList() { return m_ObjList[OBJ_ACTIVE]; }

private:
	CObjMgr();
	~CObjMgr();

private:
	// 이터레이터 패턴
	list<CObj*>		m_ObjList[OBJ_END];
};
