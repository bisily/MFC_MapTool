
// MfcToolView.cpp : CMfcToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MfcTool.h"
#endif

#include "MfcToolDoc.h"
#include "MfcToolView.h"
#include "MainFrm.h"
#include "Building.h"
#include "Player.h"
#include "Enemy.h"
#include "Drum.h"
#include "Generator.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CMfcToolView

IMPLEMENT_DYNCREATE(CMfcToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMfcToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMfcToolView ����/�Ҹ�

CMfcToolView::CMfcToolView()
	: m_pDevice(CDevice::GetInstance())
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMfcToolView::~CMfcToolView()
{
}

BOOL CMfcToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMfcToolView �׸���

void CMfcToolView::OnDraw(CDC* /*pDC*/)
{
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	m_pDevice->Render_Begin();

	m_pBackGround->BackGroundRender();
	
	CObjMgr::GetInstance()->Render();
	
	DrawSelectImage();

	m_pDevice->Render_End();
}


// CMfcToolView �μ�

BOOL CMfcToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMfcToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMfcToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMfcToolView ����

#ifdef _DEBUG
void CMfcToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcToolDoc* CMfcToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcToolDoc)));
	return (CMfcToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfcToolView �޽��� ó����
void CMfcToolView::OnDestroy()
{
	CObjMgr::GetInstance()->DestroyInstance();
	Safe_Delete(m_pBackGround);
	CToolTextureMgr::GetInstance()->DestroyInstance();
	m_pDevice->DestroyInstance();
	
	CScrollView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CMfcToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	SetScrollSizes(MM_TEXT, CSize(MAPSIZEX, MAPSIZEY));
	// 1���� : �ȼ����� ������ �ϰڴ�.
	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());
	
	RECT	rcWindow;
	
	pMainFrm->GetWindowRect(&rcWindow); // ������ â �׵θ��� ����� ������ �Լ�
	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView;
	GetClientRect(&rcMainView);		// ���� �� â�� ũ�⸦ ������ �Լ�

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(NULL, 100, 100, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	if (FAILED(m_pDevice->IniDevice()))
	{
		AfxMessageBox(L"����̽� ��ü ���� ����");
		return;
	}

	LoadUseImage();

	m_pBackGround = new CBackGround();
	if (FAILED(m_pBackGround->Initialize()))
	{
		AfxMessageBox(L"��׶��� ��ü ���� ����");
		return;
	}
	m_pBackGround->SetMainView(this);

	m_vecLine = m_pBackGround->GetVectorLine();

	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CMfcToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetSafeHwnd() != NULL &&
		((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().IsWindowVisible() != NULL)
	{
		// �ʿ� ��ü�� �������� Ÿ�� ����
		if (m_MapPngImage.empty())
		{
			m_pBackGround->TileChange(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), m_iDrawID, m_iTileOpSion);
		}

		// �ʿ� ��ü�� ����ִٸ� Object ����
		if (!m_MapPngImage.empty())
		{
			CreateObj();
		}
	}
	else if (((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetSafeHwnd() != NULL &&
				((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().IsWindowVisible() != NULL)
	{
		// �ʿ� ��ü�� ����ִٸ� Object ����
		if (!m_MapPngImage.empty())
		{
			CreateObj();
		}

		// �ʿ� ��ü�� ����ִٸ�
		if (m_MapPngImage.empty())
		{
			int iSelect = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetEnemyAddList().GetCurSel();
			if (-1 < iSelect)
			{
				// UnitTool���� MoveMode�� üũ�� �Ǿ� �ִٸ�
				if (((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetMoveMode().GetCheck())
				{
					list<CObj*>::iterator beign = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetiterEnemy();
					
					if ((*beign)->GetRoateList().empty())
					{
						D3DXVECTOR3 vTem = m_vMovePos;
						vTem.x += GetScrollPos(0);
						vTem.y += GetScrollPos(1);

						int iIndex = m_pBackGround->GetTileIndex(vTem);

						CString temString;
						temString.Format(_T("%d"), iIndex);

						((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetRotateEdit().SetWindowText(temString);

						D3DXVECTOR3 vTemp = m_pBackGround->GetIndexPos(m_vMovePos);

						(*beign)->SetRotate(D3DXVECTOR2(vTemp.x + GetScrollPos(0), vTemp.y + GetScrollPos(1)));
					}
					else
					{
						D3DXVECTOR3 vTem = m_vMovePos;
						vTem.x += GetScrollPos(0);
						vTem.y += GetScrollPos(1);

						int iIndex = m_pBackGround->GetTileIndex(vTem);

						CString temString, temString_2;
						temString.Format(_T("%d"), iIndex);

						((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetRotateEdit().GetWindowTextW(temString_2);

						if (!temString_2.IsEmpty())
						{
							temString = L"," + temString;
							temString_2 += temString;

							((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetRotateEdit().SetWindowText(temString_2);
						}

						D3DXVECTOR3 vTemp = m_pBackGround->GetIndexPos(m_vMovePos);

						(*beign)->SetRotate(D3DXVECTOR2(vTemp.x + GetScrollPos(0), vTemp.y + GetScrollPos(1)));
					}
				}
			}
		}
	}

	Invalidate(FALSE);
	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->PostMessageW(WM_PAINT);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMfcToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	 //TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// Ÿ�� ��ǥ ����
	m_vMovePos = m_pBackGround->GetIndexPos(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
	
	// ��ǥ ����
	//D3DXVECTOR3(float(point.x), float(point.y), 0.f);
	
	Invalidate(FALSE);

	CScrollView::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 CMfcToolView::GetImageSenter()
{
	map<CString, CImage*>::iterator Image = m_MapPngImage.begin();

	float fX = float(Image->second->GetWidth() / 2.f);
	float fY = float(Image->second->GetHeight() / 2.f);

	return D3DXVECTOR3(fX, fY, 0.f);
}

void CMfcToolView::DrawSelectImage()
{
	if (!m_MapPngImage.empty())
	{
		D3DXMATRIX matTrans;
		const TEXINFO*		pTexture = nullptr;
		D3DXMatrixTranslation(&matTrans, m_vMovePos.x, m_vMovePos.y, 0.f);
		m_pDevice->GetSprite()->SetTransform(&matTrans);

		auto Image = m_MapPngImage.begin();
		szBuffer = Image->first;

		int retval = 0;
		retval = szBuffer.Find('_');
		szName = szBuffer.Left(retval);
		szNumber = szBuffer.Mid(retval + 1);

		if (((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetSafeHwnd() != NULL &&
			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().IsWindowVisible() != NULL)
		{
			CString strTemp = szName;

			pTexture = CToolTextureMgr::GetInstance()->GetTexture((strTemp.MakeUpper()).operator LPCWSTR(), szName.operator LPCWSTR(), _ttoi(szNumber));
		}

		else if (((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetSafeHwnd() != NULL &&
			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().IsWindowVisible() != NULL)
		{
			pTexture = CToolTextureMgr::GetInstance()->GetTexture(szObjkey.operator LPCWSTR(), Image->first.operator LPCWSTR(), _ttoi(szNumber));
		}

		if (nullptr == pTexture)
		{
			return;
		}

		m_pDevice->GetSprite()->Draw(pTexture->pTexture
			, NULL
			, &GetImageSenter()
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMfcToolView::CreateObj()
{
	float fX = m_vMovePos.x + GetScrollPos(0);
	float fY = m_vMovePos.y + GetScrollPos(1);
	auto Image = m_MapPngImage.begin();
	int iCur = 0;

	CString		strSelectName;
	CString		strTempName, strCheckName;

	// Map Tool
	if ( ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetSafeHwnd() != NULL && 
		 ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().IsWindowVisible() != NULL)
	{
		if (!lstrcmp(szObjkey, L"BUILDING"))
		{
			CObjMgr::GetInstance()->AddObject(CObjFactory<CBuilding>::CreateObj(D3DXVECTOR3(fX, fY, 0.f), Image->first.operator LPCWSTR()), OBJ_BUILDING);

			iCur = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetStructList().GetCurSel();

			if (0 > iCur)
			{
				return;
			}

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetStructList().GetText(iCur, strSelectName);

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetAddList().InsertString(-1, strSelectName);
		}

		else if (!lstrcmp(szObjkey, L"ACTIVEOBJECT"))
		{

			iCur = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetStructList().GetCurSel();

			if (0 > iCur)
			{
				return;
			}

			CString Check = Image->first;

			int retval = 0;

			retval = Check.Find('_');
			Check = Check.Left(retval);

			// �巳��
			if (!lstrcmp(Check, L"Drum"))
			{
				CObjMgr::GetInstance()->AddObject(CObjFactory<CDrum>::CreateObj(D3DXVECTOR3(fX, fY, 0.f), Image->first.operator LPCWSTR()), OBJ_ACTIVE);
			}

			// ������
			else if (!lstrcmp(Check, L"Generator"))
			{
				CObjMgr::GetInstance()->AddObject(CObjFactory<CGenerator>::CreateObj(D3DXVECTOR3(fX, fY, 0.f), Image->first.operator LPCWSTR()), OBJ_ACTIVE);
			}

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetStructList().GetText(iCur, strSelectName);

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapDialog().GetAddList().InsertString(-1, strSelectName);

		}
	}
	
	// Unit Tool
	if ( ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetSafeHwnd() != NULL &&
		 ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().IsWindowVisible() != NULL)
	{
		strTempName = Image->first;

		int retval = 0;
		retval = strTempName.Find('_');
		strCheckName = strTempName.Left(retval);

		// Player
		if (!lstrcmp(szObjkey, L"CHARACTER"))
		{
			// list�� �÷��̾ ���� ���� �߰� ����
			if (!CObjMgr::GetInstance()->GetPlayerObjList().empty())
			{
				return;
			}

			CObjMgr::GetInstance()->AddObject(CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(fX, fY, 0.f), szObjkey, Image->first.operator LPCWSTR()), OBJ_PLAYER);

			iCur = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetPlayerList().GetCurSel();

			if (0 > iCur)
			{
				return;
			}

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetPlayerList().GetText(iCur, strSelectName);

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetPlayerAddList().AddString(strSelectName);
		}
		else if (!lstrcmp(szObjkey, L"ENEMY"))
		{
			++m_iIndex;

			CObjMgr::GetInstance()->AddObject(CObjFactory<CEnemy>::CreateObj(D3DXVECTOR3(fX, fY, 0.f), szObjkey, Image->first.operator LPCWSTR(), m_iIndex), OBJ_ENEMY);
			
			iCur = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetEnemyList().GetCurSel();

			if (0 > iCur)
			{
				return;
			}
	
			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetEnemyList().GetText(iCur, strSelectName);

			((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetUnitDialog().GetEnemyAddList().AddString(strSelectName);
		}

	}

}

void CMfcToolView::LoadUseImage()
{
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Stage0.png", L"STAGE", TEX_SINGLE)))
	{
		AfxMessageBox(L"��� �ҷ����� ����");
		return;
	}

	// Box
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Box/Box_%d.png", L"BOX", TEX_MULTI, L"Box", 3)))
	{
		AfxMessageBox(L"Box �ҷ����� ����");
		return;
	}

	// Building
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Building/Building_%d.png", L"BUILDING", TEX_MULTI, L"Building", 9)))
	{
		AfxMessageBox(L"Building �ҷ����� ����");
		return;
	}

	// Stone
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Stone/Stone_%d.png", L"STONE", TEX_MULTI, L"Stone", 4)))
	{
		AfxMessageBox(L"Stone �ҷ����� ����"	);
		return;
	}

	// Tree
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Tree/Tree_%d.png", L"TREE", TEX_MULTI, L"Tree", 2)))
	{
		AfxMessageBox(L"Tree �ҷ����� ����");
		return;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Tile/Tile%d.png", L"TILE", TEX_MULTI, L"Tile", 3)))
	{
		AfxMessageBox(L"Ÿ�� �ҷ����� ����");
		return;
	}

	// ĳ���� ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleU/IdleU_%d.png", L"CHARACTER", TEX_MULTI, L"IdleU", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleB/IdleB_%d.png", L"CHARACTER", TEX_MULTI, L"IdleB", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleL/IdleL_%d.png", L"CHARACTER", TEX_MULTI, L"IdleL", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleR/IdleR_%d.png", L"CHARACTER", TEX_MULTI, L"IdleR", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// �»�
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleLU/IdleLU_%d.png", L"CHARACTER", TEX_MULTI, L"IdleLU", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ����
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleLB/IdleLB_%d.png", L"CHARACTER", TEX_MULTI, L"IdleLB", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ���
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleRU/IdleRU_%d.png", L"CHARACTER", TEX_MULTI, L"IdleRU", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ����
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleRB/IdleRB_%d.png", L"CHARACTER", TEX_MULTI, L"IdleRB", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return;
	}

	// ���� ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleU/EIdleU_%d.png", L"ENEMY", TEX_MULTI, L"EIdleU", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleB/EIdleB_%d.png", L"ENEMY", TEX_MULTI, L"EIdleB", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleL/EIdleL_%d.png", L"ENEMY", TEX_MULTI, L"EIdleL", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ��
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleR/EIdleR_%d.png", L"ENEMY", TEX_MULTI, L"EIdleR", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// �»�
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleLU/EIdleLU_%d.png", L"ENEMY", TEX_MULTI, L"EIdleLU", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ����
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleLB/EIdleLB_%d.png", L"ENEMY", TEX_MULTI, L"EIdleLB", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ���
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleRU/EIdleRU_%d.png", L"ENEMY", TEX_MULTI, L"EIdleRU", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	// ����
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/EIdleRB/EIdleRB_%d.png", L"ENEMY", TEX_MULTI, L"EIdleRB", 1)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/Drum/Drum_%d.png", L"DRUM", TEX_MULTI, L"Drum", 1)))
	{
		AfxMessageBox(L"�巳�� �ҷ����� ����");
		return;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/Generator/Generator_%d.png", L"GENERATOR", TEX_MULTI, L"Generator", 2)))
	{
		AfxMessageBox(L"������ �ҷ����� ����");
		return;
	}

}
////////////////////////////////////////////////////////////////////////////////