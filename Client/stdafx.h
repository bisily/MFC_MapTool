// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#ifdef _DEBUG

// 현재 디버그 버전에서 CRTDBG_MAP_ALLOC를 정의하면 new로 할당한 모든 인스턴스의 소스정보를 기록한다.
#define CRTDBG_MAP_ALLOC

// C 런타임 디버그 (crtdbg) 헤더에는 new와 delete의 디버그 버전이 포함되어있음.
#include <crtdbg.h>

// 메모리 누수 체크에서는 new 연산자를 새로이 정의한다.
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

#endif