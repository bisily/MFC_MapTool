#include "stdafx.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Update()
{
	CObj* pTarget = CObjMgr::GetInstance()->FindObj(OBJ_ACTIVE, L"CAR");

	if (nullptr == pTarget)
	{
		return;
	}

	if (m_fOffSetX + 200.f < pTarget->GetInfo()->vPos.x + m_fScrollX)
	{
		m_fScrollX -= 150.f;
	}

	if (m_fOffSetX - 200.f > pTarget->GetInfo()->vPos.x + m_fScrollX)
	{
		m_fScrollX += 150.f;
	}

	if (m_fOffSetY + 200.f < pTarget->GetInfo()->vPos.y + m_fScrollY)
	{
		m_fScrollY -= 150.f;
	}

	if (m_fOffSetY - 200.f > pTarget->GetInfo()->vPos.y + m_fScrollY)
	{
		m_fScrollY += 150.f;
	}
}
