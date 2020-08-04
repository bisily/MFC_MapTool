#pragma once

#include "Obj.h"

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

public:
	HRESULT		Initialize();
	int			Progress();
	void		Render(HDC hDC);
	void		Release();
	
	
public:
	void ReleaseObj(OBJID eID);
	void AddObject(CObj* pObj, OBJID eID);
	void SetClearContion() { m_bClearContion = true; }

public:
	list<CObj*>& GetBuildingObjList() { return m_ObjList[OBJ_BUILDING]; }
	CObj* FindObj(OBJID eObj, CString wstrObjKey);
	const vector<TILE*>* GetTile(void);
	const CObj* GetObj(OBJID eObj) { return m_ObjList[eObj].front(); }
	bool GetClaerContion() { return m_bClearContion; }

private:
	HRESULT LoadObject(const wstring& wstrPath);
	HRESULT LoadEnemy(const wstring& wstrPath);
	HRESULT LoadPlayer(const wstring& wstrPath);

private:
	CObjMgr();
	~CObjMgr();

private:
	// 이터레이터 패턴
	list<CObj*>		m_ObjList[OBJ_END];

	// 각 객체의 출력 순서를 정렬하기 위한 벡터 배열.
	vector<CObj*>	m_vecRender[END];

	bool			m_bClearContion = false;
};
