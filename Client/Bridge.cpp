#include "stdafx.h"
#include "Bridge.h"
#include "Obj.h"

CBridge::CBridge()
{
}

CBridge::CBridge(CObj * pObj)
	: m_pObj(pObj)
{
}

CBridge::~CBridge()
{
}

void CBridge::SetFrame(wstring & wstrStateKey)
{
	m_wstrStateKey = wstrStateKey;

	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = static_cast<float>(CTextureMgr::GetInstance()->GetImageCount(m_pObj->GetObjKey(), wstrStateKey));
	m_tFrame.fMax = m_tFrame.fCount;
}
