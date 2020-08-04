#pragma once
#include "Obj.h"
class CCar :
	public CObj
{
public:
	CCar();
	virtual ~CCar();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	SetTarGet(CObj* pObj) { 
		if (nullptr == m_pTarget)
		{
			m_bIsExist = true;
			m_pTarget = pObj;
			m_pTarget->SetSpeed(0.f);
		}

		CSoundMgr::GetInstance()->PlayerSound(L"PowerOn.wav", CSoundMgr::CHANNEL_BOMB);
	}

public:
	CObj*	GetTargetInfo() 
	{ 
		if (nullptr == m_pTarget)
		{
			return nullptr;
		}

		return m_pTarget; 
	}

private:
	void	DrawRect();
	void	KeyCheck();

private:
	D3DXMATRIX			matScale, matTrans;
	CObj*				m_pTarget = nullptr;
	bool				m_bIsExist = false;
	bool				m_bDriveStart = false;
	double				m_iTime = 0;
};

