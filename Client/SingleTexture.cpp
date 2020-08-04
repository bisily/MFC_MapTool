#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	m_pTexInfo = new TEXINFO;


	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		ERR_MSG(wstrFilePath.c_str());
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		CDevice::GetInstance()->GetDevice()
		, wstrFilePath.c_str()
		, m_pTexInfo->tImgInfo.Width
		, m_pTexInfo->tImgInfo.Height
		, m_pTexInfo->tImgInfo.MipLevels
		, 0
		, m_pTexInfo->tImgInfo.Format
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, NULL
		, &m_pTexInfo->tImgInfo
		, NULL
		, &m_pTexInfo->pTexture)))
	{
		ERR_MSG(L"Single Texture Image Load Failed");
		return E_FAIL;
	}


	return S_OK;
}

const TEXINFO * CSingleTexture::GetTexture(const wstring & wstrStateKey, const int & iCount)
{
	return m_pTexInfo;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}
