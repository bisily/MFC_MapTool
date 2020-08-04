// UnitDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "UnitDialog.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Player.h"
#include "Enemy.h"

// CUnitDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitDialog, CDialog)

CUnitDialog::CUnitDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITDIALOG, pParent)
	, m_Name(_T(""))
	, m_iHp(0)
	, m_fPosX(0)
	, m_fPosY(0)
{

}

CUnitDialog::~CUnitDialog()
{
	for (auto i : m_MapPngImage)
	{
		i.second->Destroy();
		Safe_Delete(i.second);
	}
	m_MapPngImage.clear();

}

void CUnitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_iHp);
	DDX_Text(pDX, IDC_EDIT5, m_fPosX);
	DDX_Text(pDX, IDC_EDIT6, m_fPosY);
	DDX_Control(pDX, IDC_LIST4, m_Player);
	DDX_Control(pDX, IDC_CHECK1, m_MoveMod[0]);
	DDX_Control(pDX, IDC_CHECK3, m_MoveMod[1]);
	DDX_Control(pDX, IDC_PLAYER_PICTURE, m_PlayerPicture);
	DDX_Control(pDX, IDC_ENEMY_PICTURE, m_EnemyPicture);
	DDX_Control(pDX, IDC_LIST3, m_Enemy);
	DDX_Control(pDX, IDC_LIST2, m_EnemyADD);
	DDX_Control(pDX, IDC_LIST1, m_PlayerAddList);
	DDX_Control(pDX, IDC_EDIT4, m_RotateEdit);
}


BEGIN_MESSAGE_MAP(CUnitDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitDialog::OnPlayerADD)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitDialog::OnPlayerDelete)
	ON_BN_CLICKED(IDC_BUTTON10, &CUnitDialog::OnPlayerSave)
	ON_BN_CLICKED(IDC_BUTTON11, &CUnitDialog::OnPlayerLoad)
	ON_BN_CLICKED(IDC_BUTTON14, &CUnitDialog::OnDeleteWayPoint)
	ON_BN_CLICKED(IDC_BUTTON8, &CUnitDialog::OnEnemyADD)
	ON_BN_CLICKED(IDC_BUTTON9, &CUnitDialog::OnEnemySelectCancel)
	ON_BN_CLICKED(IDC_BUTTON12, &CUnitDialog::OnEnemySave)
	ON_BN_CLICKED(IDC_BUTTON13, &CUnitDialog::OnEnemyLoad)
	ON_LBN_SELCHANGE(IDC_LIST4, &CUnitDialog::OnListClick)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitDialog::OnSelectCancel)
	ON_LBN_SELCHANGE(IDC_LIST3, &CUnitDialog::OnEnemyListClick)
	ON_BN_CLICKED(IDC_BUTTON16, &CUnitDialog::OnEnemyDelete)
	ON_LBN_SELCHANGE(IDC_LIST2, &CUnitDialog::OnEnemyAddListClick)
END_MESSAGE_MAP()


// CUnitDialog �޽��� ó�����Դϴ�.

