#pragma once

#include "Scene.h"

class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	CScene*		m_pScene = nullptr;

public:
	HRESULT		SetScene(SCENEID eScene);
	int			Progress();
	void		Render(HDC hDC);
	void		Release();

private:
	CSceneMgr();
	~CSceneMgr();
};

