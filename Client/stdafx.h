// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <atlstr.h>
#include <fstream>
#include <process.h>
#include <ctime>
#include <io.h>

#include "Device.h"

#include "TextureMgr.h"
#include "TimeMgr.h"
#include "ObjFactory.h"
#include "KeyMgr.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#ifdef _DEBUG

// ���� ����� �������� CRTDBG_MAP_ALLOC�� �����ϸ� new�� �Ҵ��� ��� �ν��Ͻ��� �ҽ������� ����Ѵ�.
#define CRTDBG_MAP_ALLOC

// C ��Ÿ�� ����� (crtdbg) ������� new�� delete�� ����� ������ ���ԵǾ�����.
#include <crtdbg.h>

// �޸� ���� üũ������ new �����ڸ� ������ �����Ѵ�.
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

#endif