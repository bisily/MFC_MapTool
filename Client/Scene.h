#pragma once

#include "Include.h"

class CScene
{
public:
	virtual HRESULT		Initialize()	PURE;
	virtual int			Progress()		PURE;
	virtual void		Render(HDC hDC) PURE;
	virtual void		Release()		PURE;

public:
	CScene();
	virtual ~CScene();
};

