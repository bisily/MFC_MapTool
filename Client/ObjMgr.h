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
	// ���ͷ����� ����
	list<CObj*>		m_ObjList[OBJ_END];

	// �� ��ü�� ��� ������ �����ϱ� ���� ���� �迭.
	vector<CObj*>	m_vecRender[END];

	bool			m_bClearContion = false;
};
