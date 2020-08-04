#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "MainFrm.h"
#include "MfcToolView.h"

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

void CObjMgr::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator begin = m_ObjList[i].begin();

		list<CObj*>::iterator end = m_ObjList[i].end();
		for (; begin != end; ++begin)
		{
			(*begin)->Render();
		}
	}
}

void CObjMgr::RenderMini()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator begin = m_ObjList[i].begin();
		list<CObj*>::iterator end = m_ObjList[i].end();
		for (; begin != end; ++begin)
		{
			(*begin)->Render();
		}
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

