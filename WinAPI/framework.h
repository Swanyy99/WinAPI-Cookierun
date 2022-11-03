// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "commdlg.h"

// C++ 표준 라이브러리
#include <clocale>
#include <chrono>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <cassert>
#include <queue>
#include <stack>

using namespace std;

// Direct2D
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

using namespace D2D1;

// FMOD
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib,"FMOD/lib/fmod_vc.lib")

using namespace FMOD;

// Util
#include "SingleTon.h"
#include "Struct.h"
#include "Logger.h"

// Engine 1.0
#include "WinAPI.h"

#include "CCore.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCollisionManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"

// Asset
#include "CGameObject.h"
#include "CScene.h"

// Resource
#include "CResource.h"
#include "CImage.h"
#include "CSound.h"
#include "CAnimation.h"
#include "CTile.h"

// UI
#include "CUI.h"
#include "CButton.h"
#include "CPanel.h"

// Component
#include "CComponent.h"
#include "CAnimator.h"
#include "CCollider.h"