BOOL CUnitDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	/*if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleU/IdleU_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleRU/IdleRU_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleR/IdleR_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleRB/IdleRB_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleB/IdleB_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleLB/IdleLB_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleL/IdleL_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Character/IdleLU/IdleLU_%d.png", L"CHARACTER", TEX_MULTI, L"Idle", 1)))
	{
		AfxMessageBox(L"ĳ���� �ҷ����� ����");
		return E_FAIL;
	}

	
	if (FAILED(CToolTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy/Idle/Idle_%d.png", L"ENEMY", TEX_MULTI, L"Idle", 15)))
	{
		AfxMessageBox(L"���� �ҷ����� ����");
		return E_FAIL;
	}
	*/
	/*
	for (int i = 0; i < 8; ++i)
	{
		wsprintf(szBuffer, L"Idle_%d", i);

		szFullPath = L"../Texture/Character/Idle/";
		szFullPath += szBuffer;
		szFullPath += L".png";

		auto iter = m_MapPngImage.find(szBuffer);

		if (iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(szFullPath);

			m_MapPngImage.insert(make_pair(szBuffer, pPngImage));
			m_Player.AddString(szBuffer);
		}
	}*/

	

	wifstream	LoadFile;
	LoadFile.open(L"../Data/ImgPath.txt", ios::in);

	TCHAR		szObjKey[MIN_STR] = L"";
	TCHAR		szStateKey[MIN_STR] = L"";
	TCHAR		szCount[MIN_STR] = L"";
	TCHAR		szImgPath[MAX_PATH] = L"";
	int			i = 0;

	while (!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		int iCount = _ttoi(szCount);

		if (1 == iCount)
		{
			auto iter = m_MapPngImage.find(szStateKey);

			if (iter == m_MapPngImage.end())
			{
				CImage*		pPngImage = new CImage;

				PathRemoveFileSpec(szImgPath);
				
				lstrcat(szImgPath, L"\\");
				lstrcat(szImgPath, szStateKey);
				lstrcat(szImgPath, L"_0.png");

				pPngImage->Load(szImgPath);

				m_MapPngImage.insert(make_pair(szStateKey, pPngImage));
				m_Player.InsertString(-1, szStateKey);
			}
		}

		i++;

		if (i > 8 && i < 17)
		{
			auto iter = m_MapPngImage.find(szStateKey);

			iCount = _ttoi(szCount);

			if (3 == iCount)
			{
				if (iter == m_MapPngImage.end())
				{
					CImage*		pPngImage = new CImage;

					PathRemoveFileSpec(szImgPath);

					lstrcat(szImgPath, L"\\");
					lstrcat(szImgPath, szStateKey);
					lstrcat(szImgPath, L"_0.png");

					pPngImage->Load(szImgPath);

					m_MapPngImage.insert(make_pair(szStateKey, pPngImage));
					m_Enemy.InsertString(-1, szStateKey);
				}
			}
		}
	}

	LoadFile.close();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

#pragma region Player

void CUnitDialog::OnPlayerADD()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData(TRUE);

	int iCur = m_Player.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	TCHAR szBuffer[MIN_STR]{};

	m_Player.GetText(iCur, szBuffer);

	if (!CObjMgr::GetInstance()->GetPlayerObjList().empty())
	{
		return;
	}

	auto iter = m_MapPngImage.find(szBuffer);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().insert(make_pair(szBuffer, iter->second));

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"CHARACTER");

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);

}

void CUnitDialog::OnPlayerDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	for (auto i : CObjMgr::GetInstance()->GetPlayerObjList())
	{
		Safe_Delete(i);
	}

	CObjMgr::GetInstance()->GetPlayerObjList().clear();

	m_PlayerAddList.ResetContent();

}

void CUnitDialog::OnPlayerSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	TCHAR	szDirPath[MAX_PATH]{};

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	// ���� ���丮 ��θ� ����(vcproj ������ �ִ� ���丮)
	SetCurrentDirectory(szDirPath);
	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �������ִ� �Լ�
	PathRemoveFileSpec(szDirPath);
	// ������ ��θ� �߶󳻰� ���� ��θ� �������ִ� �Լ�
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;


	DWORD		dwByte = 0;

	list<CObj*> pPlayerList = CObjMgr::GetInstance()->GetPlayerObjList();

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (auto list : pPlayerList)
	{
		WriteFile(hFile, &list->GetInfo()->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		TCHAR szBuffer_1[MIN_STR];

		lstrcpy(szBuffer_1, list->GetObjKey().c_str());
		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);

		lstrcpy(szBuffer_1, list->GetStateKey().c_str());
		lstrcat(szBuffer_1, L"_");
		lstrcat(szBuffer_1, list->GetCount().c_str());

		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CUnitDialog::OnPlayerLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	// ��� : �ٸ� â���� �Ѿ� �� �� ���� �߻���Ų ���̾�α׿� ��ȭ�� ������ �ٸ� �۾��� �� �� �ִ� ���̾�α�
	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	m_PlayerAddList.ResetContent();

	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);

	lstrcat(szDirPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	TCHAR szBuffer[MIN_STR] = L"";
	TCHAR szBuffer2[MIN_STR] = L"";
	D3DXVECTOR3 vPos;

	while (true)
	{
		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);
		ReadFile(hFile, szBuffer2, MIN_STR, &dwByte, NULL);

		const wstring wstrTemp = szBuffer2;
		CString wstrTemp2 = szBuffer;

		if (dwByte == 0)
		{
			break;
		}

		m_PlayerAddList.AddString(szBuffer2);

		CObjMgr::GetInstance()->AddObject(CObjFactory<CPlayer>::CreateObj(vPos, wstrTemp2, wstrTemp), OBJ_PLAYER);
	}

	CloseHandle(hFile);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CUnitDialog::OnListClick()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	int iCur = m_Player.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	TCHAR szBuffer[MIN_STR]{};

	m_Player.GetText(iCur, szBuffer);

	auto iter = m_MapPngImage.find(szBuffer);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	m_PlayerPicture.SetBitmap(*iter->second);

	UpdateData(FALSE);
}

