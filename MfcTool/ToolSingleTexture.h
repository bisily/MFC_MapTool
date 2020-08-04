#pragma once
#include "ToolTexture.h"
class CToolSingleTexture :
	public CToolTexture
{
public:
	CToolSingleTexture();
	virtual ~CToolSingleTexture();

public:
	// CToolTexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual const TEXINFO * GetTexture(const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO*			m_pTexInfo = nullptr;
};

