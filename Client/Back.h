#pragma once
#include "Obj.h"
class CBack :
	public CObj
{
public:
	CBack();
	virtual ~CBack();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void)	override;
	virtual int Progress(void)			override;
	virtual void Render(HDC hDC)		override;
	virtual void Release(void)			override;

public:
	const vector<TILE*>*	GetTile(void) { return &m_vecTile; }

private:
	void		LoadTile(const wstring& wstrPath);

private:
	vector<TILE*>			m_vecTile;
	int						m_iTileRenderX = 0;
	int						m_iTileRenderY = 0;
};