void CUnitDialog::OnSelectCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

#pragma endregion

#pragma region Enemy

void CUnitDialog::OnEnemyADD()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	int iCur = m_Enemy.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	TCHAR szBuffer[MIN_STR]{};

	m_Enemy.GetText(iCur, szBuffer);

	auto iter = m_MapPngImage.find(szBuffer);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().insert(make_pair(szBuffer, iter->second));

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"ENEMY");

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CUnitDialog::OnEnemySelectCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CUnitDialog::OnEnemyListClick()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	int iCur = m_Enemy.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	TCHAR szBuffer[MIN_STR]{};

	m_Enemy.GetText(iCur, szBuffer);

	auto iter = m_MapPngImage.find(szBuffer);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	m_EnemyPicture.SetBitmap(*iter->second);

	UpdateData(FALSE);
}

void CUnitDialog::OnEnemyDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iCur = m_EnemyADD.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	list<CObj*>::iterator begin = CObjMgr::GetInstance()->GetEnemyObjList().begin();

	for (int i = 0; i < iCur; ++i)
	{
		++begin;
	}

	Safe_Delete(*begin);

	CObjMgr::GetInstance()->GetEnemyObjList().erase(begin);

	m_EnemyADD.DeleteString(iCur);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);

}

void CUnitDialog::OnEnemySave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	TCHAR	szDirPath[MAX_PATH]{};

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	// ���� ���丮 ��θ� ����(vcproj ������ �ִ� ���丮)
	SetCurrentDirectory(szDirPath);
	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �������ִ� �Լ�
	PathRemoveFileSpec(szDirPath);
	// ������ ��θ� �߶󳻰� ���� ��θ� �������ִ� �Լ�
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;


	DWORD		dwByte = 0;
	TCHAR		szBuffer_1[MIN_STR];
	int			iIndex = 0;
	int			iRotateSize = 0;
	D3DXVECTOR2 vTemp;

	list<CObj*> pEnemyList = CObjMgr::GetInstance()->GetEnemyObjList();
	list<D3DXVECTOR2>::iterator begin_iter;
	
	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	for (auto list : pEnemyList)
	{
		WriteFile(hFile, &list->GetInfo()->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		lstrcpy(szBuffer_1, list->GetObjKey().c_str());
		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);

		// ObjKey�� �־���
		lstrcpy(szBuffer_1, list->GetStateKey().c_str());
		lstrcat(szBuffer_1, L"_");
		lstrcat(szBuffer_1, L"0");

		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
		
		// ����Ʈ ��Ʈ���� �ε��� ��ȣ�� ����
		iIndex = list->GetIndex();
		
		swprintf_s(szBuffer_1, L"%d", iIndex);
		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
	
		// ��Ʈ�� ����Ʈ�� ��� ���� �ʴٸ�
		if (!list->GetRoateList().empty())
		{
			TCHAR temp[MIN_STR];
			lstrcpy(temp, L"NEXT");
			
			lstrcpy(szBuffer_1, L"RotateMode");
			WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);


			// ��ǥ������ŭ �����ϰ� �������� END Ű���带 ����
			for (begin_iter = list->GetRoateList().begin(); begin_iter != list->GetRoateList().end(); )
			{
				D3DXVECTOR2 vRotatePos(begin_iter->x, begin_iter->y);

				WriteFile(hFile, vRotatePos, sizeof(D3DXVECTOR2), &dwByte, NULL);

				++begin_iter;

				if (begin_iter == list->GetRoateList().end())
				{
					lstrcpy(temp, L"END");
				}
				
				WriteFile(hFile, temp, MIN_STR, &dwByte, NULL);
			}
		}
		// ��� �ִٸ� �����������
		else
		{
			lstrcpy(szBuffer_1, L"StopMode");
			WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
		}
	}

	CloseHandle(hFile);

}

void CUnitDialog::OnEnemyLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	// ��� : �ٸ� â���� �Ѿ� �� �� ���� �߻���Ų ���̾�α׿� ��ȭ�� ������ �ٸ� �۾��� �� �� �ִ� ���̾�α�
	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	m_EnemyADD.ResetContent();

	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);

	lstrcat(szDirPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	TCHAR szBuffer[MIN_STR] = L"";
	TCHAR szBuffer2[MIN_STR] = L"";
	TCHAR szBuffer3[MIN_STR] = L"";
	TCHAR szBuffer4[MIN_STR] = L"";
	TCHAR szBuffer5[MIN_STR] = L"";
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vRoatePos;

	int iCnt = 0;

	while (true)
	{
		iCnt++;
		// ��ġ�Ǵ� ��ǥ��
		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);	
		
		// ObjŰ ��
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);	
		
		// State ��
		ReadFile(hFile, szBuffer2, MIN_STR, &dwByte, NULL);

		// �ε��� ��
		ReadFile(hFile, szBuffer3, MIN_STR, &dwByte, NULL);
		
		// Rotate Mode �Ǵ� Stop Mode
		ReadFile(hFile, szBuffer4, MIN_STR, &dwByte, NULL);

		CString wstrTemp = szBuffer2;
		CString wstrTemp2 = szBuffer;
		
		int retval = 0;
		retval = wstrTemp.Find('_');
		wstrTemp = wstrTemp.Left(retval);

		if (dwByte == 0)
		{
			break;
		}

		m_EnemyADD.AddString(wstrTemp);

		const wstring wstrStatejKey = wstrTemp;

		CObjMgr::GetInstance()->AddObject(CObjFactory<CEnemy>::CreateObj(vPos, wstrTemp2, wstrStatejKey, _ttoi(szBuffer3)), OBJ_ENEMY);

		if (!lstrcmp(szBuffer4, L"RotateMode"))
		{
			list<CObj*> pEnemyList = CObjMgr::GetInstance()->GetEnemyObjList();
			
			lstrcpy(szBuffer5, L"NEXT");
			
			while(lstrcmp(szBuffer5, L"END"))
			{	
				ReadFile(hFile, vRoatePos, sizeof(D3DXVECTOR2), &dwByte, NULL);

				ReadFile(hFile, szBuffer5, MIN_STR, &dwByte, NULL);

				pEnemyList.back()->SetRotate(vRoatePos);
			}
		}
	}

	CloseHandle(hFile);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetCount(--iCnt);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CUnitDialog::OnEnemyAddListClick()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	int iCur = m_EnemyADD.GetCurSel();

	if (0 > iCur)
	{
		return;
	}

	iCur++;

	begin_EnemyList = CObjMgr::GetInstance()->GetEnemyObjList().begin();
	end_EnemyList = CObjMgr::GetInstance()->GetEnemyObjList().end();

	for (; begin_EnemyList != end_EnemyList; ++begin_EnemyList)
	{
		if((*begin_EnemyList)->GetIndex() == iCur)
		{
			break;
		}
	}

	UpdateData(FALSE);

}

void CUnitDialog::OnDeleteWayPoint()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


#pragma endregion
